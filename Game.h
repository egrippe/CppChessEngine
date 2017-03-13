//
// Created by Edward Grippe on 12.03.17.
//

#ifndef CHESS_GAME_H
#define CHESS_GAME_H


#include "Board.h"
#include "Move.h"

class Game {
public:
    void run();
private:
    enum Type { ONE_PLAYER, TWO_PLAYER };

    Board board_;
    Type game_type_;

    void printWelcomeMessage();
    void selectGameType();
    void initializeBoard();
    void startGame();

    Move getMoveFromPlayer(Color player_color);
};


#endif //CHESS_GAME_H
