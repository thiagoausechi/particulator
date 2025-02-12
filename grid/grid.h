#ifndef GRID_H
#define GRID_H

#include <set>

class Grid {
    int width, height;
    std::vector<int> grid;
    std::set<int> modifiedIndices;
    bool cleared;
    int rowCount;

public:
    Grid(): width(0), height(0), cleared(false), rowCount(0) {
    } ;

    void clear() {
        const int size = this->width * this->height;
        this->grid = std::vector(size, 0);
        this->cleared = true;
    }

    void init(const int width, const int height) {
        this->width = width;
        this->height = height;
        this->clear();
        this->modifiedIndices.clear();
        this->cleared = false;
        this->rowCount = this->grid.size() / this->width;
    }

    int indexOf(const int x, const int y) const {
        return y * this->width + x;
    }

    void setIndex(const int index, const int particle) {
        this->grid[index] = particle;
        // after implement the Particle Class
        // this will update the index of the Particle
        this->modifiedIndices.insert(index);
    }

    void set(const int x, const int y, const int particle) {
        const int index = this->indexOf(x, y);
        if (x < 0 || x >= this->width) return;
        if (y < 0 || y >= this->height) return;
        this->setIndex(index, particle);
    }

    ~Grid() = default;
};

#endif //GRID_H
