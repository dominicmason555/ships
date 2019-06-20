#include <iostream>

#include "TextGame.h"

int main ( int argc, char *argv[] )
{
    std::ios_base::sync_with_stdio ( false );
    std::random_device rd;
    TextGame game(rd);
    game.run();
    return 0;
}
