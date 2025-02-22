#ifndef MOVES_DOWN_H
#define MOVES_DOWN_H

#include "behaviors/behavior.h"

class MovesDownBehavior : public Behavior {
public:
    MovesDownBehavior(const float maxSpeed, const float acceleration) : maxSpeed(maxSpeed), acceleration(acceleration),
                                                                        velocity(0) {
    }

    void update(std::shared_ptr<Particle> particle, Grid &grid, const UpdateParams &params) override {
        const auto index = particle->getIndex();

        this->updateVelocity();
        const auto updateCount = this->getUpdateCount();

        for (int v = 0; v < updateCount; v++) {
            this->step(particle, grid);

            if (const auto newIndex = particle->getIndex(); newIndex != index) {
                grid.onModified(index);
                grid.onModified(newIndex);
            } else {
                this->resetVelocity();
                break;
            }
        }
    }

protected:
    float maxSpeed;
    float acceleration;
    float velocity;

    void resetVelocity() {
        this->velocity = 0;
    }

    void updateVelocity() {
        this->velocity = this->nextVelocity();
    }

    [[nodiscard]] float nextVelocity() const {
        if (this->maxSpeed == 0)
            return 0;

        auto newVelocity = this->velocity + this->acceleration;
        if (std::abs(newVelocity) > this->maxSpeed)
            newVelocity = std::copysign(maxSpeed, newVelocity);
        return newVelocity;
    }

    [[nodiscard]] int getUpdateCount() const {
        const auto abs = std::abs(this->velocity);
        const auto floored = std::floor(abs);
        const auto mod = abs - floored;
        const auto offset = randomInRange(0, 100) < static_cast<int>(mod * 100) ? 1 : 0;

        return static_cast<int>(floored) + offset;
    }

    [[nodiscard]] bool canPassThrough(const std::shared_ptr<Particle> &particle) const {
        if (!particle)
            return false;
        const auto properties = particle->getProperties();
        return properties.empty || !properties.solid;
    }

    [[nodiscard]] auto possibleMoves(const Grid &grid, const int index) const {
        const int nextDelta = std::copysign(grid.getWidth(), this->velocity);
        const auto
                nextVertical = index + nextDelta,
                nextVerticalLeft = nextVertical - 1,
                nextVerticalRight = nextVertical + 1;

        const auto column = nextVertical % grid.getWidth();

        std::vector<int>
                moves = {},
                weights = {};

        if (this->canPassThrough(grid.particleAt(nextVertical))) {
            moves.push_back(nextVertical);
            weights.push_back(2);
        } else {
            if (this->canPassThrough(grid.particleAt(nextVerticalLeft))
                && nextVerticalLeft % grid.getWidth() < column) {
                moves.push_back(nextVerticalLeft);
                weights.push_back(1);
            }

            if (this->canPassThrough(grid.particleAt(nextVerticalRight))
                && nextVerticalRight % grid.getWidth() > column) {
                moves.push_back(nextVerticalRight);
                weights.push_back(1);
            }
        }

        return std::pair{moves, weights};
    }

    void step(const std::shared_ptr<Particle> &particle, Grid &grid) {
        const auto index = particle->getIndex();
        if (grid.isEmpty(index)) {
            this->resetVelocity();
            return;
        }

        const auto [moves, weights] = this->possibleMoves(grid, index);
        if (moves.empty()) {
            this->resetVelocity();
            return;
        }

        const auto choice = choose(moves, weights);
        grid.swap(index, choice);
    }
};

#endif //MOVES_DOWN_H
