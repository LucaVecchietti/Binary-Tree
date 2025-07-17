# Binary Tree 

This repository contain different binary tree implementation in C++. (Work in progress).  
Questa repository contiene l'implamantazione di diversi albari binari in C++. (Work in progress).  

- [AVL Tree](#🌲-AVL-Tree-in-C++-/-Albero-AVL-in-C++)
- [Segment Tree](#🌲-Segment-Tree-in-C++)
- [Vector Tree](#🌲-Vector-Tree-in-C++)

# 🌲 AVL Tree in C++ / Albero AVL in C++

This repository contains an efficient and minimal **AVL Tree** implementation in C++.  
Questa repository contiene un'implementazione semplice ed efficace di un **albero AVL** in linguaggio C++.

An AVL tree is a self-balancing binary search tree that guarantees `O(log n)` performance for insertion and deletion by maintaining tree height.  
Un albero AVL è una struttura dati auto-bilanciante che garantisce operazioni efficienti in `O(log n)` grazie al bilanciamento automatico dell'altezza.

---

## ✅ Features / Funzionalità

- ✅ Node insertion (`insert`)  
- ✅ Node deletion (`del`)  
- ✅ Automatic rebalancing with rotations (LL, RR, LR, RL)  
- ✅ Height and balance factor updates
<br>

- ✅ Inserimento dei nodi (`insert`)  
- ✅ Cancellazione dei nodi (`del`)  
- ✅ Ribilanciamento automatico tramite rotazioni (LL, RR, LR, RL)  
- ✅ Aggiornamento di altezza e fattore di bilanciamento

> 🔧 Planned Features / Funzionalità da aggiungere:
> - Search function (`search`)
> - Tree traversals (`inOrder`, `preOrder`, `postOrder`)
> - Console tree visualization

> - Funzione di ricerca (`search`)
> - Visite dell’albero (`inOrder`, `preOrder`, `postOrder`)
> - Visualizzazione dell’albero su console

---

## 🔍 Technical Overview / Dettagli tecnici

### Node structure / Struttura del nodo

```cpp
struct Node {
    int key;
    Node *left, *right;
    int height;
    int height_dif;
};
```

- `rotationRight()` → for Left-Left imbalance  
- `rotationLeft()` → for Right-Right imbalance  
- Combined rotations handle Left-Right and Right-Left cases
<br>

- `rotationRight()` → per squilibrio Left-Left  
- `rotationLeft()` → per squilibrio Right-Right  
- Le rotazioni combinate gestiscono i casi Left-Right e Right-Left
<br>

The `balance()` function updates the height and performs the appropriate rotation.  
La funzione `balance()` aggiorna l'altezza e applica la rotazione necessaria.

---

## 💡 Future Improvements / Miglioramenti futuri

- 🔍 Binary search function  
- 📤 In-order / Pre-order / Post-order traversals  
- 🖼️ Console or graphical tree visualization  
- 📊 Store metadata in nodes (e.g. subtree sizes)
<br>

- 🔍 Funzione di ricerca binaria  
- 📤 Visite in-order, pre-order, post-order  
- 🖼️ Visualizzazione dell’albero su console o graficamente  
- 📊 Memorizzazione di metadati nei nodi (es. numero di nodi nel sottoalbero)

---

# 🌲 Segment Tree in C++  

This repository contains an efficient and minimal **Static Segment Tree** and **Dynamic Segment Tree** implementation in C++.  
Questa repository contiene un'implementazione semplice ed efficace di un **Static Segment Tree** and **Dynamic Segment Tree** in linguaggio C++.  

A Segment tree is a binary search tree that guarantees `O(log n)` performance for operate query on a range of elements.  
Un Segment tree è un albero di ricerca binaria che garantisce lo svolgimento di operazioni su un range di elementi in `O(log n)`.  

---

## ✅ Features / Funzionalità  

### Static Segment Tree / Segment Tree Statico  

- :white_check_mark: Range update (`RangeUpdate`).  
- :white_check_mark: Get range sum (`GetSum`).  
- :white_check_mark: Lazy propagation for an efficient update.  
<br>

- :white_check_mark: Aggiornamento di un range (`RangeUpdate`).  
- :white_check_mark: Ottieni la somma di un range (`GetSum`).  
- :white_check_mark: Lazy propagation per aggiornamenti efficienti.

### Dynamic Segment Tree / Segment Tree Dinamico  

- :white_check_mark: Range update (`RangeUpdate`).  
- :white_check_mark: Get range sum (`GetSum`).  
- :white_check_mark: Lazy propagation for an efficient update.
- :white_check_mark: Insert nodes only if needed (`insert`).  
- :white_check_mark: Supports multiple versions, enabling historical queries.  
<br>

- :white_check_mark: Aggiornamento di un range (`RangeUpdate`).  
- :white_check_mark: Ottieni la somma di un range (`GetSum`).  
- :white_check_mark: Lazy propagation per aggiornamenti efficienti.
- :white_check_mark: Inserisci i nodi solo se necessario (`insert`).  
- :white_check_mark: Supporta più versioni, rendendo possibili operazioni sullo storico.

## 🔍 Technical Overview / Dettagli tecnici

### Node structure / Struttura del nodo  (Static Segment Tree)

```cpp
struct Node { 
    int start, end, sum, update;    
    Node *left, *right; 

    Node(int s, int e) : start(s), end(e), sum(0), update(0), left(nullptr), right(nullptr) {}
};
```
- `push()` → for push the update to the children nodes
- The push() function is used to manage the lazy propagation  
- `UpdateRange()` → for update all the elements in a given range  
- `GetSum()` → for query the sum in a given range
<br>

- `push()` → per propagare l'aggiornamento ai nodi figli
- La funzione  push() serve per gestire la propagazione pigra dell'aggiornamento  
- `UpdateRange()` → per aggiornare un range di elementi  
- `GetSum()` → per ottenere la somma di un range di elementi

### Tree structure / Struttura dell'albero (Dynamic Segment Tree)

```cpp
class DynamicST {
    private:

        struct Node { 
            int start, end, sum, update; 
            Node *left, *right;

            Node(int s, int e) : start(s), end(e), sum(0), update(0), left(nullptr), right(nullptr) {}
        };
        
        vector <Node*> roots; 
        int currentVersion; 
        int size;

        void push(Node *&node) {}

        void insert(int key, int value, Node *&node, int start = 0, int end = -1) {}

        void UpdateRange(Node *&node, int start, int end, int value) {}

        int GetSum(Node *&node, int start, int end) {}

    public:
        DynamicST(int size) : size(size), currentVersion(0) {}

        void insert(int key, int value) {}

        void UpdateRange(int start, int end, int value){}

        int GetSum(int start, int end, int version = -1) {}

};
```

- `insert()' → for insert a new node
- If a node is inserted in a position alredy occupied the previus node will be replaced  
- `push()` → for push the update to the children nodes  
- The push() function is used to manage the lazy propagation  
- `UpdateRange()` → for update all the elements in a given range  
- `GetSum()` → for query the sum in a given range  
<br>

- `insert()' → per inserire un nuovo nodo
- Se un nodo viene inserito in una posizione già occupata il non preceente verrà sostituito  
- `push()` → per propagare l'aggiornamento ai nodi figli  
- La funzione  push() serve per gestire la propagazione pigra dell'aggiornamento  
- `UpdateRange()` → per aggiornare un range di elementi  
- `GetSum()` → per ottenere la somma di un range di elementi  
<br>

The `vector <*Node> roots` is used to store every new version of the tree.  
Il `vector <*Node> roots` serve per memorizzare ogni nuova versione dell'albero.  

# 🌲Vector Tree in C++

A Vector Tree is not a tree of vector, but I just call it with this name because it is a dynamic segment tree that works like a vector.  
When we insert a new node in the tree, but the tree is 'full', the vector tree create a new root end the old tree became the left tree of the new tree.  
So the size of the new tree is double.  

Un Vector Tree non è un albero di vettori, ma sono io che lo ho chiamto così perchè consiste in un segment tree dinamico che funziona come un vettore.  
Quando inseriamo un nuovo nodo nell'albero, ma l'albero è 'pieno', il vector tree crea una nuova radice e il vecchio albero diventa l'albero sinistro del nuovo albero.  
Quindi la dimensione del nuovo albero è il doppio.  

## ✅ Features / Funzionalità  

- ✅ Supports multiple versions, enabling historical queries.  
- ✅ Insert values like in a vector. ('insert()')  
- ✅ Get the value of the leaves using a index. ('getValue()')
- ✅ Support implementation of range queries. EX: ('GetSum()')
<br>

- ✅ Supporta più versioni, rendendo possibile operazioni sullo storico.  
- ✅ Inserisci valori come in un vettore. ('insert()')  
- ✅ Ottieni il valore delle foglie utilizzando in indice. ('getValue()')  
- ✅ Supporta l'implementazione di operazioni sui range. Es: ('GetSum()')

## 🔍 Technical Overview / Dettagli tecnici

### Node structure / Struttura del nodo  (Vector Tree)  

```cpp
class Node {
    public:
        virtual ~Node() {}
};

class Leaf : public Node {
    public:
        int index;  
        int value;  
        Leaf(int val) : Node(), value(val) {}
};

class Vertex : public Node {
    public:
        Node* left; 
        Node* right;    
        int range;  
        int start, end; 
        int value;
        Vertex(void) : Node() , range(0), value(0), left(nullptr), right(nullptr) {}
};
```

### Tree structure / Struttura dell'albero (Vector Tree)  

```cpp
class VectorTree {
    private:
        class Node {};

        class Leaf : public Node {};
        
        class Vertex : public Node {};

        vector <Node*> leaves;
        vector <Node*> roots;
        int size;
        int node_number;
        int version;

        void insert(int value, Node*& node, int start = 0, int end = -1) {}

        int GetSum(Node* node, int start, int end) {}

    public:

        VectorTree(void) : size(0), node_number(0), version(0) {}
        VectorTree(vector <int> values) : size(0), node_number(0), version(0) {}

        void insert(int value) {}

        int getValue(int index) {}

        int GetSize(void) {}

        int GetNodeNumber(void) {}

        int GetVersion(void) {}

        int GetSum (int Version, int start, int end) {}

};
```

- 'insert()' -> for insert a new node.
- 'insert()' is similar to the push_back function of the vector.
- 'getValue()' -> for get the value of a leaf.
- 'Getsize()' -> for get the size of the tree, so the number of leavs that can contain befor change size.
- 'GetNodeNumber()' -> for get the number of leaves inserted.
- 'GetVersion()' -> to get the number of versions.
- 'GetSum()' -> Range sum.
<br>  

- 'insert()' -> per inserire un nuovo nodo.  
- 'insert()' è simile alla funzione push_back di un vector.  
- 'getValue()' -> per ottenere il valore di una foglia.  
- 'Getsize()' -> per ottenere la dimensione dell'albero, ovvero il numero di foglie che può contenere prima di dover cambiare dimensione.  
- 'GetNodeNumber()' -> per ottenere il numero di foglie inserite.  
- 'GetVersion()' -> per ottenere il numero di versioni.  
- 'GetSum()' -> somma su un intervallo.
<br>


## 🧑‍💻 Author / Autore

Project developed for educational purposes.  
Progetto sviluppato a scopo didattico.

---

## 📄 License / Licenza

This project is open-source and free to use.  
Questo progetto è open-source e liberamente utilizzabile.
