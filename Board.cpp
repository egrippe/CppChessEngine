//
// Created by Edward Grippe on 11.03.17.
//

#include "Board.h"
#include "pieces/King.h"
#include "pieces/Rook.h"
#include "pieces/Queen.h"
#include "pieces/Bishop.h"
#include "pieces/Knight.h"
#include "pieces/Pawn.h"
#include "Chess.h"

#include <sstream>
#include <cassert>
#include <iostream>
#include <codecvt>
#include <locale>
#include <vector>

Board::Board() : next_move_(Color::WHITE) {}

Board::Board(Color next_move) : next_move_(next_move) {}

Board::~Board() {
    clear();
}

Color Board::nextMove() const {
    return next_move_;
}

bool Board::isEmpty(Square square) const {
    return board_state_[square.getRow()][square.getCol()] == nullptr;
}

bool Board::isOccupied(Square square) const {
    return !isEmpty(square);
}

void Board::addPiece(Piece *piece, Square square) {
    assert(isEmpty(square));
    board_state_[square.getRow()][square.getCol()] = piece;
}

void Board::removePiece(Square square) {
    delete(board_state_[square.getRow()][square.getCol()]);
    board_state_[square.getRow()][square.getCol()] = nullptr;
}

Piece *Board::getPiece(Square square) const {
    return board_state_[square.getRow()][square.getCol()];
}

bool Board::isValidCoordinates(int row, int col) {
    return (row >= 0 && row < Board::NUM_ROWS && col >= 0 && col < Board::NUM_COLS);
}

void Board::clear() {
    for (int i = 0; i < NUM_ROWS; ++i) {
        for (int j = 0; j < NUM_COLS; ++j) {
            delete(board_state_[i][j]);
        }
    }
}

bool Board::isOccupiedBy(Board::Square square, Color color) const {
    if (isEmpty(square)) {
        return false;
    }
    else return getPiece(square)->getColor() == color;
}

std::ostream &operator<<(std::ostream &os, const Board &board) {
    std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> conv32;
    for (int i = 0; i < Board::NUM_ROWS; ++i) {
        os << (Board::NUM_ROWS - i) << '|';
        for (int j = 0; j < Board::NUM_COLS; ++j) {
            Board::Square square = Board::Square(i,j);
            if (board.isEmpty(square)) {
                os << "\u2B1D";
            }
            else {
                os << conv32.to_bytes(board.getPiece(square)->utfRepresentation());
            }
            os << ' ';
        }
        os << std::endl;
    }
    std::cout << "  A\u0305 B\u0305 C\u0305 D\u0305 E\u0305 F\u0305 G\u0305 H\u0305" << std::endl;
    return os;
}

Board &operator>>(std::istream &is, Board &board) {
    board.clear();
    std::string line;
    for (int i = 0; i < Board::NUM_ROWS; ++i) {
        std::getline(is, line);
        for (int j = 0; j < Board::NUM_COLS; ++j) {
            Board::Square square = Board::Square(i,j);
            Color color = isupper(line[j]) ? Color::WHITE : Color::BLACK;
            switch (toupper(line[j])) {
                case 'K': board.addPiece(new King(color),   square); break;
                case 'Q': board.addPiece(new Queen(color),  square); break;
                case 'R': board.addPiece(new Rook(color),   square); break;
                case 'B': board.addPiece(new Bishop(color), square); break;
                case 'N': board.addPiece(new Knight(color), square); break;
                case 'P': board.addPiece(new Pawn(color),   square); break;
                case '.': break;
                default: std::cerr << "chess piece: " << line[j] << " not recognized" << std::endl;
            }
        }
    }
    return board;
}

Board::Square::Square(int row, int col) : row_(row), col_(col) {
    if (!isValidCoordinates(row, col)) {
        std::cerr << "trying to create Square object with invalid coordinates" << std::endl;
        assert(false);
    }
}

int Board::Square::getRow() const {
    return row_;
}

int Board::Square::getCol() const {
    return col_;
}

std::string Board::Square::getMatrixRepresentation() const {
    std::stringstream ss;
    ss << '(' << row_ << ',' << col_ << ')';
    return ss.str();
}

std::string Board::Square::getCoordinateRepresentation() const {
    std::stringstream ss;
    ss << ('0' + NUM_ROWS - row_) << ('A' + col_);
    return ss.str();
}

bool Board::Square::operator==(const Board::Square &rhs) const {
    return row_ == rhs.row_ &&
           col_ == rhs.col_;
}

bool Board::Square::operator!=(const Board::Square &rhs) const {
    return !(rhs == *this);
}
