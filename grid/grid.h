#ifndef GRID_H
#define GRID_H

#include "particle.h"
#include "empty_particle.h"
#include <set>
#include <vector>
#include <limits>
#include <cstdio>

class Grid {
    int width, height;
    std::vector<std::unique_ptr<Particle> > grid;
    std::set<int> modifiedIndices;
    bool cleared;
    int rowCount;

public:
    Grid(): width(0), height(0), cleared(false), rowCount(0) {
    };

    void clear() {
        const int size = this->width * this->height;
        this->grid.clear();
        this->grid.reserve(size);
        for (int index = 0; index < size; index++)
            this->grid.push_back(std::make_unique<EmptyParticle>(index));
        this->cleared = true;
    }

    void init(const int width, const int height) {
        this->width = width;
        this->height = height;
        this->clear();
        this->modifiedIndices.clear();
        this->cleared = false;
        this->rowCount = 0;

        if (this->grid.size() <= static_cast<size_t>(std::numeric_limits<int>::max())) {
            rowCount = static_cast<int>(this->grid.size() / this->width);
        } else {
            fprintf(stderr, "grid size too large for int\n");
        }
    }

    [[nodiscard]] int indexOf(const int x, const int y) const {
        return y * this->width + x;
    }

    void setIndex(const int index, std::unique_ptr<Particle> particle) {
        this->grid[index] = std::move(particle);
        particle->updateIndex(index);
        this->modifiedIndices.insert(index);
    }

    void set(const int x, const int y, std::unique_ptr<Particle> particle) {
        const int index = this->indexOf(x, y);
        if (x < 0 || x >= this->width)
            return;
        if (y < 0 || y >= this->height)
            return;
        this->setIndex(index, std::move(particle));
    }

    void swap(const int a, const int b) {
        if (this->isEmpty(a) || this->isEmpty(b))
            return;
        if (a < 0 || a >= this->grid.size() || b < 0 || b >= this->grid.size())
            return;
        std::swap(this->grid[a], this->grid[b]);
        this->modifiedIndices.insert(a);
        this->modifiedIndices.insert(b);
    }

    bool isEmpty(const int index) const {
        return this->grid[index].get()->getProperties().empty;
    }

    bool isSolid(const int index) const {
        return this->grid[index].get()->getProperties().solid;
    }

    [[nodiscard]] bool needsUpdate() const {
        return this->cleared || !this->modifiedIndices.empty();
    }

    ~Grid() = default;
};

#endif //GRID_H
