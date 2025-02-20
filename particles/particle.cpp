#include "particle.h"
#include "behavior.h"
#include "grid.h"

void Particle::setIndex(const int idx) {
    this->index = idx;
}

int Particle::getIndex() const {
    return this->index;
}

void Particle::update(Grid &grid, const int idx, const UpdateParams &params) const {
    for (const auto &behavior: this->properties.behaviors)
        behavior->update(grid.particleAt(idx), grid, params);
}

ParticleProperties Particle::getProperties() const {
    return this->properties;
}
