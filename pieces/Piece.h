//
// Created by edward on 11.03.17.
//

#ifndef CHESS_PIECE_H
#define CHESS_PIECE_H


#include "../Color.h"

class Piece {
public:
    enum class Type {
        KING,
        QUEEN,
        ROOK,
        BISHOP,
        KNIGHT,
        PAWN
    };

    Piece(Color color, Type type);

    Color getColor() const;
    Type  getType()  const;

    virtual char latin1Representation() const = 0;
    virtual char32_t utfRepresentation() const = 0;
protected:
    Color color_;
    Type  type_;
};


#endif //CHESS_PIECE_H
