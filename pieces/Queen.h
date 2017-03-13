//
// Created by edward on 11.03.17.
//

#ifndef CHESS_QUEEN_H
#define CHESS_QUEEN_H


#include "../Color.h"
#include "Piece.h"

class Queen : public Piece {
public:
    Queen(Color color) : Piece(color, Piece::Type::QUEEN) {}

    char latin1Representation() const override {
        return color_ == Color::WHITE ?  'Q' :  'q';
    }

    char32_t utfRepresentation() const override {
        return color_ == Color::WHITE ? U'♕' : U'♛';
    }
};


#endif //CHESS_QUEEN_H
