#ifndef CONDUCTOR_PARTICLE_H
#define CONDUCTOR_PARTICLE_H

#include "particles/particle.h"
#include "behaviors/conductor.h"

class ConductorParticle final : public Particle {
public:
    explicit ConductorParticle() : Particle(
        "conductor",
        ParticleProperties()
        .setColor({50.0f, 1.0f, 0.5f})
        .setBehaviors({
            std::make_shared<ConductorBehavior>()
        })) { ; }
};

#endif // CONDUCTOR_PARTICLE_H
