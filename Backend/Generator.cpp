#include "Generator.h"
#include "Solver.h"
#include <algorithm>
#include <array>

Generator::Generator() : rng_(std::random_device{}()) {
}

Board Generator::generateSolvedBoard() {
    Board::Grid grid{};

    fillGrid(grid);

    Board board;
    board.loadPuzzle(grid);

    return board;
}

bool Generator::fillGrid(Board::Grid& grid) {
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {

            if (grid[row][col] != 0)
                continue;

            std::array<int, 9> numbers{
                1, 2, 3, 4, 5, 6, 7, 8, 9
            };

            std::shuffle(numbers.begin(), numbers.end(), rng_);

            for (int number : numbers) {
                if (isSafe(grid, row, col, number)) {
                    grid[row][col] = number;

                    if (fillGrid(grid)) 
                        return true;

                    grid[row][col] = 0;
                }
            }

            return false;
        }
    }

    return true;
}

bool Generator::isSafe(const Board::Grid& grid, int row, int col, int value) {
    for (int i = 0; i < 9; ++i) {
        if (grid[row][i] == value || grid[i][col] == value) 
            return false;
    }

    int boxRow = (row / 3) * 3;
    int boxCol = (col / 3) * 3;

    for (int r = boxRow; r < boxRow + 3; ++r) {
        for (int c = boxCol; c < boxCol + 3; ++c) {
            if (grid[r][c] == value)
                return false;
        }
    }

    return true;
}

Board Generator::generatePuzzle(Difficulty difficulty) {
    Board solvedBoard = generateSolvedBoard(); // решенное 

    Board::Grid puzzle{}; // Копируем значения в Grid

    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            puzzle[row][col] = solvedBoard.getCell(row, col);
        }
    }

    int cellsToRemove = 0; // Количество клеток, которые нужно удалить

    switch (difficulty) {
        case Difficulty::Easy:
            cellsToRemove = 35;
            break;

        case Difficulty::Medium:
            cellsToRemove = 45;
            break;

        case Difficulty::Hard:
            cellsToRemove = 52;
            break;
    }

    std::array<int, 81> positions{}; // Список всех 81 клетки

    for (int i = 0; i < 81; ++i) {
        positions[i] = i;
    }

    std::shuffle(positions.begin(), positions.end(), rng_);
    
    Solver solver; // Удаляем числа

int removed = 0;

for (int i = 0; i < 81 && removed < cellsToRemove; ++i) {
    int position = positions[i];

    int row = position / 9;
    int col = position % 9;

    int oldValue = puzzle[row][col];

    puzzle[row][col] = 0;

    Board candidate;
    candidate.loadPuzzle(puzzle);

    int solutions = solver.countSolutions(candidate); // Проверяем количество решений

    if (solutions == 1) {
        ++removed;
    } else {
        // Вернём число обратно
        puzzle[row][col] = oldValue; // Вернём число обратно
    }
}

    Board result;
    result.loadPuzzle(puzzle);

    return result;
}

int Generator::countEmptyCells(const Board& board) {
    int emptyCells = 0;

    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            if (board.getCell(row, col) == 0) {
                ++emptyCells;
            }
        }
    }

    return emptyCells;
}