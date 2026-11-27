#include "Solver.h"

bool Solver::isValidRow(const Board& board, int row, int value) const {
    for (int col = 0; col < Board::SIZE; ++col) {
        if (board.getCell(row, col) == value) 
            return false;
    }
    return true;
}

bool Solver::isValidCol(const Board& board,
                           int col, int value) const {
    for (int row = 0; row < Board::SIZE; ++row) {
        if (board.getCell(row, col) == value)
            return false;
    }

    return true;
}

bool Solver::isValidBox(const Board& board, int row, int col, int value) const {
    int startRow = (row / 3) * 3;
    int startCol = (col / 3) * 3;

    for (int r = startRow; r < startRow + 3; ++r) {
        for (int c = startCol; c < startCol + 3; ++c) {
            if (board.getCell(r, c) == value) 
                return false;
        }
    }

    return true;
}


bool Solver::isValidMove(const Board& board, int row, int col, int value) const {
    if (row < 0 || row >= Board::SIZE || col < 0 || col >= Board::SIZE || value < 1 || value > 9) {
        return false;
    }

    if (board.getCell(row, col) != 0) {
        return false;
    }

    return isValidRow(board, row, value) && isValidCol(board, col, value) && isValidBox(board, row, col, value);
}

bool Solver::isBoardValid(const Board& board) const {
    for (int row = 0; row < Board::SIZE; ++row) {
        for (int col = 0; col < Board::SIZE; ++col) {
            int value = board.getCell(row, col);

            if (value == 0)
                continue;

            // Проверяем, нет ли повторов
            for (int otherCol = col + 1; otherCol < Board::SIZE; ++otherCol) {
                if (board.getCell(row, otherCol) == value) {
                    return false;
                }
            }

            for (int otherRow = row + 1;
                 otherRow < Board::SIZE; ++otherRow) {
                if (board.getCell(otherRow, col) == value) {
                    return false;
                }
            }

            int startRow = (row / 3) * 3;
            int startCol = (col / 3) * 3;

            for (int r = startRow; r < startRow + 3; ++r) {
                for (int c = startCol; c < startCol + 3; ++c) {
                    if ((r > row || (r == row && c > col)) &&
                        board.getCell(r, c) == value) {
                        return false;
                    }
                }
            }
        }
    }

    return true;
}

bool Solver::solveRecursive(Board& board) const {
    for (int row = 0; row < Board::SIZE; ++row) {
        for (int col = 0; col < Board::SIZE; ++col) {

            if (board.getCell(row, col) != 0)
                continue;

            for (int value = 1; value <= 9; ++value) {
                if (isValidMove(board, row, col, value)) {

                    board.setCell(row, col, value);

                    if (solveRecursive(board))
                        return true;

                    // Если решение не подошло, возвращаем 0
                    board.setCell(row, col, 0);
                }
            }

            return false;
        }
    }

    return true;
}

bool Solver::solve(Board& board) const {
    if (!isBoardValid(board)) {
        return false;
    }

    return solveRecursive(board);
}

int Solver::countSolutions(Board board, int limit) {
    if (limit <= 0)
        return 0;

    
    if (!isBoardValid(board)) // Если поле уже содержит конфликты — решений нет
        return 0;

    return countSolutionsRecursive(board, limit);
}

int Solver::countSolutionsRecursive(Board& board, int limit) {
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {

            if (board.getCell(row, col) != 0) {
                continue;
            }

            int solutions = 0;

            for (int value = 1; value <= 9; ++value) {

                if (isValidMove(board, row, col, value)) {
                    board.setCell(row, col, value);

                    solutions += countSolutionsRecursive(
                        board,
                        limit - solutions
                    );


                    board.setCell(row, col, 0); // Клетку в исходное состояние

                    if (solutions >= limit) {
                        return limit;
                    }
                }
            }

            return solutions;
        }
    }

    return 1;
}