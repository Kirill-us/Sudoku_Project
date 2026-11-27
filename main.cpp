#include <iostream>
#include "Backend/Generator.h"
#include "Backend/Solver.h"

int main() {
    Generator generator;

    Board board = generator.generatePuzzle(Difficulty::Hard);

    std::cout << "Generated Sudoku:\n\n";

    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            int value = board.getCell(row, col);

            if (value == 0) {
                std::cout << ". ";
            } else {
                std::cout << value << " ";
            }
        }

        std::cout << '\n';
    }

    Solver solver;

    int solutions = solver.countSolutions(board);

    return 0;
}