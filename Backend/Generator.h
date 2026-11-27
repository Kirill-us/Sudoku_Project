#ifndef GENERATOR_H
#define GENERATOR_H

#include "Board.h"
#include <random>


enum class Difficulty {
    Easy,
    Medium,
    Hard
};

class Generator {
public:
    Generator();

    Board generateSolvedBoard();

    Board generatePuzzle(Difficulty difficulty);

    int countEmptyCells(const Board& board);
private:
    std::mt19937 rng_;

    bool fillGrid(Board::Grid& grid);
    bool isSafe(const Board::Grid& grid, int row, int col, int value);
};

#endif