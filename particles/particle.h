#ifndef PARTICLE_H
#define PARTICLE_H

#include <allegro5/allegro_color.h>

struct ParticleProperties {
    ALLEGRO_COLOR color;
    bool empty;
    bool solid;

    explicit ParticleProperties(const ALLEGRO_COLOR color) : color(color), empty(false), solid(true) {
    }

    explicit ParticleProperties(const ALLEGRO_COLOR color, const bool empty) : color(color), empty(empty), solid(true) {
    }

    ParticleProperties(const ALLEGRO_COLOR color, const bool empty, const bool solid) : color(color), empty(empty),
        solid(solid) {
    }

    ~ParticleProperties() = default;
};

class Particle {
protected:
    int index;
    ParticleProperties properties;

public:
    Particle(const int index, const ParticleProperties &properties) : index(index), properties(properties) {
    }

    void updateIndex(const int index) {
        this->index = index;
    }

    [[nodiscard]] ParticleProperties getProperties() const {
        return this->properties;
    }

    virtual ~Particle() = default;
};

#endif //PARTICLE_H
