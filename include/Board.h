#pragma once

#include <vector>
#include <random>

#include "Ivec2.h"
#include "Ship.h"
#include "Target.h"

enum class tile {
    NONE, MISS, HIT
};


class Board {
public:
    std::mt19937 gen;
    std::uniform_int_distribution<> dist;
    int size;
    std::vector<Ship> ships;
    std::vector<std::vector<tile>> board;
    std::vector<Target> targets;

    explicit Board(std::random_device& rd, int boardSize = 10, bool randomShips = true);

    bool checkPosSafe(const Ivec2 pos) const;

    bool checkPosOnBoard(const Ivec2 pos) const;

    int createShip(const Ivec2 start, const Ivec2 end, bool truncate = false);

    void placeRandomShips();

    bool contactsOrAdjacentToShip(const Ivec2 pos) const;

    int shipsLeft() const;

    void informMiss(Ivec2 pos);

    bool fireAt(const Ivec2 pos);

    Ivec2 getRandomTile(bool fresh = true);

    tile atPos(Ivec2 pos) const;
};
