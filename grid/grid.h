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
protected:
    int width, height;
    std::vector<std::shared_ptr<Particle>> grid;
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
            this->grid.push_back(std::make_shared<EmptyParticle>());
            this->onModified(index);
        }
        this->cleared = true;
    }

    void clearIndex(const int index) {
        this->setIndex(index, std::make_shared<EmptyParticle>());
    }

    void init(const int width, const int height) {
        this->width = width;
        this->height = height;
        this->clear();
        this->cleared = false;
        this->rowCount = 0;

        if (this->grid.size() <= static_cast<size_t>(std::numeric_limits<int>::max()))
            rowCount = static_cast<int>(this->grid.size() / this->width);
        else fprintf(stderr, "grid size too large for int\n");
    }

    void beforeUpdate() {
        this->cleared = false;
        this->modifiedIndices.clear();
    }

    virtual int modifyIndexHook(const int index, const UpdateParams &params) {
        return index;
    }

    void updateWithParams(const UpdateParams &params = {}) {
        for (int row = this->rowCount - 1; row >= 0; row--) {
            const int rowOffset = row * this->width;
            const bool leftToRight = static_cast<bool>(randomInRange(0, 1));
            for (int i = 0; i < this->width; i++) {
                const int columnOffset = leftToRight ? i : -i - 1 + this->width;
                int index = rowOffset + columnOffset;

                index = this->modifyIndexHook(index, params);
                this->grid[index]->update(*this, index, params);
            }
        }
    }

    virtual bool update() {
        this->beforeUpdate();
        this->updateWithParams();
        return !this->modifiedIndices.empty();
    }

    void draw(const int resolution) const {
        const auto resolutionAsFloat = static_cast<float>(resolution);
        if (this->modifiedIndices.empty())
            return;

        for (int index = 0; index < this->grid.size(); ++index) {
            // TEMP-REMOVED: for (const auto index: this->modifiedIndices) {
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
        this->onModified(index);
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
        this->onModified(a);
        this->onModified(b);
    }

    void onModified(const int index) {
        this->grid[index]->setIndex(index);
        this->modifiedIndices.insert(index);
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

    [[nodiscard]] std::shared_ptr<Particle> particleAt(const int index) const {
        if (!this->isValidIndex(index))
            return nullptr;
        return this->grid[index];
    }

    [[nodiscard]] bool isValidIndex(const int index) const {
        return !(index < 0 || index > this->grid.size() - 1);
    }

    virtual ~Grid() = default;
};

#endif //GRID_H
