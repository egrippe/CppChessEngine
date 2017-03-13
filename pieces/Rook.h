//
// Created by edward on 11.03.17.
//

#ifndef CHESS_ROOK_H
#define CHESS_ROOK_H


#include "../Color.h"
#include "Piece.h"

class Rook : public Piece {
public:
    Rook(Color color) : Piece(color, Piece::Type::ROOK) {}

    char latin1Representation() const override {
        return color_ == Color::WHITE ? 'R' : 'r';
    }

    char32_t utfRepresentation() const override {
        return color_ == Color::WHITE ? U'♖' : U'♜';
    }
};


#endif //CHESS_ROOK_H
