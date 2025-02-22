#ifndef CONDUCTOR_H
#define CONDUCTOR_H

#include "behaviors/behavior.h"
#include "particles/electrons.h"
#include "lib/neighborhood_strategy.h"

class Conductor final : public Behavior {
public:
    Conductor() = default;

    void update(std::shared_ptr<Particle> particle, Grid &grid, const UpdateParams &params) override {
        if (params.direction != 1)
            return;

        const auto index = particle->getIndex();
        const auto neighbors = MooreNeighborhoodStrategy().getNeighbors(index, grid);
        int headsSurrounding = 0;

        for (const int currentIndex: neighbors) {
            if (const auto neighbor = grid.getParticleAtPreviousState(currentIndex);
                neighbor && std::dynamic_pointer_cast<ElectronHeadParticle>(neighbor)) {
                headsSurrounding++;
                if (headsSurrounding > 2)
                    break;
            }
        }

        if (headsSurrounding == 1 || headsSurrounding == 2) {
            grid.setIndex(index, std::make_shared<ElectronHeadParticle>());
        }
    }
};

#endif // CONDUCTOR_H
