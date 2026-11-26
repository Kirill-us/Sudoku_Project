#ifndef BOARD_H
#define BOARD_H

#include <array>

class Board {
public:
    static const int SIZE = 9; // размер доски (9x9)
    using Grid = std::array<std::array<int, SIZE>, SIZE>;

    Board(); // создает поле по умолчяанию(пустое)

    int getCell(int row, int col) const; // возвращает значение клетки

    bool loadPuzzle(const Grid& puzzle); // // Загружает новую головоломку

    bool setCell(int row, int col, int value); // изменяет значение клетки игроком

    bool isGiven(int row, int col) const; // проверяет, является ли клетка заданной

    bool isValidValue(int row, int col, int value);

    void clear(); // очищает доску, удаляя все значения клеток

private:
    Grid cells; // текущее состояние игрового поля.
    Grid original; // исходные числа головоломки.
    bool isValidPosition(int row, int col) const; // проверяет, находится ли позиция в пределах доски
};

#endif