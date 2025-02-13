#include "particle.h"
#include "behavior.h"
#include "grid.h"

void Particle::setIndex(const int idx) {
    this->index = idx;
}

void Particle::update(Grid &grid, const int idx) const {
    for (const auto behavior: this->properties.behaviors)
        behavior->update(grid.particleAt(idx), grid);
}

ParticleProperties Particle::getProperties() const {
    return this->properties;
}
