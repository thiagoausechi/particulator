#ifndef SAND_PARTICLE_H
#define SAND_PARTICLE_H

#include "behavior.h"
#include "moves_down_behavior.h"
#include "particle.h"
#include "colors.h"

class SandParticle final : public Particle {
public:
    explicit SandParticle() : Particle(
        ParticleProperties()
            .setColor(Colors::varyColor({40.0, 65.2, 60.6}))
            .setBehaviors({std::make_shared<MovesDownBehavior>()})) {
    }
};

#endif // SAND_PARTICLE_H
