#ifndef EMPTY_PARTICLE_H
#define EMPTY_PARTICLE_H

#include "particle.h"
#include "colors.h"

class EmptyParticle final : public Particle {
public:
  explicit EmptyParticle() : Particle(ParticleProperties().setEmpty()) {
  }
};

#endif //EMPTY_PARTICLE_H
