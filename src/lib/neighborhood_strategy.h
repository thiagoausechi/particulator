#ifndef NEIGHBORHOOD_STRATEGY_H
#define NEIGHBORHOOD_STRATEGY_H

#include <vector>
#include <unordered_map>
#include "grid/grid.h"

enum Direction {
	TOP,
	TOP_RIGHT,
	RIGHT,
	BOTTOM_RIGHT,
	BOTTOM,
	BOTTOM_LEFT,
	LEFT,
	TOP_LEFT
};

class NeighborhoodStrategy {
public:
	virtual ~NeighborhoodStrategy() = default;

	[[nodiscard]] virtual std::vector<int> getNeighbors(int index, const Grid &grid) const = 0;

protected:
	[[nodiscard]] std::vector<int> getOffsets(const Grid &grid, const std::vector<Direction> &directions) const {
		const std::unordered_map<Direction, int> directionOffsets = {
			{TOP, -grid.getWidth()},
			{TOP_RIGHT, -grid.getWidth() + 1},
			{RIGHT, 1},
			{BOTTOM_RIGHT, grid.getWidth() + 1},
			{BOTTOM, grid.getWidth()},
			{BOTTOM_LEFT, grid.getWidth() - 1},
			{LEFT, -1},
			{TOP_LEFT, -grid.getWidth() - 1}
		};
		std::vector<int> offsets;
		offsets.reserve(directions.size());
		for (const auto &direction: directions)
			offsets.push_back(directionOffsets.at(direction));
		return offsets;
	}
};

/**
 * The Moore neighborhood strategy considers all eight possible neighbors
 * surrounding a central cell in a grid. These neighbors [x] are located at the 
 * top, top-right, right, bottom-right, bottom, bottom-left, left, and top-left 
 * positions relative to the central cell [i].
 * 
 * [x][x][x]
 * [x][i][x]
 * [x][x][x]
 */
class MooreNeighborhoodStrategy final : public NeighborhoodStrategy {
public:
	[[nodiscard]] std::vector<int> getNeighbors(const int index, const Grid &grid) const override {
		const auto offsets = getOffsets(
			grid, {TOP, TOP_RIGHT, RIGHT, BOTTOM_RIGHT, BOTTOM, BOTTOM_LEFT, LEFT, TOP_LEFT});
		std::vector<int> neighbors;
		neighbors.reserve(offsets.size());
		for (const auto &offset: offsets)
			neighbors.push_back(index + offset);
		return neighbors;
	}
};

/**
 * The Von Neumann neighborhood strategy includes the cells that are directly
 * adjacent to the central cell [i] in the four cardinal directions:
 * up, down, left, and right.
 *
 * [ ][x][ ]
 * [x][i][x]
 * [ ][x][ ]
 */
class VonNeumannNeighborhoodStrategy final : public NeighborhoodStrategy {
public:
	[[nodiscard]] std::vector<int> getNeighbors(const int index, const Grid &grid) const override {
		const auto offsets = getOffsets(grid, {TOP, RIGHT, BOTTOM, LEFT});
		std::vector<int> neighbors;
		neighbors.reserve(offsets.size());
		for (const auto &offset: offsets)
			neighbors.push_back(index + offset);
		return neighbors;
	}
};

#endif //NEIGHBORHOOD_STRATEGY_H
