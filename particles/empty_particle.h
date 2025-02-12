#ifndef EMPTY_PARTICLE_H
#define EMPTY_PARTICLE_H

#include "particle.h"

class EmptyParticle : public Particle {
public:
  explicit EmptyParticle(const int index) : Particle(index, ParticleProperties(al_map_rgb(255, 0, 0), true)) {
  }
};

#endif //EMPTY_PARTICLE_H
