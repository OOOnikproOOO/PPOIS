/**
 * @file TicTacToe.h
 * @brief Объявление класса TicTacToe для игры "Крестики-нолики" на поле произвольного размера.
 * @author Nikita Momot
 * @date 2026
 */

#ifndef TICTACTOE_H
#define TICTACTOE_H

#include <vector>

 /**
  * @brief Класс, реализующий логику игры "Крестики-нолики".
  */
class TicTacToe {
public:
    /**
     * @brief Конструктор игры.
     * @param size Размер игрового поля, по умолчанию - 3.
     */
    explicit TicTacToe(unsigned int size = 3);

    /**
     * @brief Проверяет возможность установки символа и делает ход, если клетка свободна.
     * @param row Номер строки.
     * @param column Номер столбца.
     * @return true, если ход успешен, false — если клетка занята или координаты вне игрового поля.
     */
    bool MakeMove(unsigned int row, unsigned int column);

    /**
     * @brief Перегрузка оператора индексации для получения строки поля (только для чтения).
     * @param index Индекс строки.
     * @return Константная ссылка на строку игрового поля.
     */
    const std::vector<char>& operator[](unsigned int index) const;

    /**
     * @brief Проверяет, есть ли сейчас победитель.
     * @return Символ победителя ('X' / 'O') или пробел ' ', если победителя пока нет.
     */
    char CheckWin() const;

    /**
     * @brief Проверяет, закончилась ли игра ничьей.
     * @return true, если ничья, иначе false.
     */
    bool IsDraw() const;

    /**
     * @brief Возвращает символ игрока, чей сейчас ход.
     * @return 'X' или 'O'.
     */
    char GetActivePlayer() const;

    /**
     * @brief Геттер для размера игрового поля.
     * @return Размер игрового поля.
     */
    unsigned int GetSize() const;

    /**
     * @brief Очищает поле для новой игры.
     */
    void Reset();

private:
    /**
     * @brief Двумерный вектор, представляющий игровое поле.
     * Хранит символы 'X', 'O' или ' ' (пробел - пустая клетка).
     */
    std::vector<std::vector<char>> board_;

    /**
     * @brief Размер игрового поля.
     */
    unsigned int size_;

    /**
     * @brief Символ игрока, который должен сделать следующий ход ('X' или 'O').
     */
    char active_player_;

    /**
     * @brief Количество уже сделанных ходов. Используется для проверки на ничью.
     */
    unsigned int moves_;
};

#endif