//
// Created by Edward Grippe on 11.03.17.
//

#include "Chess.h"

#include <iostream>
#include <algorithm>

using namespace std;

namespace Chess {

    std::vector<Move>& addPossibleMoves(const Board *board, Board::Square from_square, std::vector<Move> &moves) {
        if (board->isEmpty(from_square)) {
            return moves;
        }

        Piece::Type type = board->getPiece(from_square)->getType();
        switch (type) {
            case Piece::Type::KING:   return addMovesPatternKing(board, from_square, moves);
            case Piece::Type::QUEEN:  return addMovesPatternQueen(board, from_square, moves);
            case Piece::Type::ROOK:   return addMovesPatternRook(board, from_square, moves);
            case Piece::Type::BISHOP: return addMovesPatternBishop(board, from_square, moves);
            case Piece::Type::KNIGHT: return addMovesPatternKnight(board, from_square, moves);
            case Piece::Type::PAWN:   return addMovesPatternPawn(board, from_square, moves);
        }
    }

    std::vector<Move> findPossibleMoves(const Board *board, Board::Square from_square) {
        std::vector<Move> moves = std::vector<Move>();
        return addPossibleMoves(board, from_square, moves);
    }

    std::vector<Move> findPossibleMoves(const Board *board, Color player_color) {
        std::vector<Move> moves = std::vector<Move>();
        for (int i = 0; i < Board::NUM_ROWS; ++i) {
            for (int j = 0; j < Board::NUM_COLS; ++j) {
                Board::Square square(i,j);
                if (board->isOccupiedBy(square, player_color)) {
                    addPossibleMoves(board, square, moves);
                }
            }
        }
        return moves;
    }

    std::vector<Move>& addMovesPatternKing(const Board *board, Board::Square from_square, std::vector<Move> &moves) {

        int row_offset[8] = {-1,-1,-1, 0, 0, 1, 1, 1};
        int col_offset[8] = {-1, 0, 1,-1, 1,-1, 0, 1};

        for (int i = 0; i < 8; ++i) {
            int new_row = from_square.getRow() + row_offset[i];
            int new_col = from_square.getCol() + col_offset[i];

            if (board->isValidCoordinates(new_row, new_col)) {

                Board::Square to_square = Board::Square(new_row, new_col);
                if (board->isEmpty(to_square)) {
                    moves.push_back(Move(from_square, to_square, Move::Type::NON_CAPTURING));
                    continue;
                }
                else if (board->getPiece(from_square)->getColor() != board->getPiece(to_square)->getColor()) {
                    moves.push_back(Move(from_square, to_square, Move::Type::CAPTURING));
                }
            }
        }

        return moves;
    }

    std::vector<Move>& addMovesPatternQueen(const Board *board, Board::Square from_square, std::vector<Move> &moves) {
        addMovesPatternRook(board, from_square, moves);
        addMovesPatternBishop(board, from_square, moves);
        return moves;
    }

    std::vector<Move>& addMovesPatternRook(const Board *board, Board::Square from_square, std::vector<Move> &moves) {

        int row_offset[] = {-1, 1, 0, 0};
        int col_offset[] = { 0, 0,-1, 1};

        for (int i = 0; i < 4; ++i) {
            int to_row = from_square.getRow();
            int to_col = from_square.getCol();
            while (true) {
                to_row += row_offset[i];
                to_col += col_offset[i];

                if (!board->isValidCoordinates(to_row, to_col)) break;

                Board::Square to_square(to_row, to_col);
                if (board->isEmpty(to_square)) {
                    moves.push_back(Move(from_square, to_square, Move::Type::NON_CAPTURING));
                    continue;
                }

                if (board->getPiece(from_square)->getColor() != board->getPiece(to_square)->getColor()) {
                    moves.push_back(Move(from_square, to_square, Move::Type::CAPTURING));
                }

                break;
            }
        }

        return moves;
    }

    std::vector<Move>& addMovesPatternBishop(const Board *board, Board::Square from_square, std::vector<Move> &moves) {

        int row_offset[] = {-1,-1, 1, 1};
        int col_offset[] = {-1, 1,-1, 1};

        for (int i = 0; i < 4; ++i) {
            int to_row = from_square.getRow();
            int to_col = from_square.getCol();

            while (true) {
                to_row += row_offset[i];
                to_col += col_offset[i];

                if (!board->isValidCoordinates(to_row, to_col)) break;

                Board::Square to_square(to_row, to_col);
                if (board->isEmpty(to_square)) {
                    moves.push_back(Move(from_square, to_square, Move::Type::NON_CAPTURING));
                    continue;
                }

                if (board->getPiece(from_square)->getColor() != board->getPiece(to_square)->getColor()) {
                    moves.push_back(Move(from_square, to_square, Move::Type::CAPTURING));
                }

                break;
            }
        }

        return moves;
    }

    std::vector<Move>& addMovesPatternKnight(const Board *board, Board::Square from_square, std::vector<Move> &moves) {

        int row_offset[] = {-2,-1, 1, 2, 2, 1,-1,-2};
        int col_offset[] = { 1, 2, 2, 1,-1,-2,-2,-1};

        for (int i = 0; i < 8; ++i) {
            int to_row = from_square.getRow() + row_offset[i];
            int to_col = from_square.getCol() + col_offset[i];

            if (board->isValidCoordinates(to_row, to_col)) {

                Board::Square to_square(to_row, to_col);

                if (board->isEmpty(to_square)) {
                    moves.push_back(Move(from_square, to_square, Move::Type::NON_CAPTURING));
                    continue;
                }

                if (board->getPiece(from_square)->getColor() != board->getPiece(to_square)->getColor()) {
                    moves.push_back(Move(from_square, to_square, Move::Type::CAPTURING));
                    continue;
                }
            }
        }

        return moves;
    }

    std::vector<Move>& addMovesPatternPawn(const Board *board, Board::Square from_square, std::vector<Move> &moves) {

        Color player_color = board->getPiece(from_square)->getColor();

        int row = from_square.getRow();
        int col = from_square.getCol();

        if (player_color == Color::WHITE) {

            // try move one step up
            if (board->isValidCoordinates(row -1, col)) {
                Board::Square square(row -1, col);
                if (board->isEmpty(square)) {
                    moves.push_back(Move(from_square, square, Move::Type::NON_CAPTURING));
                }
            }

            // if on row 6 try move 2 steps up
            if (row == 6) {
                Board::Square square(row -2, col);
                if (board->isEmpty(square)) {
                    moves.push_back(Move(from_square, square, Move::Type::NON_CAPTURING));
                }
            }

            // try capture up left
            if (board->isValidCoordinates(row -1, col -1)) {
                Board::Square to_square(row -1, col -1);
                if (board->isOccupiedBy(to_square, Color::BLACK)) {
                    moves.push_back(Move(from_square, to_square, Move::Type::CAPTURING));
                }
            }

            // try capture right
            if (board->isValidCoordinates(row -1, col +1)) {
                Board::Square to_square(row -1, col +1);
                if (board->isOccupiedBy(to_square, Color::BLACK)) {
                    moves.push_back(Move(from_square, to_square, Move::Type::CAPTURING));
                }
            }

        }

        if (player_color == Color::BLACK) {

            // try move one step down
            if (board->isValidCoordinates(row +1, col)) {
                Board::Square square(row +1, col);
                if (board->isEmpty(square)) {
                    moves.push_back(Move(from_square, square, Move::Type::NON_CAPTURING));
                }
            }

            // if on row 1 try move 2 steps down
            if (row == 6) {
                Board::Square square(row +2, col);
                if (board->isEmpty(square)) {
                    moves.push_back(Move(from_square, square, Move::Type::NON_CAPTURING));
                }
            }

            // try capture down left
            if (board->isValidCoordinates(row +1, col -1)) {
                Board::Square to_square(row +1, col -1);
                if (board->isOccupiedBy(to_square, Color::BLACK)) {
                    moves.push_back(Move(from_square, to_square, Move::Type::CAPTURING));
                }
            }

            // try capture down right
            if (board->isValidCoordinates(row +1, col +1)) {
                Board::Square to_square(row +1, col +1);
                if (board->isOccupiedBy(to_square, Color::BLACK)) {
                    moves.push_back(Move(from_square, to_square, Move::Type::CAPTURING));
                }
            }

        }

        return moves;
    }

    bool isValidMove(const Board *board, Move move) {
        std::vector<Move> moves = findPossibleMoves(board, move.getFrom());
        return std::find(moves.begin(), moves.end(), move) != moves.end();
    }

}
