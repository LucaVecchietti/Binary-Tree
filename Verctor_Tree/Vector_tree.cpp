#include<iostream>
#include<vector>

using namespace std;

/*
    * VectorTree is a data structure that allows for efficient insertion of integers
    * and retrieval of the sum of values in a specified range across different versions.
    * It uses a binary tree structure to manage the values and their indices.
    * Each version of the tree can be accessed to get the sum of values between two indices.
    * It supports dynamic insertion of values and maintains a history of versions.
    * I called it VectorTree because it is desgned to work like a vector, but with a tree structure
    * to allow for efficient range queries and versioning.
*/

class VectorTree {
    private:
        // Node is the base class for both Leaf and Vertex
        class Node {
            public:
                virtual ~Node() {}
        };

        // Leaf represents a leaf node in the tree, which contains a value and its index
        class Leaf : public Node {
            public:
                int index;  // Index of the leaf in the vector
                int value;  // Value stored in the leaf
                Leaf(int val) : Node(), value(val) {}
        };
        // Vertex represents a vertex node in the tree, which contains a range and its value
        class Vertex : public Node {
            public:
                Node* left; // Pointer to the left child
                Node* right;    // Pointer to the right child
                int range;  // Range of indices covered by this vertex
                int start, end; // Start and end indices of the range
                int value;
                Vertex(void) : Node() , range(0), value(0), left(nullptr), right(nullptr) {}
        };

        vector <Node*> leaves;  // Vector to store all leaf nodes
        vector <Node*> roots;   // Vector to store the roots of different versions of the tree
        int size;   // Current size of the tree
        int node_number;    // Current number of nodes in the tree
        int version;    // Current version of the tree

        // Insert a value into the tree, creating new nodes as necessary
        // The function is recursive and handles the insertion logic based on the current size and node number
        void insert(int value, Node*& node, int start = 0, int end = -1) {
            if (end == -1) {
                end = size - 1;
            }

            if (size == 0) {
                Node* newNode = new Leaf(value);
                leaves.push_back(newNode);
                static_cast<Leaf*>(newNode)->index = node_number;
                node = newNode;
                size = 1;
                node_number = 1;
                return;
            }

            if (node == nullptr) {
                node = new Vertex();
                roots.push_back(node);
            }

            if (size == node_number){
                Node* newNode = new Vertex();
                size*=2;
                end = size - 1;
                static_cast<Vertex*>(newNode)->left = node;
                node = newNode;
            }

            if (start == end){
                Node* newNode = new Leaf(value);
                leaves.push_back(newNode);
                static_cast<Leaf*>(newNode)->index = node_number++;
                node = newNode;
                return;
            }

            int mid = (start + end) / 2;
            if (node_number > mid) {
                if (static_cast<Vertex*>(node)->right == nullptr) {
                    static_cast<Vertex*>(node)->right = new Vertex();
                }
                insert(value, static_cast<Vertex*>(node)->right, mid + 1, end);
            } else {
                if (static_cast<Vertex*>(node)->left == nullptr) {
                    static_cast<Vertex*>(node)->left = new Vertex();
                }
                insert(value, static_cast<Vertex*>(node)->left, start, mid);
            }

            Vertex* vertex = static_cast<Vertex*>(node);

            if (vertex->left) {
                if (dynamic_cast<Leaf*>(vertex->left)) {
                    vertex->value += static_cast<Leaf*>(vertex->left)->value;
                } else {
                    vertex->value += static_cast<Vertex*>(vertex->left)->value;
                }
            }
            if (vertex->right) {
                if (dynamic_cast<Leaf*>(vertex->right)) {
                    vertex->value += static_cast<Leaf*>(vertex->right)->value;
                } else {
                    vertex->value += static_cast<Vertex*>(vertex->right)->value;
                }
            }

            vertex->start = start;
            vertex->end = end;
            vertex->range = end - start + 1;

        }

        // Get the sum of values in the specified range [start, end] for a given version of the tree
        // The function traverses the tree recursively to find the sum of values in the specified range
        int GetSum(Node* node, int start, int end) {
            if (node == nullptr || start > end) {
                return 0;
            }
            
            Vertex* vertex = static_cast<Vertex*>(node);

            if (dynamic_cast<Leaf*>(node)) {
                Leaf* leaf = static_cast<Leaf*>(node);
                if (leaf->index >= start && leaf->index <= end) {
                    return leaf->value;
                } else {
                    return 0;
                }
            }

            if (start <= vertex->start && end >= vertex->end) {
                return vertex->value;
            }
            if (start > vertex->end || end < vertex->start) {
                return 0;
            }

            return GetSum(vertex->left, start, end) + GetSum(vertex->right, start, end);
        }

    public:

        // Constructor to initialize the VectorTree with an empty tree or with a vector of values
        // It initializes the size, node_number, and version, and sets the root to nullptr
        VectorTree(void) : size(0), node_number(0), version(0) {roots.push_back(nullptr);}
        VectorTree(vector <int> values) : size(0), node_number(0), version(0) {
            roots.push_back(nullptr);
            for (int val : values) {
                insert(val, roots[0]);
            }
        }

        // Insert a value into the tree, creating a new version of the tree
        // It increments the version and pushes a new root to the roots vector
        void insert(int value) {
            version++;
            roots.push_back(roots.back());
            insert(value, roots[version]);
        }

        // Get the value at a specific index in the leaves vector
        int getValue(int index) {
            if (index < 0 || index >= leaves.size()) {
                throw out_of_range("Index out of range");
            }
            return static_cast<Leaf*>(leaves[index])->value;
        }

        // Getters for size, node_number, version, and sum of values in a specified range
        int GetSize(void) {
            return size;
        }

        // Get the number of nodes in the tree
        int GetNodeNumber(void) {
            return node_number;
        }

        // Get the current version of the tree
        int GetVersion(void) {
            return version + 1;
        }

        // Get the sum of values in the specified range [start, end] for a given version of the tree
        int GetSum (int Version, int start, int end) {
            if (Version < 0 || Version > version) {
                throw out_of_range("Version out of range");
            }
            if (start < 0 || end >= size || start > end) {
                throw out_of_range("Range out of bounds");
            }

            Node* node = roots[Version];
            return GetSum(node, start, end);
        }

};

/*
    We can add new features to the VectorTree class, such as:
    - Support for removing values from the tree.
    - Support for updating values in the tree. Lazy updates can be implemented to avoid recalculating the entire tree.
    - Support for querying the minimum or maximum value in a specified range.
    - Support for more complex queries, such as finding the k-th smallest or largest value in a specified range.
    - Support for multi-threaded access to the tree, allowing concurrent insertions and queries.
    - Support for serialization and deserialization of the tree, allowing it to be saved to a file and loaded later.
    We can implement all these features like in every other tree data structure.
*/

int main() {
    cout << "Vector Tree Example" << endl;
    VectorTree tree;
    vector<int> values = {1, 2, 3, 4, 5};
    cout << "Inserting values into the tree..." << endl;
    for (int val : values) {
        tree.insert(val);
    }

    cout << "Size: " << tree.GetSize() << endl;
    cout << "Node Number: " << tree.GetNodeNumber() << endl;
    cout << "Version: " << tree.GetVersion() << endl;
    cout << "Values in the tree:" << endl;
    for (int i = 0; i < tree.GetNodeNumber(); i++) {
        cout << "Value at index " << i << ": " << tree.getValue(i) << endl;
    }

    int start = 0, end = 2;
    cout << "Sum from index " << start << " to " << end << ": " 
         << tree.GetSum(tree.GetVersion() - 1, start, end) << endl;

    return 0;
}