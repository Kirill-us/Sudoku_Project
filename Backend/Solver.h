#ifndef SOLVER_H
#define SOLVER_H

#include "Board.h"

class Solver {
public:
    bool isValidMove(const Board& board, int row, int col, int value) const;

    bool isBoardValid(const Board& board) const; // правильно ли заполнено поле

    bool solve(Board& board) const;

    int countSolutions(Board board, int limit = 2);

private:
    bool isValidRow(const Board& board, int row, int value) const;
    bool isValidCol(const Board& board, int col, int value) const;

    bool isValidBox(const Board& board, int row, int col, int value) const;

    bool solveRecursive(Board& board) const;

    int countSolutionsRecursive(Board& board, int limit);
};

#endif