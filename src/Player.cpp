#include "Player.h"

Player::Player(std::random_device &rd, bool h, int number, int boardSize)
        : human(h),
          id(number),
          gen(rd()),
          board(rd, boardSize) {}

void Player::initialiseDanger(const std::vector<Player> &players) {
    for (auto &p : players) {
        if (p.id != id) {
            playerIDs.push_back(p.id);
            stats[p.id] = {0, 0, 0};
        }
    }
}

void Player::update(Turn t) {
    turns++;
    if (t.player != id && t.victim != id) {
        if (t.hit) {
            stats[t.player].danger += 2;
            stats[t.player].accuracy++;
            stats[t.victim].damage++;
        } else {
            stats[t.player].accuracy--;
            stats[t.player].danger--;
        }
        if (t.out)
            stats[t.player].danger += 10;
    }
    if (t.out)
        removeStat(t.victim);
    for (auto &s : stats) {
        s.second.danger--;
    }
}

bool Player::fireAt(const Ivec2 pos, int id) {
    bool hit = board.fireAt(pos);
    if (hit)
        stats[id].danger += 10;
    else
        stats[id].danger += 5;
    return hit;
}

void Player::removeStat(int id) {
    stats.erase(id);
    playerIDs.erase(std::remove(playerIDs.begin(), playerIDs.end(), id), playerIDs.end());
}

int Player::mostDangerousPlayerID() const {
    return std::max_element(stats.begin(), stats.end(),
                            [](const std::pair<int, stat> &s1, const std::pair<int, stat> &s2) {
                                return s1.second.danger < s2.second.danger;
                            })->first;
}

int Player::randomPlayerId() {
    std::uniform_int_distribution<int> dist(0, playerIDs.size() - 1);
    return playerIDs[dist(gen)];
}

bool Player::dangerEqual() const {
    return (std::adjacent_find(stats.begin(), stats.end(),
                               [](const std::pair<int, stat> &s1, const std::pair<int, stat> &s2) {
                                   return s1.second.danger != s2.second.danger;
                               }) == stats.end());
}

int Player::chooseVictim() {
    if (dangerEqual())
        return randomPlayerId();
    else
        return mostDangerousPlayerID();
}

Ivec2 Player::getAim(Player &p) const {
    return p.board.getRandomTile();
}
