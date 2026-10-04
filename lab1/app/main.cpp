#include <iostream>
#include "Set.h"

using namespace std;

short Menu();

int main() { // Используется одно множество, над которым будут проводиться действия? // Дополнительные функции (меню и др.) тоже в заголовочный файл? // Выводить само множество и его элементы?
    Set the_set;
    string form_string = "";

    while (true) {
        short user_choice = Menu();
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
                subset.FormSetFromString(form_string, 0);
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
                subset.FormSetFromString(form_string, 0);
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
                subset.FormSetFromString(form_string, 0);
                if (the_set.Contains(subset))
                    cout << "The element is included!\n\n";
                else cout << "The element isn't included!\n\n";
            }
            else
                if (the_set.Contains(form_string))
                    cout << "The element is included!\n\n";
                else cout << "The element isn't included!\n\n";
            form_string = "";
            break;

        //...

        case 11:
            cout << the_set.PrintSet() << "\n\n";
            break;

        case 12:
            return 0;

        default:
            cout << "Error! Incorrect input! Try again!\n\n";
        }
    }
}

short Menu() {
    short choice;
    for (int i = 0; i < 47; i++) printf("-");
    printf("\n|%-20sMENU%-21s|\n", "", "");
    for (int i = 0; i < 47; i++) printf("-");
    printf("\n| 1 - Create a set from a string%-14s|\n| 2 - Check for an empty set%-18s|\n| 3 - Determine the cardinality of a set%-6s|\n| 4 - Add an element%-26s|\n| 5 - Delete an element%-23s|\n| 6 - Check if an element belongs to a set%-4s|\n| 7 - Union of two sets%-23s|\n| 8 - Intersection of two sets%-16s|\n| 9 - Difference of two sets%-18s|\n| 10 - Construction of the power set of a set |\n| 11 - Print a set%-28s|\n| 12 - Exit%-35s|\n", "", "", "", "", "", "", "", "", "", "", "");
    for (int i = 0; i < 47; i++) printf("-");
    cout << "\nSelected: ";
    cin >> choice;
    cout << endl;
    return choice;
}
