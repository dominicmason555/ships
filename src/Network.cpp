#include "Network.h"

void Network::resetNetwork(std::vector<Player> &players) {
    updateBoards ( players );
    for ( Player &p : players ) {
        if ( p.remote ) {

        }
    }
}

void Network::kickOut(Player &p) {

}

void Network::updateBoards(std::vector<Player> &players) {
    for (Player &p : players) {

    }
}

void Network::updateNetwork(std::vector<Player> &players, const Turn t, const int turns) {

}

Turn Network::runRemoteTurn(Player &p) {
    Turn t;
    return t;
}
