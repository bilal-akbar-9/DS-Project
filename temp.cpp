#include <bits/stdc++.h>
#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>
using namespace std;
// BP node
//this is the for b+ p
int MAX_KEYS = 3;
// Hello i am tauseef 
// i am a student of bsse
class Node {
    bool IS_LEAF; //indicating if it's a leaf 
    int* key, size;   //size is the number of keys in a node, it changes with the addition of more keys
    Node** ptr; //double pointer to create 
    friend class BPTree;
public:
    Node();
};

// BP tree
class BPTree {
    Node* root;
    void insertInternal(int, Node*, Node*);
    Node* findParent(Node*, Node*);
public:
    BPTree();
    void search(int);
    void insert(int);
    void display(Node*);
    Node* getRoot();
};

Node::Node() {
    key = new int[MAX_KEYS];
    ptr = new Node * [MAX_KEYS + 1];
}

BPTree::BPTree() {
    root = NULL;
}

// Search operation
void BPTree::search(int x) {
    if (root == NULL) {
        cout << "Tree is empty\n";
    }
    else {
        Node* cursor = root;
        while (cursor->IS_LEAF == false) {
            for (int i = 0; i < cursor->size; i++) {
                if (x < cursor->key[i]) {
                    cursor = cursor->ptr[i];
                    break;
                }
                if (i == cursor->size - 1) {
                    cursor = cursor->ptr[i + 1];
                    break;
                }
            }
        }
        for (int i = 0; i < cursor->size; i++) {
            if (cursor->key[i] == x) {
                cout << "Found\n";
                return;
            }
        }
        cout << "Not found\n";
    }
}

// Insert Operation
void BPTree::insert(int x /*it's the incoming value*/) {
    if (root == NULL) {
        root = new Node; 
        root->key[0] = x; //the first key of the root now has the value 'x'
        root->IS_LEAF = true; //initially the root is the leaf
        root->size = 1; //because only one key is added to the root
    }
    else {
        Node* cursor = root;
        Node* parent;
        while (cursor->IS_LEAF == false) {
            parent = cursor;
            for (int i = 0; i < cursor->size; i++) {
                if (x < cursor->key[i]) {
                    cursor = cursor->ptr[i];
                    break;
                }
                if (i == cursor->size - 1) {
                    cursor = cursor->ptr[i + 1];
                    break;
                }
            }
        }
        if (cursor->size < MAX_KEYS) {
            int i = 0;
            while (x > cursor->key[i] && i < cursor->size)
                i++;
            for (int j = cursor->size; j > i; j--) {
                cursor->key[j] = cursor->key[j - 1];
            }
            cursor->key[i] = x;
            cursor->size++;
            cursor->ptr[cursor->size] = cursor->ptr[cursor->size - 1];
                cursor->ptr[cursor->size - 1] = NULL;
        }
        else {
            Node* newLeaf = new Node;
            int virtualNode[MAX_KEYS + 1];
            for (int i = 0; i < MAX_KEYS; i++) {
                virtualNode[i] = cursor->key[i];
            }
            int i = 0, j;
            while (x > virtualNode[i] && i < MAX_KEYS)
                i++;
            for (int j = MAX_KEYS + 1; j > i; j--) {
                virtualNode[j] = virtualNode[j - 1];
            }
            virtualNode[i] = x;
            newLeaf->IS_LEAF = true;
            cursor->size = (MAX_KEYS + 1) / 2;
            newLeaf->size = MAX_KEYS + 1 - (MAX_KEYS + 1) / 2;
            cursor->ptr[cursor->size] = newLeaf;
            newLeaf->ptr[newLeaf->size] = cursor->ptr[MAX_KEYS];
            cursor->ptr[MAX_KEYS] = NULL;
            for (i = 0; i < cursor->size; i++) {
                cursor->key[i] = virtualNode[i];
            }
            for (i = 0, j = cursor->size; i < newLeaf->size; i++, j++) {
                newLeaf->key[i] = virtualNode[j];
            }
            if (cursor == root) {
                Node* newRoot = new Node;
                newRoot->key[0] = newLeaf->key[0];
                newRoot->ptr[0] = cursor;
                newRoot->ptr[1] = newLeaf;
                newRoot->IS_LEAF = false;
                newRoot->size = 1;
                root = newRoot;
            }
            else {
                insertInternal(newLeaf->key[0], parent, newLeaf);
            }
        }
    }
}

// Insert Operation
void BPTree::insertInternal(int x, Node* cursor, Node* child) {
    if (cursor->size < MAX_KEYS) {
        int i = 0;
        while (x > cursor->key[i] && i < cursor->size)
            i++;
        for (int j = cursor->size; j > i; j--) {
            cursor->key[j] = cursor->key[j - 1];
        }
        for (int j = cursor->size + 1; j > i + 1; j--) {
            cursor->ptr[j] = cursor->ptr[j - 1];
        }
        cursor->key[i] = x;
        cursor->size++;
        cursor->ptr[i + 1] = child;
    }
    else {
        Node* newInternal = new Node;
        int virtualKey[MAX_KEYS + 1];
        Node* virtualPtr[MAX_KEYS + 2];
        for (int i = 0; i < MAX_KEYS; i++) {
            virtualKey[i] = cursor->key[i];
        }
        for (int i = 0; i < MAX_KEYS + 1; i++) {
            virtualPtr[i] = cursor->ptr[i];
        }
        int i = 0, j;
        while (x > virtualKey[i] && i < MAX_KEYS)
            i++;
        for (int j = MAX_KEYS + 1; j > i; j--) {
            virtualKey[j] = virtualKey[j - 1];
        }
        virtualKey[i] = x;
        for (int j = MAX_KEYS + 2; j > i + 1; j--) {
            virtualPtr[j] = virtualPtr[j - 1];
        }
        virtualPtr[i + 1] = child;
        newInternal->IS_LEAF = false;
        cursor->size = (MAX_KEYS + 1) / 2;
        newInternal->size = MAX_KEYS - (MAX_KEYS + 1) / 2;
        for (i = 0, j = cursor->size + 1; i < newInternal->size; i++, j++) {
            newInternal->key[i] = virtualKey[j];
        }
        for (i = 0, j = cursor->size + 1; i < newInternal->size + 1; i++, j++) {
            newInternal->ptr[i] = virtualPtr[j];
        }
        if (cursor == root) {
            Node* newRoot = new Node;
            newRoot->key[0] = cursor->key[cursor->size];
            newRoot->ptr[0] = cursor;
            newRoot->ptr[1] = newInternal;
            newRoot->IS_LEAF = false;
            newRoot->size = 1;
            root = newRoot;
        }
        else {
            insertInternal(cursor->key[cursor->size], findParent(root, cursor), newInternal);
        }
    }
}

// Find the parent
Node* BPTree::findParent(Node* cursor, Node* child) {
    Node* parent;
    if (cursor->IS_LEAF || (cursor->ptr[0])->IS_LEAF) {
        return NULL;
    }
    for (int i = 0; i < cursor->size + 1; i++) {
        if (cursor->ptr[i] == child) {
            parent = cursor;
            return parent;
        }
        else {
            parent = findParent(cursor->ptr[i], child);
            if (parent != NULL)
                return parent;
        }
    }
    return parent;
}

// Print the tree
void BPTree::display(Node* cursor) {
    if (cursor != NULL) {
        for (int i = 0; i < cursor->size; i++) {
            cout << cursor->key[i] << " ";
        }
        cout << "\n";
        if (cursor->IS_LEAF != true) {
            for (int i = 0; i < cursor->size + 1; i++) {
                display(cursor->ptr[i]);
            }
        }
    }
}

// Get the root
Node* BPTree::getRoot() {
    return root;
}

int main() {
    BPTree node;
    node.insert(1);
    node.insert(4);
    node.insert(7);
    node.display(node.getRoot());
    cout << "***********************\n";
    node.insert(10);

    node.display(node.getRoot());
    cout << "***********************\n";
    node.insert(17);

    node.display(node.getRoot());
    cout << "***********************\n";
    node.insert(21);

    node.display(node.getRoot());
    cout << "***********************\n";
    node.insert(31);

    node.display(node.getRoot());
    cout << "***********************\n";
    node.insert(25);

    node.display(node.getRoot());
    cout << "***********************\n";
    node.insert(19);

    node.display(node.getRoot());
    cout << "***********************\n";
    node.insert(20);

    node.display(node.getRoot());
    cout << "***********************\n";
    node.insert(28);

    node.display(node.getRoot());
    cout << "***********************\n";
    node.insert(42);

    node.display(node.getRoot());
    cout << "***********************\n";
    node.insert(43);

    node.display(node.getRoot());
    cout << "***********************\n";
    // node.search(15);
}