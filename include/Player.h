#pragma once

#include <string>
#include <map>
#include <random>

#include "Board.h"
#include "Turn.h"

class Player {
public:
    bool human;
    bool out = false;
    bool remote = false;
    int id;
    int turns = 0;
    std::string name;
    std::mt19937 gen;
    Board board;
    struct stat {
        int danger;
        int damage;
        int accuracy;
    };
    std::map<int, stat> stats;
    std::vector<int> playerIDs;

    Player(std::random_device &rd, bool h, int number, int boardSize);

    void initialiseDanger(const std::vector<Player> &players);

    void update(Turn t);

    bool fireAt(const Ivec2 pos, int id);

    void removeStat(int id);

    int mostDangerousPlayerID() const;

    int randomPlayerId();

    bool dangerEqual() const;

    int chooseVictim();

    Ivec2 getAim(Player &p) const;
};
