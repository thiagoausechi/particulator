#ifndef ELECTRON_H
#define ELECTRON_H

#include "behaviors/behavior.h"

enum class ElectronType {
    TAIL,
    HEAD
};

class ElectronBehavior final : public Behavior {
    ElectronType type;

public:
    explicit ElectronBehavior(const ElectronType type) : type(type) {
    }

    void update(std::shared_ptr<Particle> particle, Grid &grid, const UpdateParams &params) override;
};

#endif //ELECTRON_H
