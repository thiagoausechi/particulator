#ifndef BIDIRECTIONAL_GRID_H
#define BIDIRECTIONAL_GRID_H

#include "grid.h"

class BidirectionalGrid final : public Grid {
public:
    bool update() override {
        this->beforeUpdate();

        for (int pass = -1; pass <= 1; pass += 2)
            this->updateWithParams({.direction = pass});

        return !this->modifiedIndices.empty();
    }

    int modifyIndexHook(const int index, const UpdateParams &params) override {
        if (params.direction == -1)
            return this->grid.size() - index - 1;
        return index;
    }
};

#endif //BIDIRECTIONAL_GRID_H
