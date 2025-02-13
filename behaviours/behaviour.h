#ifndef BEHAVIOUR_H
#define BEHAVIOUR_H

#include <cstdio>
#include <vector>

class Particle;
class Grid;

class Behaviour {
    void update(std::shared_ptr<Particle> particle, Grid &grid);
};

#endif //BEHAVIOUR_H
