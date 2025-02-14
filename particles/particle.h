#ifndef PARTICLE_H
#define PARTICLE_H

#include "colors.h"
#include "update_params.h"

class Grid;
class Behavior;

struct ParticleProperties {
    Color color;
    bool empty;
    bool solid;
    std::vector<std::shared_ptr<Behavior>> behaviors;

    explicit ParticleProperties() : color(Colors::Black), empty(false), solid(true), behaviors({}) {
    }

    ParticleProperties &setColor(const Color color) {
        this->color = color;
        return *this;
    }

    ParticleProperties &setEmpty(const bool empty = true) {
        this->empty = empty;
        return *this;
    }

    ParticleProperties &setSolid(const bool solid = true) {
        this->solid = solid;
        return *this;
    }

    ParticleProperties &setBehaviors(const std::vector<std::shared_ptr<Behavior>> &behaviors) {
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
    explicit Particle(const ParticleProperties &properties) : index(-1), properties(properties) {
    }

    void setIndex(int idx);

    int getIndex() const;

    void update(Grid &grid, int idx, const UpdateParams &params) const;

    ParticleProperties getProperties() const;

    virtual ~Particle() = default;
};

#endif //PARTICLE_H
