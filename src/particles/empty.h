#ifndef EMPTY_PARTICLE_H
#define EMPTY_PARTICLE_H

#include "particles/particle.h"

class EmptyParticle final : public Particle {
public:
  explicit EmptyParticle() : Particle("empty", ParticleProperties().setEmpty()) { ; }
};

#endif //EMPTY_PARTICLE_H
