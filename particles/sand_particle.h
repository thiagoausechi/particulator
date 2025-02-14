#ifndef SAND_PARTICLE_H
#define SAND_PARTICLE_H

#include "particle.h"
#include "colors.h"

class SandParticle final : public Particle {
public:
    explicit SandParticle() : Particle(
        ParticleProperties()
            .setColor(Colors::varyColor({40.0, 65.2, 60.6}))
        ) {
    }
};

#endif // SAND_PARTICLE_H
