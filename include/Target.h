#pragma once

#include <vector>
#include <algorithm>

#include "Ivec2.h"

class Target {
public:
    std::vector<Ivec2> hits;
    std::vector<Ivec2> misses;
    bool headExplored, tailExplored;
    int boardSize;
    enum class Dir {
        UNKNOWN, HORIZ, VERT
    };
    Dir dir;

    Target(Ivec2 start, int size);

    void hit(Ivec2 pos);

    Ivec2 getEndPos(bool top);

    Ivec2 getTargetPos();

    void miss(Ivec2 pos);

    bool isExplored() const;
};
