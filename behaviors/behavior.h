#ifndef BEHAVIOR_H
#define BEHAVIOR_H

#include <cstdio>
#include <vector>

class Particle;
class Grid;

class Behavior {
public:
    void update(std::shared_ptr<Particle> particle, Grid &grid);
};

#endif //BEHAVIOR_H
