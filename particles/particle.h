#ifndef PARTICLE_H
#define PARTICLE_H

#include "colors.h"

class Grid;
class Behavior;

struct ParticleProperties {
    Color color;
    bool empty;
    bool solid;
    std::vector<std::shared_ptr<Behavior> > behaviors;

    explicit ParticleProperties(const Color color) : color(color), empty(false), solid(true), behaviors({}) {
    }

    ParticleProperties &setEmpty(const bool empty = true) {
        this->empty = empty;
        return *this;
    }

    ParticleProperties &setSolid(const bool solid = true) {
        this->solid = solid;
        return *this;
    }

    ParticleProperties &setBehaviors(const std::vector<std::shared_ptr<Behavior> > &behaviors) {
        this->behaviors = behaviors;
        return *this;
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

    void update(Grid &grid, const int idx) const;

    ParticleProperties getProperties() const;

    virtual ~Particle() = default;
};

#endif //PARTICLE_H
