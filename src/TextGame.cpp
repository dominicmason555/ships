#include "TextGame.h"

TextGame::TextGame(std::random_device &rd) {
    int humans, robots;
    std::cout << "Enter the number of human players: ";
    std::cin >> humans;
    std::cout << "Enter the number of robot players: ";
    std::cin >> robots;
    for ( int i = 1; i <= humans; i++ ) {
        int size;
        std::cout << "Enter the board size for human player " << i << ": ";
        std::cin >> size;
        if ( size )
            players.emplace_back (rd, true, i, size );
    }
    for ( int i = humans + 1; i <= humans + robots; i++ ) {
        int size;
        std::cout << "Enter the board size for robot player " << i << ": ";
        std::cin >> size;
        if ( size )
            players.emplace_back (rd, false, i, size );
    }
    if ( players.size() < 2 )
        exit ( 0 );
    for ( auto &p : players )
        p.initialiseDanger ( players );
}

int TextGame::playersLeft() const {
    return std::count_if(players.begin(), players.end(), [](const Player &p) {
        return !p.out;
    });
}

std::string TextGame::draw(const Board &b) const {
    std::ostringstream outBuf(std::ios_base::ate);
    outBuf << b.size << " x " << b.size << " board:\n";
    outBuf << "  ";
    for (int i = 0; i < b.board.size(); i++) {
        outBuf << std::setw(4) << i;
    }
    outBuf << "\n";
    for (int i = 0; i < b.board.size(); i++) {
        outBuf << "   ";
        for (int k = 0; k < b.board.size(); k++) {
            outBuf << "+---";
        }
        outBuf << "+\n";
        outBuf << std::setw(2) << i << " ";
        for (int j = 0; j < b.board.size(); j++) {
            outBuf << "|";
            switch (b.board[i][j]) {
                case tile::NONE:
                    outBuf << " ~ ";
                    break;
                case tile::MISS:
                    outBuf << "\\ /";
                    break;
                case tile::HIT:
                    outBuf << " X ";
                    break;
            }
        }
        outBuf << "|\n";
    }
    outBuf << "   ";
    for (int i = 0; i < b.board.size(); i++) {
        outBuf << "+---";
    }
    outBuf << "+\n";
    return outBuf.str();
}

int TextGame::getVictimId(const Player &p) {
    if (playersLeft() > 2) {
        while (true) {
            int victim;
            std::cout << "Player " << p.id << ", enter the player id to attack: ";
            std::cin >> victim;
            if (victim > 0 && victim <= players.size() && victim != p.id)
                return victim;
        }
    } else {
        auto victim = std::find_if(players.begin(), players.end(), [&p](const Player &p2) {
            return !p2.out && p2.id != p.id;
        });
        if (victim != players.end())
            return victim->id;
        else {
            endGame();
            return p.id;
        }
    }
}

void TextGame::endGame() {
    std::cout << "Game Over!" << std::endl;
    running = false;
    auto winner = std::find_if(players.begin(), players.end(), [](const Player &p) {
        return !p.out;
    });
    if (winner != players.end())
        std::cout << "Winner is player " << winner->id << std::endl;
    std::cout << "Won in " << turns << " turns" << std::endl;
}

Ivec2 TextGame::aim(const int victim) const {
    while (true) {
        Ivec2 pos;
        std::cout << "Enter position to fire at (x y): ";
        std::cin >> pos;
        if (players[victim].board.checkPosOnBoard(pos))
            return pos;
    }
}

void TextGame::kickOut(Player &p) {
    p.out = true;
    std::cout << "Player " << p.id << " is out!" << std::endl;
    if (p.remote)
        net.kickOut(p);
    if (playersLeft() <= 1)
        endGame();
}

Turn TextGame::runTurn(Player &p) {
    Turn t;
    t.player = p.id;
    std::cout << "\nPlayer " << p.id << "'s Turn:" << std::endl;
    for (Player &p : players) {
        std::cout << "Player " << p.id << " has " << p.board.shipsLeft() << " ships remaining" << std::endl;
    }
    t.victim = getVictimId(p);
    int victim = t.victim - 1;
    std::cout << "Targeting player " << t.victim << ":" << std::endl;
    std::cout << draw(players[victim].board);
    t.pos = aim(victim);
    t.hit = players[victim].fireAt(t.pos, p.id);
    if (t.hit)
        std::cout << "Ship Hit!" << std::endl;
    else
        std::cout << "Missed" << std::endl;
    std::cout << draw(players[victim].board);
    if (players[victim].board.shipsLeft() == 0) {
        t.out = true;
        kickOut(players[victim]);
    } else
        t.out = false;
    std::cout << std::endl;
    return t;
}

Turn TextGame::runRoboTurn(Player &p) {
    Turn t;
    t.player = p.id;
    std::cout << "\nRobot player " << p.id << "'s Turn:" << std::endl;
    t.victim = p.chooseVictim();
    int victim = t.victim - 1;
    std::cout << "Target acqurired: player " << t.victim << std::endl;
    t.pos = p.getAim(players[victim]);
    std::cout << "Firing at: " << t.pos << std::endl;
    t.hit = players[victim].fireAt(t.pos, p.id);
    if (t.hit)
        std::cout << "Ship Hit!" << std::endl;
    else
        std::cout << "Missed" << std::endl;
    std::cout << draw(players[victim].board);
    if (players[victim].board.shipsLeft() == 0) {
        t.out = true;
        kickOut(players[victim]);
    } else
        t.out = false;
    std::cout << std::endl;
    return t;
}

void TextGame::updatePlayers(const Turn t) {
    for (Player &p : players) {
        p.update(t);
    }
    if (networked) {
        net.updateNetwork(players, t, turns);
    }
}

void TextGame::run() {
    if (networked)
        net.resetNetwork(players);
    while (running) {
        for (Player &p : players) {
            if (running && !p.out) {
                std::cout << "Turn " << ++turns << ":" << std::endl;
                if (p.remote)
                    updatePlayers(net.runRemoteTurn(p));
                else if (p.human)
                    updatePlayers(runTurn(p));
                else
                    updatePlayers(runRoboTurn(p));
            }
        }
    }
}
