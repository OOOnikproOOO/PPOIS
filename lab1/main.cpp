#include <iostream>
#include "Set.h"

using namespace std;

int main() {
    Set The_Set;

    cout << "Is set empty? " << (The_Set.IsEmpty() ? "Yes" : "No") << endl;
    cout << "Adding \"apple\". Is it successful? " << (The_Set.Add("apple") ? "Yes" : "No") << endl;
    cout << "Adding \"orange\" Is it successful? " << (The_Set.Add("orange") ? "Yes" : "No") << endl;
    cout << "Adding \"apple\" again. Is it successful? " << (The_Set.Add("apple") ? "Yes" : "No") << endl;
    cout << "The number of elements in set is " << The_Set.Size() << endl;

    return 0;
}