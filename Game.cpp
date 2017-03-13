//
// Created by edward on 12.03.17.
//

#include "Chess.h"
#include "Game.h"
#include "Move.h"

#include <iostream>
#include <sstream>
#include <limits>
#include <regex>

void Game::run() {

    initializeBoard();

    printWelcomeMessage();
    selectGameType();

    startGame();

}

void Game::printWelcomeMessage() {
    std::cout << "********************************************" << std::endl;
    std::cout << "**                Chess Game              **" << std::endl;
    std::cout << "********************************************" << std::endl;
    std::cout << std::endl;
}

void Game::selectGameType() {
    std::cout << "** Select Game Type *******" << std::endl;
    std::cout << "** Type 1 for ONE PLAYER **" << std::endl;
    std::cout << "** Type 1 for TWO PLAYER **" << std::endl;

    bool done = false;
    while (!done) {

        char cmd;
        std::cin >> cmd;
        switch (cmd) {
            case '1': {
                game_type_ = Game::Type::ONE_PLAYER;
                done = true;
                break;
            }
            case '2': {
                game_type_ = Game::Type::TWO_PLAYER;
                done = true;
                break;
            }
            default: {
                std::cout << "Command: '" << cmd << "' not recognized." << std::endl;
                std::cout << "Try again." << std::endl;
            }
        }

        // clear crap in cin buffer
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

void Game::initializeBoard() {

    std::stringstream ss;

    ss << "rnbqkbnr" << std::endl;
    ss << "pppppppp" << std::endl;
    ss << "........" << std::endl;
    ss << "........" << std::endl;
    ss << "........" << std::endl;
    ss << "........" << std::endl;
    ss << "PPPPPPPP" << std::endl;
    ss << "RNBQKBNR" << std::endl;

    ss >> board_;
}

void Game::startGame() {

    std::cout << "** Starting Game **" << std::endl;

    bool done = false;
    while (!done) {

        // print board
        std::cout << board_ << std::endl;

        // let the player make a move
        Move move = getMoveFromPlayer(Color::WHITE);
        /*
        board_.makeMove(getMoveFromPlayer());
        std::cout << move << std::endl;
        */

    }


}

Move Game::getMoveFromPlayer(Color player_color) {

    // regex for a standard move command
    std::regex std_regex("[a-hA-H][1-8][ -][a-hA-H][1-8]( \\([QRNR]\\))? *");
    // regex for a pawn promotion command
    std::regex pro_regex("[a-hA-H][1-8][ -][a-hA-H][1-8]( \\([QRNR]\\)) *");

    while (true) {

        // read player input from cin
        std::string cmd;
        std::getline(std::cin, cmd);

        // check that move command is in valid form
        if (!regex_match(cmd, std_regex)) {
            std::cout << "Wrong format of move command. Try again." << std::endl;
            continue;
        }

        // parse the move command
        int from_row = 7 - (toupper(cmd[1]) - '1');
        int from_col = toupper(cmd[0]) - 'A';
        int to_row   = 7 - (toupper(cmd[4]) - '1');
        int to_col   = toupper(cmd[3]) - 'A';

        Board::Square from_square(from_row, from_col);
        Board::Square to_square(to_row, to_col);

        if (board_.isEmpty(from_square)) {
            std::cout << "There is no piece at the given square. Try again." << std::endl;
            continue;
        }
        else if (!board_.isOccupiedBy(from_square, player_color)) {
            std::cout << "You have to move our own piece. Try again." << std::endl;
        }
        else {
            Move move = Move(from_square, to_square);
            if (Chess::isValidMove(&board_, move)) {
                return move;
            }
            else {
                std::cout << "Invalid move. Try again." << std::endl;
            }
        }
    }
}
