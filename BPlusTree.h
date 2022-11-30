#pragma once
#include <iostream>
using namespace std;
//forward declaration
template <class T>
class BPLusTree;
int MAX_KEYS = 10;
template <class T=int>
class Node {
    bool IS_LEAF; //indicating if it's a leaf 
    T* key;
    int size;   //size is the number of keys in a node, it changes with the addition of more keys
    Node** ptr; //double pointer to create 
    friend class BPLusTree<T>;
public:
    Node();
};
template <class T>
Node<T>::Node() {
    key = new T[MAX_KEYS];
    ptr = new Node * [MAX_KEYS + 1];
}
// BP tree
template <class T=int>
class BPLusTree {
    Node<T>* root;
    Node<T>* findParent(Node<T>*, Node<T>*); //this is used to find the parent of the node
    void insertInternalNode(int, Node<T>*, Node<T>*); //this function is used to insert a key in the internal node
public:
    BPLusTree();
    void search(int); //searching a key in the tree
    void insert(int); //inserting a key in the tree
    void display(Node<T>*); //displaying the tree
    Node<T>* getRoot(); //returning the root of the tree
    void deleteTree(Node<T>*); //deleting the tree
    ~BPLusTree();
};
template <class T>
BPLusTree<T>::BPLusTree() {
    root = NULL;
}
// Find the parent
template <class T>
Node<T>* BPLusTree<T>::findParent(Node<T>* cursor, Node<T>* child) {
    Node<T>* parent;
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
// Insert Operation
template <class T>
void BPLusTree<T>::insertInternalNode(int x, Node<T>* cursor, Node<T>* child) {
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
        Node<T>* newInternal = new Node<T>;
        int virtualKey[MAX_KEYS + 1];
        Node<T>* virtualPtr[MAX_KEYS + 2];
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
            Node<T>* newRoot = new Node<T>;
            newRoot->key[0] = cursor->key[cursor->size];
            newRoot->ptr[0] = cursor;
            newRoot->ptr[1] = newInternal;
            newRoot->IS_LEAF = false;
            newRoot->size = 1;
            root = newRoot;
        }
        else {
            insertInternalNode(cursor->key[cursor->size], findParent(root, cursor), newInternal);
        }
    }
}


template <class T>
// Search operation
void BPLusTree<T>::search(int x) {
    if (root == NULL) {
        cout << "Tree is empty\n";
    }
    else {
        Node<T>* cursor = root;
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

template <class T>
// Insert Operation
void BPLusTree<T>::insert(int x /*it's the incoming value*/) {
    if (root == NULL) {
        root = new Node<T>; 
        root->key[0] = x; //the first key of the root now has the value 'x'
        root->IS_LEAF = true; //initially the root is the leaf
        root->size = 1; //because only one key is added to the root
    }
    else {
        Node<T>* cursor = root;
        Node<T>* parent;
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
            Node<T>* newLeaf = new Node<T>;
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
                Node<T>* newRoot = new Node<T>;
                newRoot->key[0] = newLeaf->key[0];
                newRoot->ptr[0] = cursor;
                newRoot->ptr[1] = newLeaf;
                newRoot->IS_LEAF = false;
                newRoot->size = 1;
                root = newRoot;
            }
            else {
                insertInternalNode(newLeaf->key[0], parent, newLeaf);
            }
        }
    }
}


// Print the tree
template <class T>
void BPLusTree<T>::display(Node<T>* cursor) {
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
template <class T>
Node<T>* BPLusTree<T>::getRoot() {
    return root;
}
template <class T>
void BPLusTree<T>::deleteTree(Node<T>* cursor) {
    if (cursor != NULL) {
        if (cursor->IS_LEAF != true) {
            for (int i = 0; i < cursor->size + 1; i++) {
                deleteTree(cursor->ptr[i]);
            }
        }
        delete cursor;
    }
}
template<class T>
BPLusTree<T>::~BPLusTree()
{
    //delete tree
    deleteTree(root);
}