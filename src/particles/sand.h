#ifndef SAND_PARTICLE_H
#define SAND_PARTICLE_H

#include "particles/particle.h"
#include "behaviors/moves.h"
#include "lib/colors.h"

class SandParticle final : public Particle {
public:
    explicit SandParticle() : Particle(
        "sand",
        ParticleProperties()
        .setColor(Colors::varyColor({40.0, 65.2, 60.6}))
        .setBehaviors({
            std::make_shared<MovesBehavior>(3, 0.4)
        })) { ; }
};

#endif // SAND_PARTICLE_H
