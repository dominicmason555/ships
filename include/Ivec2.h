#pragma once

#include <iostream>
#include <vector>

class Ivec2
{
public:
    int x, y;

    std::vector<Ivec2> neighbours () const;
    std::vector<Ivec2> connected () const;
    bool isAdjacent ( const Ivec2 pos ) const;
    bool isConnected ( const Ivec2 pos ) const;
    bool isWithin (int size) const;
    Ivec2 operator+ ( const Ivec2 other ) const;
    Ivec2 operator- ( const Ivec2 other ) const;
    bool operator== ( const Ivec2 other ) const;
    bool operator!= ( const Ivec2 other ) const;
    Ivec2 sign() const;
    Ivec2 dirFrom ( const Ivec2 other ) const;
    bool isZero() const;
    bool isStraight() const;
    friend std::istream &operator>> ( std::istream &in, Ivec2 &out );
    friend std::ostream &operator<< ( std::ostream &out, const Ivec2 &vec );
};

