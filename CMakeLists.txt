cmake_minimum_required(VERSION 3.6)
project(Chess)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp pieces/Piece.cpp pieces/Piece.h Color.h pieces/King.h pieces/Queen.h pieces/Rook.h pieces/Bishop.h pieces/Knight.h pieces/Pawn.h Chess.cpp Chess.h Move.h Board.cpp Board.h Game.cpp Game.h)
add_executable(Chess ${SOURCE_FILES})