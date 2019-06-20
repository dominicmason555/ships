#include "Ivec2.h"

int x, y;

std::vector<Ivec2> Ivec2::neighbours() const {
    return {
            {x - 1, y - 1},
            {x,     y - 1},
            {x + 1, y - 1},
            {x - 1, y},
            {x + 1, y},
            {x - 1, y + 1},
            {x,     y + 1},
            {x + 1, y + 1}
    };
}

std::vector<Ivec2> Ivec2::connected() const {
    return {
            {x,     y - 1},
            {x,     y + 1},
            {x - 1, y},
            {x + 1, y}
    };
}

bool Ivec2::isAdjacent(const Ivec2 pos) const {
    std::vector<Ivec2> adj = neighbours();
    return find(adj.begin(), adj.end(), pos) != adj.end();
}

bool Ivec2::isConnected(const Ivec2 pos) const {
    std::vector<Ivec2> con = connected();
    return find(con.begin(), con.end(), pos) != con.end();
}

bool Ivec2::isWithin(int size) const {
    return x < size && y < size;
}

Ivec2 Ivec2::operator+(const Ivec2 other) const {
    return Ivec2{x + other.x, y + other.y};
}

Ivec2 Ivec2::operator-(const Ivec2 other) const {
    return Ivec2{x - other.x, y - other.y};
}

bool Ivec2::operator==(const Ivec2 other) const {
    return x == other.x && y == other.y;
}

bool Ivec2::operator!=(const Ivec2 other) const {
    return x != other.x || y != other.y;
}

Ivec2 Ivec2::sign() const {
    return {((0 < x) - (x < 0)), ((0 < y) - (y < 0))};
}

Ivec2 Ivec2::dirFrom(const Ivec2 other) const {
    return (*this - other).sign();
}

bool Ivec2::isZero() const {
    return x == 0 && y == 0;
}

bool Ivec2::isStraight() const {
    return !(x && y);
}

std::istream &operator>>(std::istream &in, Ivec2 &out) {
    in >> out.y;
    in >> out.x;
    return in;
}

std::ostream &operator<<(std::ostream &out, const Ivec2 &vec) {
    out << "(" << vec.y << "," << vec.x << ")";
    return out;
}
