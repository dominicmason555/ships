#include "Ship.h"

bool Ship::sunk() const {
    return std::all_of(sections.begin(), sections.end(), [](const section &s) {
        return s.sunk;
    });
}

bool Ship::contacts(const Ivec2 pos) const {
    return std::any_of(sections.begin(), sections.end(), [pos](const section &s) {
        return s.pos == pos;
    });
}

bool Ship::contactsOrAdjacent(const Ivec2 pos) const {
    return std::any_of(sections.begin(), sections.end(), [pos](const section &s) {
        return s.pos == pos || s.pos.isAdjacent(pos);
    });
}

bool Ship::hit(const Ivec2 pos) {
    auto sec = std::find_if(sections.begin(), sections.end(), [pos](const section &s) {
        return s.pos == pos;
    });
    if (sec == sections.end())
        return false;
    else {
        sec->sunk = true;
        return true;
    }
}

Ship::Ship(std::vector<Ship::section> secs)
        : sections(secs) {}
