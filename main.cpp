#include <iostream>
#include "Backend/Board.h"

int main() {
    Board board;

    Board::Grid puzzle = {};

    puzzle[0][0] = 5;
    puzzle[0][1] = 3;
    puzzle[1][0] = 6;

    board.loadPuzzle(puzzle);

    std::cout << "Cell (0, 0): "
              << board.getCell(0, 0) << '\n';

    std::cout << "Cell (0, 2): "
              << board.getCell(0, 2) << '\n';

    // Попытка изменить исходную клетку
    std::cout << "Change given cell: "
              << board.setCell(0, 8, 7) << '\n';

    // Заполнение пустой клетки
    std::cout << "Change empty cell: "
              << board.setCell(0, 2, 4) << '\n';

    std::cout << "New value: "
              << board.getCell(0, 8) << '\n';

    std::cout << "New value: "
              << board.getCell(0, 2) << '\n';

    return 0;
}
