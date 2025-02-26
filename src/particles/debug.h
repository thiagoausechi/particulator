#ifndef DEBUG_PARTICLE_H
#define DEBUG_PARTICLE_H

#include "particles/particle.h"
#include "lib/colors.h"
#include "behaviors/moves.h"

inline Color debugColor{0.0, 100.0, 50.0};
inline ColorModifiers colorModifiers{
    .hueFn = []() { return randomInRange(0, 360); },
    .satFn = []() { return 0; },
    .lightFn = []() { return 0; },
};

class DebugParticle final : public Particle {
public:
    explicit DebugParticle() : Particle(
        "debug",
        ParticleProperties()
        .setColor(Colors::varyColor(debugColor, colorModifiers))
        .setBehaviors({
            std::make_shared<MovesBehavior>(3, 0.9)
        })) { ; }
};

#endif //DEBUG_PARTICLE_H
