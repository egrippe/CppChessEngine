#include "Color.h"
#include "pieces/Piece.h"
#include "pieces/Queen.h"
#include "pieces/Rook.h"
#include "Board.h"
#include "Move.h"
#include "Chess.h"
#include "pieces/King.h"
#include "Game.h"

#include <iostream>
#include <codecvt>
#include <locale>  //wstring_convert
#include <sstream>

using namespace std;

int main() {

    std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> conv32;

    Board board = Board();

    stringstream ss;
    ss << "........" << endl;
    ss << "........" << endl;
    ss << "........" << endl;
    ss << ".r.r...." << endl;
    ss << "r.P....." << endl;
    ss << "........" << endl;
    ss << "........" << endl;
    ss << "........" << endl;

    ss >> board;


    Game game;
    game.run();

    std::vector<Move> moves = Chess::findPossibleMoves(&board, Board::Square(1,1));

    return 0;
}