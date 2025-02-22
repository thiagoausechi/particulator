#ifndef GRID_H
#define GRID_H

#include <set>
#include <vector>
#include <limits>
#include <cstdio>
#include <allegro5/allegro_primitives.h>

#include "particles/particle.h"
#include "particles/empty_particle.h"

class Grid {
protected:
    int width, height, resolution;
    std::vector<std::shared_ptr<Particle>> grid;
    std::vector<std::shared_ptr<Particle>> gridSnapshotBeforeUpdate;
    std::set<int> modifiedIndices;
    bool cleared;
    int rowCount;

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
                this->particleAt(index)->update(*this, index, params);
            }
        }
    }

    void beforeUpdate() {
        this->cleared = false;
        this->modifiedIndices.clear();
        this->gridSnapshotBeforeUpdate = this->grid;
    }

public:
    Grid(): width(0), height(0), resolution(0), cleared(false), rowCount(0) {
    }

    void init(const int width, const int height, const int resolution) {
        this->width = width;
        this->height = height;
        this->resolution = resolution;
        this->clear();
        this->cleared = false;
        this->rowCount = 0;

        if (this->grid.size() <= static_cast<size_t>(std::numeric_limits<int>::max()))
            rowCount = static_cast<int>(this->grid.size() / this->width);
        else fprintf(stderr, "grid size too large for int\n");
    }


    virtual void update() {
        this->beforeUpdate();
        this->updateWithParams();
    }

    void draw() const {
        for (int index = 0; index < this->grid.size(); ++index) {
            // TEMP-REMOVED: for (const auto index: this->modifiedIndices) {
            const int
                    x = index % this->width,
                    y = index / this->width;
            const auto color = this->particleAt(index)->getProperties().color;
            this->drawPixel(x, y, color);
        }
    }

    void drawPixel(const int x, const int y, const Color &color) const {
        const auto resolutionAsFloat = static_cast<float>(this->resolution);
        const float
                startX = static_cast<float>(x) * resolutionAsFloat,
                startY = static_cast<float>(y) * resolutionAsFloat,
                endX = startX + resolutionAsFloat,
                endY = startY + resolutionAsFloat;
        al_draw_filled_rectangle(startX, startY, endX, endY, color.toAllegro());
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
        this->particleAt(index)->setIndex(index);
        this->modifiedIndices.insert(index);
    }

    [[nodiscard]] bool isEmpty(const int index) const {
        if (!this->isValidIndex(index))
            return false;

        return this->particleAt(index)->getProperties().empty;
    }

    [[nodiscard]] bool isSolid(const int index) const {
        if (!this->isValidIndex(index))
            return true;

        return this->particleAt(index)->getProperties().solid;
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

    [[nodiscard]] std::shared_ptr<Particle> getParticleAtPreviousState(const int index) const {
        if (!this->isValidIndex(index))
            return nullptr;
        return this->gridSnapshotBeforeUpdate[index];
    }

    [[nodiscard]] bool isValidIndex(const int index) const {
        return !(index < 0 || index > this->grid.size() - 1);
    }

    virtual ~Grid() = default;
};

#endif //GRID_H
