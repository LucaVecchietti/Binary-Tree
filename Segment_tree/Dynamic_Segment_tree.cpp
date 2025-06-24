#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

/*
    * This function implements a dynamic segment tree with lazy propagation.
    * It allows for efficient range updates and range queries on an array.
    * The segment tree supports multiple versions, enabling historical queries.
    * It can insert values at specific indices and update ranges by adding a value to all elements in that range.
    * The sum of elements in a specified range can be queried for any version of the segment tree.
*/

class DynamicST {
   private:
       struct Node { // Structure for Dynamic Segment Tree Node
           int start, end, sum, update; // Start and end indices of the segment, sum of the segment, and update value
           Node *left, *right; // Pointers to the left and right children
   
           Node(int s, int e) : start(s), end(e), sum(0), update(0), left(nullptr), right(nullptr) {}
       };

        vector <Node*> roots; // Vector to store roots of different versions of the segment tree
        int currentVersion; // Current version of the segment tree
        int size; // Size of the segment tree

        void push(Node *&node) {
            if (node && node->update != 0) {
                node->sum += (node->end - node->start + 1) * node->update; // Update the sum with the lazy value
                if (node->left) {
                    node->left->update += node->update; // Propagate the update to the left child
                }
                if (node->right) {
                    node->right->update += node->update; // Propagate the update to the right child
                }
                node->update = 0; // Reset the update value after pushing
            }
        }

        void insert(int key, int value, Node *&node, int start = 0, int end = -1) {
            if (end == -1) end = size - 1; // Set end index if not provided
            if (!node) {
                node = new Node(start, end); // Create a new node if it doesn't exist
            }

            push(node); // Push any pending updates

            if (key < start || key > end) return; // Out of range

            if (start == end) {
                node->sum += value; // Update the sum at the leaf node
                return;
            }

            int mid = start + (end - start) / 2; // Calculate the midpoint
            if (key <= mid) {
                insert(key, value, node->left, start, mid); // Insert in the left subtree
            } else {
                insert(key, value, node->right, mid + 1, end); // Insert in the right subtree
            }
        }

        void UpdateRange(Node *&node, int start, int end, int value) {
            if (!node || start > node->end || end < node->start) return; // Out of range

            push(node); // Push any pending updates

            if (start <= node->start && end >= node->end) {
                node->update += value; // Apply the update lazily
                push(node); // Push the update to the current node
                return;
            }

            UpdateRange(node->left, start, end, value); // Update left subtree
            UpdateRange(node->right, start, end, value); // Update right subtree

            node->sum = (node->left ? node->left->sum : 0) + (node->right ? node->right->sum : 0); // Recalculate sum
        }

        int GetSum(Node *&node, int start, int end) {
            if (!node || start > node->end || end < node->start) return 0; // Out of range

            push(node); // Push any pending updates

            if (start <= node->start && end >= node->end) {
                return node->sum; // Return the sum if the range matches
            }

            int mid = node->start + (node->end - node->start) / 2; // Calculate the midpoint
            return GetSum(node->left, start, end) + GetSum(node->right, start, end); // Sum from both subtrees
        }

    public:
        DynamicST(int size) : size(size), currentVersion(0) {
            roots.push_back(nullptr); // Initialize with a null root for version 0
        }

        void insert(int key, int value) {
            insert(key, value, roots[currentVersion]);
            currentVersion++;
            roots.push_back(roots[currentVersion - 1]); // Create a new version based on the previous one
        }

        void UpdateRange(int start, int end, int value){
            UpdateRange(roots[currentVersion], start, end, value);
            currentVersion++;
            roots.push_back(roots[currentVersion - 1]); // Create a new version based on the previous one
        }

        int GetSum(int start, int end, int version = -1) {
            if (version = -1) version = currentVersion; // Use the current version if not specified
            return GetSum(roots[version], start, end);
        }

};

/*
    You can use this dynamic segment tree to perform operations like inserting values,
    updating ranges, and querying sums efficiently. you can create multiple versions of the segment tree
    to keep track of historical changes, allowing you to query the state of the segment tree at any previous version.
    This implementation supports lazy propagation for efficient range updates.
    You acn also modify the code to support more complex operations like range minimum queries, range maximum queries, etc.
    You can insert nested structures or additional variables in the Node structure to store more information,
    such as the number of elements in the segment, which can be useful for other operations.
*/

int main() {
    DynamicST segTree(100); // Create a dynamic segment tree with size 100

    segTree.insert(1, 5); // Insert value 5 at index 1
    segTree.insert(2, 10); // Insert value 10 at index 2
    segTree.UpdateRange(1, 2, 3); // Update range [1, 2] by adding 3

    cout << "Sum from index 1 to 2: " << segTree.GetSum(1, 2) << endl; // Should output 21 (5 + 10 + 3)

    return 0;
}
