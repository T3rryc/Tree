#include <iostream>
#include <string>
#include "build-tree.hpp"


using namespace std;

int main() {
    BinaryTree tree;
    int choice, id;
    char place[100];

    while (true) {
        cout << "1. Insert\n2. Delete\n3. Search\n4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        Road* result = nullptr; // Declare result outside the switch statement

        switch (choice) {
            case 1:
                cout << "Enter id and place: ";
                cin >> id >> place;
                tree.root = tree.insert(tree.root, id, place);
                break;
            case 2:
                cout << "Enter id to delete: ";
                cin >> id;
                tree.root = tree.deletion(tree.root, id);
                break;
            case 3:
                cout << "Enter id to search: ";
                cin >> id;
                result = tree.search(tree.root, id);
                if (result) {
                    cout << "Road found: " << result->place << endl;
                } else {
                    cout << "Road not found" << endl;
                }
                break;
            case 4:
                exit(0);
            default:
                cout << "Invalid choice" << endl;
        }
    }

    return 0;
}