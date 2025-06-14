/*
    * AVL Tree Implementation in C++
    * This code implements an AVL tree with insertion functionality.
    * It maintains the balance of the tree after each insertion. 
*/


#include <iostream>
#include <algorithm>
using namespace std;

struct Node { // Structure for AVL Tree Node

    // Each node contains a key, pointers to left and right children, height, and height difference
    // The height is used to maintain the balance of the AVL tree
    // The height difference is used to determine the type of rotation needed for balancing
    // The key is the value stored in the node

    int key;
    Node *left, *right;
    int height;
    int height_dif;

    //Add here additional variables or structures if needed for other operations

    Node(int k) : key(k), left(nullptr), right(nullptr), height(1) {}
};

// Function to get the height of a node
int height(Node *N) {
    return N ? N->height : 0;
}

// Function to perform right rotation
void rotationRight(Node *&node) {
    Node *temp = node->left;
    node->left = temp->right;
    temp->right = node;
    node->height = 1 + max(height(node->left), height(node->right));
    temp->height = 1 + max(height(temp->left), height(temp->right));
    node = temp;
}

// Function to perform left rotation
void rotationLeft(Node *&node) {
    Node *temp = node->right;
    node->right = temp->left;
    temp->left = node;
    node->height = 1 + max(height(node->left), height(node->right));
    temp->height = 1 + max(height(temp->left), height(temp->right));
    node = temp;
}

void balance(Node *&node) {
    /*
        * This function checks the balance of the AVL tree and performs rotations if necessary.
        * It is called after every insertion to ensure the tree remains balanced.
    */
    if (!node) return;

    node->height = 1 + max(height(node->left), height(node->right));
    node->height_dif = height(node->left) - height(node->right);

    if (node->height_dif > 1) {
        if (node->left->height_dif >= 0) {
            rotationRight(node); // Left Left Case
        } else {
            rotationLeft(node->left); // Left Right Case
            rotationRight(node); // After left rotation, perform right rotation
        }
    } else if (node->height_dif < -1) {
        if (node->right->height_dif <= 0) {
            rotationLeft(node); // Right Right Case
        } else {
            rotationRight(node->right); // Right Left Case
            rotationLeft(node); // After right rotation, perform left rotation
        }
    }

    node->height = 1 + max(height(node->left), height(node->right));
    node->height_dif = height(node->left) - height(node->right);
    
}

void insert(Node *&node, int key) {

    /*
        * This function inserts a new key into the AVL tree.
        * It first finds the correct position for the new key,
        * then updates the height and height difference of the nodes,
        * and finally performs rotations to maintain the balance of the tree.
    */

    if (!node) {
        node = new Node(key);
        return;
    }
    if (key < node->key) {
        insert(node->left, key);
    } else if (key > node->key) {
        insert(node->right, key);
    } else {
        return; // Duplicate keys are not allowed
    }

    balance(node); // Balance the tree after insertion

}

void del(Node *&node, int key) {
    /*
        * This function deletes a key from the AVL tree.
        * It first finds the node to be deleted, then handles three cases:
        * 1. Node with no child
        * 2. Node with one child
        * 3. Node with two children (in which case it finds the inorder successor)
        * After deletion, it updates the height and height difference of the nodes,
        * and performs rotations to maintain the balance of the tree.
    */

    if (!node) return;
    if (key < node->key) {
        del(node->left, key);
    } else if (key > node->key) {
        del(node->right, key);
    } else {
        // Node with only one child or no child
        if (!node->left || !node->right) {
            Node *temp = node->left ? node->left : node->right;
            if (!temp) {
                temp = node;
                node = nullptr;
            } else {
                *node = *temp; // Copy the contents of the non-empty child
            }
            delete temp;
        } else {
            // Node with two children: Get the inorder successor (smallest in the right subtree)
            Node *temp = node->right;
            while (temp && temp->left) {
                temp = temp->left;
            }
            node->key = temp->key; // Copy the inorder successor's content to this node
            del(node->right, temp->key); // Delete the inorder successor
        }
    }

    if (!node) return; // If the tree is empty after deletion
    balance(node); // Balance the tree after deletion

}

/*
To implement the AVL tree fully, you can add functions to search for a key,
display the tree, and traverse it in different orders (inorder, preorder, postorder).
The easiest way to search for a key it to use a binary search tree search algorithm.
You can also add different variable or structures in the Node structures to store additional information
like the number of nodes in the subtree, which can be useful for other operations.
*/

int main() {
    Node *root = nullptr;
    int keys[] = {10, 20, 30, 40, 50, 25};

    for (int key : keys) {
        insert(root, key);
    }

    cout << "AVL Tree constructed successfully." << endl;

    // Additional code to display or manipulate the AVL tree can be added here.

    return 0;
}