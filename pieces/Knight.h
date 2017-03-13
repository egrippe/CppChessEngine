//
// Created by edward on 11.03.17.
//

#ifndef CHESS_KNIGHT_H
#define CHESS_KNIGHT_H


#include "../Color.h"
#include "Piece.h"

class Knight : public Piece {
public:
    Knight(Color color) : Piece(color, Piece::Type::KNIGHT) {}

    char latin1Representation() const override {
        return color_ == Color::WHITE ? 'N' : 'n';
    }

    char32_t utfRepresentation() const override {
        return color_ == Color::WHITE ? U'♘' : U'♞';
    }
};


#endif //CHESS_KNIGHT_H
