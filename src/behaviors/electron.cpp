#include "behaviors/electron.h"
#include "particles/electrons.h"
#include "particles/conductor_particle.h"

void ElectronBehavior::update(std::shared_ptr<Particle> particle, Grid &grid, const UpdateParams &params) {
    if (params.direction != 1)
        return;

    const auto index = particle->getIndex();
    if (type == ElectronType::HEAD)
        grid.setIndex(index, std::make_shared<ElectronTailParticle>());
    else
        grid.setIndex(index, std::make_shared<ConductorParticle>());
}