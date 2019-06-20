#include "Turn.h"

std::istream &operator>>(std::istream &in, Turn &t) {
    in >> t.player;
    in >> t.victim;
    in >> t.pos;
    in >> t.hit;
    in >> t.out;
    return in;
}

std::ostream &operator<<(std::ostream &outStream, const Turn &t) {
    outStream << t.player << " " << t.victim << " " << t.pos.y << " " << t.pos.x << " " << t.hit << " " << t.out;
    return outStream;
}

std::string Turn::explain() const {
    std::ostringstream out_str(std::ios_base::ate);
    out_str << "Player " << player;
    out_str << " fired at player " << victim;
    out_str << " at " << pos << " which ";
    out_str << (hit ? "hit!" : "missed.");
    return out_str.str();
}
