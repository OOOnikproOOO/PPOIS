#include <iostream>
#include "Set.h"

using namespace std;

int main() {
    Set TheSet;

    cout << "Is set empty? " << (TheSet.IsEmpty() ? "Yes" : "No") << endl;
    cout << "Adding \"apple\". Is it successful? " << (TheSet.Add("apple") ? "Yes" : "No") << endl;
    cout << "Adding \"orange\" Is it successful? " << (TheSet.Add("orange") ? "Yes" : "No") << endl;
    cout << "Adding \"banana\". Is it successful? " << (TheSet.Add("banana") ? "Yes" : "No") << endl;
    cout << "Adding \"apple\" again. Is it successful? " << (TheSet.Add("apple") ? "Yes" : "No") << endl;
    cout << "The number of elements in set is " << TheSet.Size() << endl;
    cout << "Deleting \"orange\". Is it successful? " << (TheSet.Delete("orange") ? "Yes" : "No") << endl;
    cout << "The number of elements in set is " << TheSet.Size() << endl;

    return 0;
}