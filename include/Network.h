#pragma once

#include <vector>

#include "Player.h"

class Network {
public:
    void resetNetwork(std::vector<Player> &players);

    void kickOut(Player &p);

    void updateBoards(std::vector<Player> &players);

    void updateNetwork(std::vector<Player> &players, const Turn t, const int turns);

    Turn runRemoteTurn(Player &p);
};
