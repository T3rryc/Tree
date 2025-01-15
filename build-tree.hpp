#ifndef BUILD_TREE_HPP
#define BUILD_TREE_HPP

#include <cstring>
#include <algorithm>

// Class representing a road in the binary tree
class Road {
public:
    int id; // Unique identifier for the road
    char place[100]; // Name of the place
    Road* left; // Pointer to the left child
    Road* right; // Pointer to the right child
    int height; // Height of the node for balancing

    // Constructor to initialize a road with an id and place
    Road(int id, const char* place) : id(id), left(nullptr), right(nullptr), height(1) {
        strcpy(this->place, place); // Copy the place name
    }
};

// Class representing a binary tree
class BinaryTree {
public:
    Road* root; // Root of the binary tree

    // Constructor to initialize the binary tree
    BinaryTree() : root(nullptr) {}

    // Function to insert a road into the tree
    Road* insert(Road* road, int id, const char* place);

    // Function to delete a road from the tree
    Road* deletion(Road* road, int id);

    // Function to search for a road in the tree
    Road* search(Road* road, int id);

    // Function to find the minimum value node in the tree
    Road* findMin(Road* road);

    // Function to get the height of a node
    int getHeight(Road* road);

    // Function to get the balance factor of a node
    int getBalance(Road* road);

    // Function to perform a right rotation
    Road* rightRotate(Road* y);

    // Function to perform a left rotation
    Road* leftRotate(Road* x);
};

// Function definitions

// Function to get the height of a node
int BinaryTree::getHeight(Road* road) {
    return road ? road->height : 0;
}

// Function to get the balance factor of a node
int BinaryTree::getBalance(Road* road) {
    return road ? getHeight(road->left) - getHeight(road->right) : 0;
}

// Function to perform a right rotation
Road* BinaryTree::rightRotate(Road* y) {
    Road* x = y->left;
    Road* T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;
    return x;
}

// Function to perform a left rotation
Road* BinaryTree::leftRotate(Road* x) {
    Road* y = x->right;
    Road* T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;
    return y;
}

// Function to insert a road into the tree
Road* BinaryTree::insert(Road* road, int id, const char* place) {
    if (road == nullptr) {
        return new Road(id, place);
    }
    if (id < road->id) {
        road->left = insert(road->left, id, place);
    } else if (id > road->id) {
        road->right = insert(road->right, id, place);
    } else {
        return road;
    }

    road->height = 1 + std::max(getHeight(road->left), getHeight(road->right));
    int balance = getBalance(road);

    if (balance > 1 && id < road->left->id) {
        return rightRotate(road);
    }
    if (balance < -1 && id > road->right->id) {
        return leftRotate(road);
    }
    if (balance > 1 && id > road->left->id) {
        road->left = leftRotate(road->left);
        return rightRotate(road);
    }
    if (balance < -1 && id < road->right->id) {
        road->right = rightRotate(road->right);
        return leftRotate(road);
    }

    return road;
}

// Function to delete a road from the tree
Road* BinaryTree::deletion(Road* road, int id) {
    if (road == nullptr) {
        return road;
    }
    if (id < road->id) {
        road->left = deletion(road->left, id);
    } else if (id > road->id) {
        road->right = deletion(road->right, id);
    } else {
        if (road->left == nullptr || road->right == nullptr) {
            Road* temp = road->left ? road->left : road->right;
            if (temp == nullptr) {
                temp = road;
                road = nullptr;
            } else {
                *road = *temp;
            }
            delete temp;
        } else {
            Road* temp = findMin(road->right);
            road->id = temp->id;
            strcpy(road->place, temp->place);
            road->right = deletion(road->right, temp->id);
        }
    }

    if (road == nullptr) {
        return road;
    }

    road->height = 1 + std::max(getHeight(road->left), getHeight(road->right));
    int balance = getBalance(road);

    if (balance > 1 && getBalance(road->left) >= 0) {
        return rightRotate(road);
    }
    if (balance > 1 && getBalance(road->left) < 0) {
        road->left = leftRotate(road->left);
        return rightRotate(road);
    }
    if (balance < -1 && getBalance(road->right) <= 0) {
        return leftRotate(road);
    }
    if (balance < -1 && getBalance(road->right) > 0) {
        road->right = rightRotate(road->right);
        return leftRotate(road);
    }

    return road;
}

// Function to search for a road in the tree
Road* BinaryTree::search(Road* road, int id) {
    if (road == nullptr || road->id == id) {
        return road;
    }
    if (id < road->id) {
        return search(road->left, id);
    }
    return search(road->right, id);
}

// Function to find the minimum value node in the tree
Road* BinaryTree::findMin(Road* road) {
    while (road->left != nullptr) {
        road = road->left;
    }
    return road;
}

#endif // BUILD_TREE_HPP
