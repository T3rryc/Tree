#ifndef BUILD_TREE_HPP
#define BUILD_TREE_HPP

#include <cstring>

class Road {
public:
    int id;
    char place[100];
    Road* left;
    Road* right;

    Road(int id, const char* place) : id(id), left(nullptr), right(nullptr) {
        strcpy(this->place, place);
    }
};

class BinaryTree {
public:
    Road* root; // root of the binary tree

    BinaryTree() : root(nullptr) {} // constructor

    Road* insert(Road* road, int id, const char* place);
    Road* deletion(Road* road, int id);
    Road* search(Road* road, int id);
    Road* findMin(Road* road);
};

// Function definitions
Road* BinaryTree::insert(Road* road, int id, const char* place) {
    if (road == nullptr) {
        road = new Road(id, place);
    } else if (id < road->id) {
        road->left = insert(road->left, id, place);
    } else {
        road->right = insert(road->right, id, place);
    }
    return road;
}

Road* BinaryTree::deletion(Road* road, int id) {
    if (road == nullptr) {
        return nullptr;
    } else if (id < road->id) {
        road->left = deletion(road->left, id);
    } else if (id > road->id) {
        road->right = deletion(road->right, id);
    } else {
        if (road->left == nullptr && road->right == nullptr) {
            delete road;
            return nullptr;
        } else if (road->left == nullptr) {
            Road* temp = road;
            road = road->right;
            delete temp;
        } else if (road->right == nullptr) {
            Road* temp = road;
            road = road->left;
            delete temp;
        } else {
            Road* temp = findMin(road->right);
            road->id = temp->id;
            strcpy(road->place, temp->place);
            road->right = deletion(road->right, temp->id);
        }
    }
    return road;
}

Road* BinaryTree::search(Road* road, int id) {
    if (road == nullptr || road->id == id) {
        return road;
    } else if (id < road->id) {
        return search(road->left, id);
    } else {
        return search(road->right, id);
    }
}

Road* BinaryTree::findMin(Road* road) {
    while (road->left != nullptr) {
        road = road->left;
    }
    return road;
}


#endif
