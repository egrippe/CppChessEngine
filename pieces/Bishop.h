//
// Created by edward on 11.03.17.
//

#ifndef CHESS_BISHOP_H
#define CHESS_BISHOP_H


#include "../Color.h"
#include "Piece.h"

class Bishop : public Piece {
public:
    Bishop(Color color) : Piece(color, Piece::Type::BISHOP) {}

    char latin1Representation() const override {
        return color_ == Color::WHITE ? 'B' : 'b';
    }

    char32_t utfRepresentation() const override {
        return color_ == Color::WHITE ? U'♗' : U'♝';
    }
};


#endif //CHESS_BISHOP_H
