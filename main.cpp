#include <iostream>
#include <string>
#include <limits>
#include "build-tree.hpp"

using namespace std;

// Function to perform in-order traversal and print the sorted roads
void inOrderTraversal(Road* node) {
    if (node == nullptr) {
        return;
    }
    inOrderTraversal(node->left); // Traverse the left subtree
    cout << "ID: " << node->id << ", Place: " << node->place << endl; // Print the road
    inOrderTraversal(node->right); // Traverse the right subtree
}

int main() {
    BinaryTree tree; // Create an instance of BinaryTree
    int choice, id; // Variables to store user choice and road id
    char place[100]; // Variable to store the name of the place

    while (true) {
        // Display menu options
        cout << "1. Insert\n2. Delete\n3. Search\n4. Sort\n5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice; // Get user choice

        // Clear the input buffer
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        Road* result = nullptr; // Declare result outside the switch statement

        switch (choice) {
            case 1:
                // Insert a new road
                cout << "Enter id and place: ";
                cin >> id;
                cin.ignore(); // Clear the input buffer
                cin.getline(place, 100); // Get road id and place from user
                tree.root = tree.insert(tree.root, id, place); // Insert the road into the tree
                break;
            case 2:
                // Delete an existing road
                cout << "Enter id to delete: ";
                cin >> id; // Get road id to delete from user
                tree.root = tree.deletion(tree.root, id); // Delete the road from the tree
                break;
            case 3:
                // Search for a road
                cout << "Enter id to search: ";
                cin >> id; // Get road id to search from user
                result = tree.search(tree.root, id); // Search for the road in the tree
                if (result) {
                    // If road is found, display its place
                    cout << "Road found: " << result->place << endl;
                } else {
                    // If road is not found, display a message
                    cout << "Road not found" << endl;
                }
                break;
            case 4:
                // Sort and display the roads
                inOrderTraversal(tree.root);
                break;
            case 5:
                // Exit the program
                exit(0);
            default:
                // Handle invalid choices
                cout << "Invalid choice" << endl;
        }
    }

    return 0;
}