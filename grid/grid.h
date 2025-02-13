#ifndef GRID_H
#define GRID_H

#include "particle.h"
#include "empty_particle.h"
#include <set>
#include <vector>
#include <limits>
#include <cstdio>
#include <allegro5/allegro_primitives.h>

class Grid {
    int width, height;
    std::vector<std::shared_ptr<Particle> > grid;
    std::set<int> modifiedIndices;
    bool cleared;
    int rowCount;

public:
    Grid(): width(0), height(0), cleared(false), rowCount(0) {
    }

    void clear() {
        const int size = this->width * this->height;
        this->grid.clear();
        this->modifiedIndices.clear();
        this->grid.reserve(size);
        for (int index = 0; index < size; index++) {
            this->grid.push_back(std::make_shared<EmptyParticle>(index));
            this->modifiedIndices.insert(index);
        }
        this->cleared = true;
    }

    void init(const int width, const int height) {
        this->width = width;
        this->height = height;
        this->clear();
        this->cleared = false;
        this->rowCount = 0;

        if (this->grid.size() <= static_cast<size_t>(std::numeric_limits<int>::max())) {
            rowCount = static_cast<int>(this->grid.size() / this->width);
        } else {
            fprintf(stderr, "grid size too large for int\n");
        }
    }

    void update() const {
        return;
    }

    void draw(const int resolution) const {
        const auto resolutionAsFloat = static_cast<float>(resolution);
        for (const int index: this->modifiedIndices) {
            const float
                    x = static_cast<float>(index % this->width),
                    y = static_cast<float>(index / this->width),
                    startX = x * resolutionAsFloat,
                    startY = y * resolutionAsFloat,
                    endX = startX + resolutionAsFloat,
                    endY = startY + resolutionAsFloat;
            const auto color = this->grid[index]->getProperties().color.toAllegro();
            al_draw_filled_rectangle(startX, startY, endX, endY, color);
        }
    }

    [[nodiscard]] int indexOf(const int x, const int y) const {
        return y * this->width + x;
    }

    void setIndex(const int index, std::shared_ptr<Particle> particle) {
        if (!this->isValidIndex(index)) {
            fprintf(stderr, "Index out of bounds: %d\n", index);
            return;
        }
        this->grid[index] = std::move(particle);
        this->grid[index]->setIndex(index);
        this->modifiedIndices.insert(index);
    }

    void set(const int x, const int y, std::shared_ptr<Particle> particle) {
        const int index = this->indexOf(x, y);
        if (!this->isValidIndex(index)) {
            fprintf(stderr, "Coordinates out of bounds: (%d, %d)\n", x, y);
            return;
        }
        this->setIndex(index, std::move(particle));
    }

    void swap(const int a, const int b) {
        if (!this->isValidIndex(a) || !this->isValidIndex(b))
            return;
        std::swap(this->grid[a], this->grid[b]);
        this->grid[a]->setIndex(b);
        this->grid[b]->setIndex(a);
        this->modifiedIndices.insert(a);
        this->modifiedIndices.insert(b);
    }

    [[nodiscard]] bool isEmpty(const int index) const {
        if (!this->isValidIndex(index))
            return false;

        return this->grid[index]->getProperties().empty;
    }

    [[nodiscard]] bool isSolid(const int index) const {
        if (!this->isValidIndex(index))
            return true;

        return this->grid[index]->getProperties().solid;
    }

    [[nodiscard]] bool needsUpdate() const {
        return this->cleared || !this->modifiedIndices.empty();
    }

    [[nodiscard]] int getWidth() const {
        return this->width;
    }

    [[nodiscard]] int getHeight() const {
        return this->height;
    }

    [[nodiscard]] bool isValidIndex(const int index) const {
        return !(index < 0 || index > this->grid.size() - 1);
    }

    ~Grid() = default;
};

#endif //GRID_H
