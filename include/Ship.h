#pragma once

#include <algorithm>

#include "Ivec2.h"

class Ship {
public:
    struct section {
        Ivec2 pos;
        bool sunk;
    };
    std::vector<section> sections;

    Ship(std::vector<section> secs);

    bool sunk() const;

    bool contacts(const Ivec2 pos) const;

    bool contactsOrAdjacent(const Ivec2 pos) const;

    bool hit(const Ivec2 pos);
};
