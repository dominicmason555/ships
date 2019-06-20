#pragma once

#include <string>
#include <sstream>

#include "Ivec2.h"

class Turn {
public:
    int player;
    int victim;
    Ivec2 pos;
    bool hit;
    bool out;

    friend std::istream &operator>>(std::istream &in, Turn &t);

    friend std::ostream &operator<<(std::ostream &outStream, const Turn &t);

    std::string explain() const;
};
