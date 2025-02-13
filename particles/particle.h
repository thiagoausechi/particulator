#ifndef PARTICLE_H
#define PARTICLE_H

#include "colors.h"

class Grid;

struct ParticleProperties {
    Color color;
    bool empty;
    bool solid;

    explicit ParticleProperties(const Color color) : color(color), empty(false), solid(true) {
    }

    explicit ParticleProperties(const Color color, const bool empty) : color(color), empty(empty), solid(true) {
    }

    ParticleProperties(const Color color, const bool empty, const bool solid) : color(color), empty(empty),
        solid(solid) {
    }

    ~ParticleProperties() = default;
};

class Particle : public std::enable_shared_from_this<Particle> {
protected:
    int index;
    ParticleProperties properties;

public:
    Particle(const int index, const ParticleProperties &properties) : index(index), properties(properties) {
    }

    void setIndex(const int idx);

    void update(Grid &grid, const int idx);

    ParticleProperties getProperties() const;

    virtual ~Particle() = default;
};

#endif //PARTICLE_H
