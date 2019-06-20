#pragma once

#include <vector>
#include <iostream>
#include <iomanip>
#include <random>

#include "Network.h"
#include "Player.h"
#include "Turn.h"
#include "Ivec2.h"

class TextGame {
public:
    int turns = 0;
    bool networked = false;
    bool running = true;
    Network net;
    std::vector<Player> players;

    TextGame(std::random_device &rd);

    int playersLeft() const;

    std::string draw(const Board &b) const;

    int getVictimId(const Player &p);

    void endGame();

    Ivec2 aim(const int victim) const;

    void kickOut(Player &p);

    Turn runTurn(Player &p);

    Turn runRoboTurn(Player &p);

    void updatePlayers(const Turn t);

    void run();
};

