//
// Created by edward on 11.03.17.
//

#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H


#include "Color.h"
#include "pieces/Piece.h"

#include <string>
#include <ostream>

class Move;

class Board {
public:
    class Square {
    public:
        Square(int row, int col);

        bool operator==(const Square &rhs) const;
        bool operator!=(const Square &rhs) const;

        int getRow() const;
        int getCol() const;

        std::string getMatrixRepresentation()     const;
        std::string getCoordinateRepresentation() const;
    private:
        int row_, col_;
    };

    const static int NUM_ROWS = 8;
    const static int NUM_COLS = 8;

    static bool isValidCoordinates(int row, int col);

    Board();
    Board(Color next_move);
    ~Board();

    Color nextMove() const;
    bool isEmpty(Square square) const;
    bool isOccupied(Square square) const;
    void addPiece(Piece *piece, Square square);
    void removePiece(Square square);
    Piece* getPiece(Square square) const;
    void clear();

    bool isOccupiedBy(Square square, Color color) const;

private:
    Color  next_move_;
    Piece* board_state_[NUM_ROWS][NUM_COLS] = {};
};

std::ostream &operator<<(std::ostream &os, const Board &board);
Board& operator>>(std::istream &is, Board &cb);


#endif //CHESS_BOARD_H
