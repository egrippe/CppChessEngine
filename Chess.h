//
// Created by Edward Grippe on 11.03.17.
//

#ifndef CHESS_CHESS_H
#define CHESS_CHESS_H


#include "Color.h"
#include "Move.h"
#include "Board.h"

#include <vector>

namespace Chess {

    /**
     * Find all possible moves for a given player.
     * @param board pointer to the chess board
     * @param player_color the color of the player
     * @return vector of possible moves
     */
    std::vector<Move> findPossibleMoves(const Board *board, Color player_color);

    /**
     * Find all possible moves starting from a given square.
     * If there is no piece occupying the given square an empty vector is returned.
     * @param board pointer to the chess board
     * @param from_square the square to start from
     * @return vector of possible moves
     */
    std::vector<Move> findPossibleMoves(const Board *board, Board::Square from_square);

    bool isValidMove(const Board *board, Move move);

    std::vector<Move>& addMovesPatternKing(const Board *board, Board::Square from_square, std::vector<Move> &moves);
    std::vector<Move>& addMovesPatternQueen(const Board *board, Board::Square from_square, std::vector<Move> &moves);
    std::vector<Move>& addMovesPatternRook(const Board *board, Board::Square from_square, std::vector<Move> &moves);
    std::vector<Move>& addMovesPatternBishop(const Board *board, Board::Square from_square, std::vector<Move> &moves);
    std::vector<Move>& addMovesPatternKnight(const Board *board, Board::Square from_square, std::vector<Move> &moves);
    std::vector<Move>& addMovesPatternPawn(const Board *board, Board::Square from_square, std::vector<Move> &moves);
};


#endif //CHESS_CHESS_H
