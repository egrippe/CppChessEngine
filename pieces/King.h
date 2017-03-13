//
// Created by edward on 11.03.17.
//

#ifndef CHESS_KING_H
#define CHESS_KING_H

#include "../Color.h"
#include "Piece.h"

class King : public Piece {
public:
    King(Color color) : Piece(color, Piece::Type::KING) {}

    char latin1Representation() const override {
        return color_ == Color ::WHITE?  'K' :  'k';
    }

    char32_t utfRepresentation() const override {
        return color_ == Color::WHITE ? U'♔' : U'♚';
    }
};


#endif //CHESS_KING_H
