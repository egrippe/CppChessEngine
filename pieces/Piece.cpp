//
// Created by edward on 11.03.17.
//

#include "Piece.h"

Piece::Piece(Color color, Piece::Type type) : color_(color), type_(type) {}

Color Piece::getColor() const {
    return color_;
}

Piece::Type Piece::getType() const {
    return type_;
}
