#include <iostream>
#include "TicTacToe.h"

TicTacToe::TicTacToe(unsigned int size) : size_(size), active_player_('X'), moves_(0) {
    board_.assign(size_, std::vector<char>(size_, ' '));
}

bool TicTacToe::IsValidMove(unsigned int row, unsigned int column) const {
    if (row >= size_ || column >= size_) {
        std::cout << "Error! Out of board bounds!\n";
        return false;
    }

    if (board_[row][column] != ' ') {
        std::cout << "Error! The cell is occupied!\n";
        return false;
    }

    return true;
}

const std::vector<char>& TicTacToe::operator[](unsigned int index) const {
    return board_.at(index);
}

std::vector<char>& TicTacToe::operator[](unsigned int index) {
    return board_.at(index);
}

void TicTacToe::SwitchPlayer() {
    moves_++;
    if (active_player_ == 'X')
        active_player_ = 'O';
    else
        active_player_ = 'X';
}

char TicTacToe::CheckWin() const {
    // Проверка строк
    for (unsigned int i = 0; i < size_; i++) {
        char first = board_[i][0];
        if (first == ' ') continue;

        bool win = true;
        for (unsigned int j = 1; j < size_; j++) {
            if (board_[i][j] != first) {
                win = false;
                break;
            }
        }
        if (win) return first;
    }

    // Проверка столбцов
    for (unsigned int j = 0; j < size_; j++) {
        char first = board_[0][j];
        if (first == ' ') continue;

        bool win = true;
        for (unsigned int i = 1; i < size_; i++) {
            if (board_[i][j] != first) {
                win = false;
                break;
            }
        }
        if (win) return first;
    }

    // Проверка главной диагонали
    char first = board_[0][0];
    if (first != ' ') {
        bool win = true;
        for (unsigned int i = 1; i < size_; i++) {
            if (board_[i][i] != first) {
                win = false;
                break;
            }
        }
        if (win) return first;
    }

    // Проверка побочной диагонали
    first = board_[0][size_ - 1];
    if (first != ' ') {
        bool win = true;
        for (unsigned int i = 1; i < size_; i++) {
            if (board_[i][size_ - 1 - i] != first) {
                win = false;
                break;
            }
        }
        if (win) return first;
    }

    // Пока никто не выиграл
    return ' ';
}

bool TicTacToe::IsDraw() const {
    return (moves_ == size_ * size_) && (CheckWin() == ' ');
}

char TicTacToe::GetActivePlayer() const {
    return active_player_;
}

unsigned int TicTacToe::GetSize() const {
    return size_;
}

void TicTacToe::Reset() {
    board_.assign(size_, std::vector<char>(size_, ' '));
    active_player_ = 'X';
    moves_ = 0;
}