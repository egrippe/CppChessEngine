//
// Created by edward on 11.03.17.
//

#ifndef CHESS_MOVE_H
#define CHESS_MOVE_H


#include "Board.h"

class Move {
public:

    enum class Type {
        CAPTURING,
        NON_CAPTURING,
        NOT_SET,
        INVALID
    };

    Move(Board::Square from_, Board::Square to_) : from_(from_), to_(to_), type_(Type::NOT_SET) {}
    Move(Board::Square from, Board::Square to, Type type) : from_(from), to_(to), type_(type) {};

    bool operator==(const Move &rhs) const {
        return from_ == rhs.from_ &&
               to_ == rhs.to_;
    }

    bool operator!=(const Move &rhs) const {
        return !(rhs == *this);
    }

    Board::Square getFrom() const { return from_; }
    Board::Square getTo() const { return to_; }

    Type getType() const { return type_; }

private:
    Board::Square from_;
    Board::Square to_;
    Type type_;
};



#endif //CHESS_MOVE_H
