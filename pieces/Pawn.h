//
// Created by edward on 11.03.17.
//

#ifndef CHESS_PAWN_H
#define CHESS_PAWN_H


#include "../Color.h"
#include "Piece.h"

class Pawn : public Piece{
public:
    Pawn(Color color) : Piece(color, Piece::Type::PAWN) {}

    char latin1Representation() const override {
        return color_ == Color::WHITE ? 'P' : 'p';
    }

    char32_t utfRepresentation() const override {
        return color_ == Color::WHITE ? U'♙' : U'♟';
    }
};


#endif //CHESS_PAWN_H
