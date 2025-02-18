#ifndef BEHAVIOR_H
#define BEHAVIOR_H

#include <cstdio>
#include "grid/grid.h"

class Particle;
class Grid;

class Behavior {
public:
    virtual void update(std::shared_ptr<Particle> particle, Grid &grid, const UpdateParams &params) {
        fprintf(stderr, "Behavior::update() not implemented\n");
    }

    virtual ~Behavior() = default;
};

#endif //BEHAVIOR_H
