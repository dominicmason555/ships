#include "Board.h"

Board::Board(std::random_device& rd, int boardSize, bool randomShips)
        : gen(rd()),
          dist(0, boardSize - 1),
          size(boardSize),
          board(boardSize) {
    for (int i = 0; i < size; i++) {
        board[i] = std::vector<tile>(size);
        for (int j = 0; j < size; j++)
            board[i][j] = tile::NONE;
    }
    if (randomShips)
        placeRandomShips();
}

bool Board::checkPosSafe(const Ivec2 pos) const {
    return checkPosOnBoard(pos) && !contactsOrAdjacentToShip(pos);
}

bool Board::checkPosOnBoard(const Ivec2 pos) const {
    return pos.x >= 0 && pos.x < size
           && pos.y >= 0 && pos.y < size;
}

int Board::createShip(const Ivec2 start, const Ivec2 end, bool truncate) {
    int numSecs = 0;
    std::vector<Ship::section> sections;
    Ivec2 dir = end.dirFrom(start);
    if (dir.isZero() || !dir.isStraight()) {
        return 0;
    }
    for (Ivec2 i = start; i != end + dir; i = i + dir) {
        if (checkPosSafe(i)) {
            sections.push_back({i, false});
            numSecs++;
            std::cout << i << std::endl;
        } else {
            if (!truncate)
                numSecs = 0;
            break;
        }
    }
    if (numSecs > 1) {
        ships.emplace_back(std::move(sections));
        return numSecs;
    } else
        return 0;
}

void Board::placeRandomShips() {
    int sections = 0, iters = 0;
    while (sections < board.size() * 2 && iters < 1000) {
        Ivec2 start, end;
        int pos1 = dist(gen);
        if (dist(gen) > board.size() / 2) {
            start = {pos1, dist(gen)};
            end = {pos1, dist(gen)};
        } else {
            start = {dist(gen), pos1};
            end = {dist(gen), pos1};
        }
        sections += createShip(start, end, true);
        iters++;
    }
    std::cout << sections << " sections" << std::endl;
}

bool Board::contactsOrAdjacentToShip(const Ivec2 pos) const {
    return std::any_of(ships.begin(), ships.end(), [pos](const Ship &s) {
        return s.contactsOrAdjacent(pos);
    });
}

int Board::shipsLeft() const {
    return std::count_if(ships.begin(), ships.end(), [](const Ship &s) {
        return !s.sunk();
    });
}

void Board::informMiss(Ivec2 pos) {
    for (Target &t : targets)
        t.miss(pos);
}

bool Board::fireAt(const Ivec2 pos) {
    auto ship = std::find_if(ships.begin(), ships.end(), [pos](Ship &s) {
        return s.hit(pos);
    });
    if (ship == ships.end()) {
        board[pos.x][pos.y] = tile::MISS;
        informMiss(pos);
        return false;
    } else {
        board[pos.x][pos.y] = tile::HIT;
        return true;
    }
}

Ivec2 Board::getRandomTile(bool fresh) {
    Ivec2 pos = {dist(gen), dist(gen)};
    while (fresh && atPos(pos) != tile::NONE) {
        pos = {dist(gen), dist(gen)};
    }
    return pos;
}

tile Board::atPos(Ivec2 pos) const {
    return board[pos.x][pos.y];
}
