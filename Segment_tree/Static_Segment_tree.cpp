#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

/*
    * This function implements a static segment tree with lazy propagation.
    * It allows for efficient range updates and range queries on an array.
    * The segment tree is built from a given array, and it supports updating a range
    * by adding a value to all elements in that range, as well as querying the sum of elements
    * in a specified range.
*/

struct Node { // Structure for Segment Tree Node
    int start, end, sum, update;    // Start and end indices of the segment, and the sum of the segment
    Node *left, *right; // Pointers to the left and right children

    Node(int s, int e) : start(s), end(e), sum(0), update(0), left(nullptr), right(nullptr) {}
};

// Function to build the segment tree from the given array
void build(Node *&node, int start = 0, int end = -1, vector <int> &arr){
    if (end == -1) end = arr.size() - 1;
    node = new Node(start, end);
    
    if (start == end) {
        node->sum = arr[start];
        return;
    }
    
    int mid = start + (end - start) / 2;
    build(node->left, start, mid, arr);
    build(node->right, mid + 1, end, arr);
    
    node->sum = node->left->sum + node->right->sum;
}

// Overloaded function to build the segment tree from a raw array
void build(Node *&node, int start = 0, int end = -1, int *arr){
    if (end == -1) cout << "Error: end index not set." << endl;
    node = new Node(start, end);
    
    if (start == end) {
        node->sum = arr[start];
        return;
    }
    
    int mid = start + (end - start) / 2;
    build(node->left, start, mid, arr);
    build(node->right, mid + 1, end, arr);
    
    node->sum = node->left->sum + node->right->sum;

}

void push(Node *&node) {
    if (node->update != 0) {
        node->sum += (node->end - node->start + 1) * node->update;
        if (node->left) {
            node->left->update += node->update;
            node->right->update += node->update;
        }
        node->update = 0; // Reset the update value after pushing
    }
}

// Function to query the sum in a given range
void UpdateRange(Node *&node, int start, int end, int value){
    if (!node || start > node->end || end < node->start) return; // Out of range
    push(node); // Push any pending updates

    if (start <= node->start && end >= node->end) {
        node->update += value; // Mark the update
        push(node); // Apply the update immediately
        return;
    }

    UpdateRange(node->left, start, end, value);
    UpdateRange(node->right, start, end, value);
    
    node->sum = node->left->sum + node->right->sum; // Update the sum after changes
}

// Function to get the sum in a given range
int GetSum(Node *&node, int start, int end) {
    if (!node || start > node->end || end < node->start) return 0; // Out of range
    push(node); // Push any pending updates

    if (start <= node->start && end >= node->end) {
        return node->sum; // Return the sum for the segment
    }

    int leftSum = GetSum(node->left, start, end);
    int rightSum = GetSum(node->right, start, end);
    
    return leftSum + rightSum; // Combine results from both segments
}

/*
you can use this segment tree to perform range updates and queries efficiently.
For example, you can build the tree from an array, update a range by adding a value, and query the sum of a range.
you can also add more functionalities like range minimum queries or range maximum queries by modifying the Node structure and the functions accordingly.
*/

int main() {
    vector<int> arr = {1, 2, 3, 4, 5}; // Example array
    Node *root = nullptr;
    
    build(root, 0, arr.size() - 1, arr); // Build the segment tree

    cout << "Initial sum of range (0, 4): " << GetSum(root, 0, 4) << endl; // Should print 15

    UpdateRange(root, 1, 3, 10); // Update range [1, 3] by adding 10

    cout << "Sum after update of range (0, 4): " << GetSum(root, 0, 4) << endl; // Should print 25

    return 0;
}