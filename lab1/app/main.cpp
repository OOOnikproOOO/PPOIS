#include <iostream>
#include <string>
#include <limits>
#include "Set.h"
#include "TicTacToe.h"

using namespace std;

short MainMenu();
void SetTask();
short SetMenu();
void TicTacToeTask();
void PrintBoard(const TicTacToe&);

int main() {
    while (true) {
        short user_choice = MainMenu();

        switch (user_choice) {
        case 1:
            SetTask();
            break;
        case 2:
            TicTacToeTask();
            break;
        case 0:
            return 0;
        default:
            cout << "Error! Incorrect input! Try again!\n\n";
        }
    }
}

short MainMenu() {
    short choice;
    for (unsigned int i = 0; i < 37; i++) printf("-");
    printf("\n|%-7sMain Laboratory Menu%-8s|\n", "", "");
    for (unsigned int i = 0; i < 37; i++) printf("-");
    printf("\n| 1 - Task 1: Unoriented Cantor Set |\n| 2 - Task 2: Tic-Tac-Toe Game%-6s|\n| 0 - Exit%-26s|\n", "", "");
    for (unsigned int i = 0; i < 37; i++) printf("-");
    cout << "\nSelected: ";
    cin >> choice;
    cout << endl;
    return choice;
}

void SetTask() {
    Set the_set;
    string form_string = "";

    while (true) {
        short user_choice = SetMenu();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (user_choice) {
        case 1:
            cout << "Enter a string: ";
            getline(cin, form_string);
            cout << "\n";
            the_set.FormSetFromString(form_string, 1);
            form_string = "";
            break;

        case 2:
            if (the_set.IsEmpty())
                cout << "The set is empty!\n\n";
            else cout << "The set isn't empty!\n\n";
            break;

        case 3:
            cout << "The cardinality of a set is " << the_set.Size() << "\n\n";
            break;

        case 4:
            cout << "Enter an element to add: ";
            getline(cin, form_string);
            cout << "\n";
            if (form_string[0] == '{') {
                Set subset;
                subset.FormSetFromString(form_string, 1);
                if (the_set.Add(subset))
                    cout << "The element was successfully added!\n\n";
                else cout << "The element wasn't added! It is already contained!\n\n";
            }
            else
                if (the_set.Add(form_string))
                    cout << "The element was successfully added!\n\n";
                else cout << "The element wasn't added! It is already contained!\n\n";
            form_string = "";
            break;

        case 5:
            cout << "Enter an element to delete: ";
            getline(cin, form_string);
            cout << "\n";
            if (form_string[0] == '{') {
                Set subset;
                subset.FormSetFromString(form_string, 1);
                if (the_set.Delete(subset))
                    cout << "The element was successfully deleted!\n\n";
                else cout << "The element wasn't deleted! It isn't contained!\n\n";
            }
            else
                if (the_set.Delete(form_string))
                    cout << "The element was successfully deleted!\n\n";
                else cout << "The element wasn't deleted! It isn't contained!\n\n";
            form_string = "";
            break;

        case 6:
            cout << "Enter an element to be checked for inclusion: ";
            getline(cin, form_string);
            cout << "\n";
            if (form_string[0] == '{') {
                Set subset;
                subset.FormSetFromString(form_string, 1);
                if (the_set[subset])
                    cout << "The element is included!\n\n";
                else cout << "The element isn't included!\n\n";
            }
            else
                if (the_set[form_string])
                    cout << "The element is included!\n\n";
                else cout << "The element isn't included!\n\n";
            form_string = "";
            break;

        case 7:
        {
            cout << "Enter a set to unite with: ";
            getline(cin, form_string);
            cout << "\n";
            Set other;
            other.FormSetFromString(form_string, 1);
            Set result = the_set + other;
            string string_result = result.PrintedSet();
            cout << "The union of the sets is " << string_result << "\n\n";
            form_string = "";
            break;
        }

        case 8:
        {
            cout << "Enter a set to intersect with: ";
            getline(cin, form_string);
            cout << "\n";
            Set other;
            other.FormSetFromString(form_string, 1);
            Set result = the_set * other;
            string string_result = result.PrintedSet();
            cout << "The intersection of the sets is " << string_result << "\n\n";
            form_string = "";
            break;
        }
           
        case 9:
        {
            cout << "Enter a set for the difference: ";
            getline(cin, form_string);
            cout << "\n";
            Set other;
            other.FormSetFromString(form_string, 1);
            Set result = the_set - other;
            string string_result = result.PrintedSet();
            cout << "The difference of the sets is " << string_result << "\n\n";
            form_string = "";
            break;
        }

        case 10:
        {
            Set result = the_set.Boolean();
            string string_result = result.PrintedSet();
            cout << "The boolean of the set is " << string_result << "\n\n";
            break;
        }

        case 11:
            cout << "The set is " << the_set.PrintedSet() << "\n\n";
            break;

        case 12:
            return;

        default:
            cout << "Error! Incorrect input! Try again!\n\n";
        }
    }
}

short SetMenu() {
    short choice;
    for (unsigned int i = 0; i < 47; i++) printf("-");
    printf("\n|%-18sSet Menu%-19s|\n", "", "");
    for (unsigned int i = 0; i < 47; i++) printf("-");
    printf("\n| 1 - Create a set from a string%-14s|\n| 2 - Check for an empty set%-18s|\n| 3 - Determine the cardinality of a set%-6s|\n| 4 - Add an element%-26s|\n| 5 - Delete an element%-23s|\n| 6 - Check if an element belongs to a set%-4s|\n| 7 - Union of two sets%-23s|\n| 8 - Intersection of two sets%-16s|\n| 9 - Difference of two sets%-18s|\n| 10 - Boolean of a set%-23s|\n| 11 - Print the set%-26s|\n| 12 - Exit%-35s|\n", "", "", "", "", "", "", "", "", "", "", "", "");
    for (unsigned int i = 0; i < 47; i++) printf("-");
    cout << "\nSelected: ";
    cin >> choice;
    cout << endl;
    return choice;
}

void TicTacToeTask() {
    unsigned int size;
    printf("%-6s=== Tic-Tac-Toe ===\n", "");
    cout << "Enter board size (minimum 3): ";
    cin >> size;

    if (size < 3) {
        size = 3;
        cout << "Invalid size! Defaulting to 3x3.\n";
    }

    cout << "\nAttention! The move is entered in the format \"row and column\". For example, 0 0.\n";

    TicTacToe game(size);

    while (true) {
        PrintBoard(game);

        char winner = game.CheckWin();
        if (winner != ' ') {
            cout << ">>> Player " << winner << " Wins! <<<\n\n";
            break;
        }

        if (game.IsDraw()) {
            cout << ">>> It's A Draw! <<<\n\n";
            break;
        }

        unsigned int row, col;
        cout << "Player " << game.GetActivePlayer() << ": ";
        cin >> row >> col;

        if (game.IsValidMove(row, col)) {
            game[row][col] = game.GetActivePlayer();
            game.SwitchPlayer();
        }
        else
            cout << "Please, try again.\n";
    }
}

void PrintBoard(const TicTacToe& game) {
    unsigned int size = game.GetSize();
    cout << "\n";

    for (unsigned int i = 0; i < size; i++) {
        cout << "|"; 
        for (unsigned int j = 0; j < size; j++) {
            cout << game[i][j] << "|";
        }
        cout << "\n";
    }
    cout << "\n";
}