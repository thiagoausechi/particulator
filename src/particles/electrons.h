#ifndef ELECTRONS_H
#define ELECTRONS_H

#include "particles/particle.h"
#include "behaviors/electron.h"

class ElectronTailParticle final : public Particle {
public:
    explicit ElectronTailParticle() : Particle(
        "electron_tail",
        ParticleProperties()
        .setColor({15.0f, 1.0f, 0.5f})
        .setBehaviors({
            std::make_shared<ElectronBehavior>(ElectronType::TAIL)
        })
    ) { ; }
};

class ElectronHeadParticle final : public Particle {
public:
    explicit ElectronHeadParticle() : Particle(
        "electron_head",
        ParticleProperties()
        .setColor({210.0f, 1.0f, 0.5f})
        .setBehaviors({
            std::make_shared<ElectronBehavior>(ElectronType::HEAD)
        })
    ) { ; }
};

#endif //ELECTRONS_H
