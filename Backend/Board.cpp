#include "Board.h"
#include <stdexcept> // для обработки исключений
using namespace std;

Board::Board() {
    clear(); // инициализация доски пустыми значениями
}

bool Board::isValidPosition(int row, int col) const {
    return row >= 0 && row < SIZE && col >= 0 && col < SIZE;
}

void Board::clear() {
    for (int row = 0; row < SIZE; ++row) {
        for (int col = 0; col < SIZE; ++col) {
            cells[row][col] = 0; // очищаем клетку
            original[row][col] = 0; // очищаем исходное значение
        }
    }
}

bool Board::loadPuzzle(const Grid& puzzle) {
    for (int row = 0; row < SIZE; ++row) {
        for (int col = 0; col < SIZE; ++col) {
            if (puzzle[row][col] < 0 || puzzle[row][col] > 9) 
                return false;
        }
    }
    cells = puzzle;
    original = puzzle;
    
    return true;
}

int Board::getCell(int row, int col) const {
    if (!isValidPosition(row, col))
        throw out_of_range("Invalid position");

    return cells[row][col];
}

bool Board::isGiven(int row, int col) const {
    if (!isValidPosition(row, col)) 
        return false;

    return original[row][col] != 0;
}

bool Board::isValidValue(int row, int col, int value) {
    if (value < 0 || value > 9)
        return false;
    if (isGiven(row, col))
        return false;
    return true;
}

bool Board::setCell(int row, int col, int value) {
    if (isValidValue(row, col, value)) {
        cells[row][col] = value;
        return true;
    }
    return false;
}