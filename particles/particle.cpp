#include "particle.h"
#include "grid.h"

void Particle::setIndex(const int idx) {
    this->index = idx;
}

void Particle::update(Grid &grid, const int idx) {
    if (const auto bellow = idx + grid.getWidth(); grid.isEmpty(bellow)) {
        grid.swap(idx, bellow);
    }
}

ParticleProperties Particle::getProperties() const {
    return this->properties;
}
