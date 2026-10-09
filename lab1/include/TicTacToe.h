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
     * @brief Проверяет возможность установки символа в указанную клетку игрового поля.
     * @param row Индекс строки игрового поля.
     * @param column Индекс столбца игрового поля.
     * @return true, если ход возможен, false — если клетка занята или координаты вне игрового поля.
     */
    bool IsValidMove(unsigned int row, unsigned int column) const;

    /**
     * @brief Перегрузка оператора индексации (для чтения).
     * @param index Индекс запрашиваемой строки игрового поля.
     * @return Константная ссылка на строку поля.
     */
    const std::vector<char>& operator[](unsigned int index) const;

    /**
     * @brief Перегрузка оператора индексации (для установки значения).
     * @param index Индекс запрашиваемой строки игрового поля.
     * @return Ссылка на строку поля.
     */
    std::vector<char>& operator[](unsigned int index);

    /**
     * @brief Меняет игрока, увеличивая счетчик ходов.
     */
    void SwitchPlayer();

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
     * @brief Двумерный вектор, представляющий игровое поле и хранящий символы 'X', 'O' или ' ' (пробел - пустая клетка).
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
     * @brief Количество уже сделанных ходов.
     */
    unsigned int moves_;
};

#endif