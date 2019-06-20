#include "Target.h"

void Target::hit(Ivec2 pos) {
    hits.emplace_back(pos);
    if (dir == Dir::UNKNOWN) {
        if (hits[1].dirFrom(hits[0]).y == 0)
            dir = Dir::HORIZ;
        else
            dir = Dir::VERT;
    }
    if (dir == Dir::HORIZ)
        std::sort(hits.begin(), hits.end(), [](Ivec2 lhs, Ivec2 rhs) {
            return lhs.x < rhs.x;
        });
    else
        std::sort(hits.begin(), hits.end(), [](Ivec2 lhs, Ivec2 rhs) {
            return lhs.y < rhs.y;
        });
}

Ivec2 Target::getEndPos(bool top) {
    Ivec2 add;
    if (dir == Dir::HORIZ)
        add = {1, 0};
    else
        add = {0, 1};
    if (top)
        return hits[hits.size() - 1] + add;
    else
        return hits[0] - add;
}

Ivec2 Target::getTargetPos() {
    return getEndPos(!headExplored);
}

void Target::miss(Ivec2 pos) {
    misses.emplace_back(pos);
}

bool Target::isExplored() const {
    return headExplored && tailExplored;
}

Target::Target(Ivec2 start, int size)
        : headExplored(false),
          tailExplored(false),
          boardSize(size),
          dir(Dir::UNKNOWN) {
    hits.emplace_back(start);
}
