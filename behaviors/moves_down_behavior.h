#ifndef MOVES_DOWN_BEHAVIOR_H
#define MOVES_DOWN_BEHAVIOR_H

#include <cstdio>
#include <vector>

#include "behavior.h"

class MovesDownBehavior : public Behavior {
    void update(std::shared_ptr<Particle> particle, Grid &grid) override {
        fprintf(stderr, "MovesDownBehavior::update() not implemented\n");
    };
};

#endif //MOVES_DOWN_BEHAVIOR_H
