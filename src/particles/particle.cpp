#include "particles/particle.h"
#include "behaviors/behavior.h"
#include "grid/grid.h"
#include "grid/update_params.h"

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

Color Particle::getColor(const Grid &grid, const int idx) const {
    return this->properties.color;
}

bool Particle::canBePlaced(Grid &grid, const int idx) const {
    const auto currentParticleIdAtGrid = grid.particleAt(idx)->id;
    return this->id != currentParticleIdAtGrid;
}
