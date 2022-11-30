#pragma once
#include <iostream>
using namespace std;
//forward declaration
template <class T>
class BPLusTree;
int MAX_KEYS = 50;
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
    //if the cursor is null, then return null
    if (cursor->IS_LEAF || (cursor->ptr[0])->IS_LEAF) {
        return NULL;
    }
    //if the child is the first pointer of the cursor, then return the cursor
    for (int i = 0; i < cursor->size + 1; i++) {
        //
        if (cursor->ptr[i] == child) {
            parent = cursor;
            return parent;
        }
        //if the child is not the first pointer of the cursor, then recursively call the function
        else {
            parent = findParent(cursor->ptr[i], child);
            if (parent != NULL) {
                return parent;
            }
        }
    }
    return parent;
}
// Insert Operation
template <class T>
void BPLusTree<T>::insertInternalNode(int x, Node<T>* cursor, Node<T>* child) {
    // If the node is not full
    if (cursor->size < MAX_KEYS) {
        int i = 0;
        // Find the position of the new key
        while (x > cursor->key[i] && i < cursor->size)
            i++;
        // Shifting the keys to the right
        for (int j = cursor->size; j > i; j--) {
            cursor->key[j] = cursor->key[j - 1];
        }
        // Inserting the new key
        for (int j = cursor->size + 1; j > i + 1; j--) {
            cursor->ptr[j] = cursor->ptr[j - 1];
        }
        cursor->key[i] = x;
        cursor->size++;
        cursor->ptr[i + 1] = child;
    }
    // If the node is full 
    else {
        Node<T>* newInternal = new Node<T>;
        int virtualKey[MAX_KEYS + 1];
        Node<T>* virtualPtr[MAX_KEYS + 2];
        // Copying the keys  to the virtual arrays
        for (int i = 0; i < MAX_KEYS; i++) {
            virtualKey[i] = cursor->key[i];
        }
        // Copying the pointers to the virtual array
        for (int i = 0; i < MAX_KEYS + 1; i++) {
            virtualPtr[i] = cursor->ptr[i];
        }
        int i = 0, j;
        // Find the position of the new key
        while (x > virtualKey[i] && i < MAX_KEYS)
            i++;
        // Shifting the keys to the right
        for (int j = MAX_KEYS + 1; j > i; j--) {
            virtualKey[j] = virtualKey[j - 1];
        }
        virtualKey[i] = x;
        // Shifting the pointers to the right
        for (int j = MAX_KEYS + 2; j > i + 1; j--) {
            virtualPtr[j] = virtualPtr[j - 1];
        }
        virtualPtr[i + 1] = child;
        newInternal->IS_LEAF = false;
        cursor->size = (MAX_KEYS + 1) / 2;
        newInternal->size = MAX_KEYS - (MAX_KEYS + 1) / 2;
        // Copying the first half of the keys to the original node
        for (i = 0, j = cursor->size + 1; i < newInternal->size; i++, j++) {
            newInternal->key[i] = virtualKey[j];
        }
        // Copying the first half of the pointers to the original node
        for (i = 0, j = cursor->size + 1; i < newInternal->size + 1; i++, j++) {
            newInternal->ptr[i] = virtualPtr[j];
        }
        // If the node is the root
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
     // If the node is not a leaf
        while (cursor->IS_LEAF == false) {
            
            for (int i = 0; i < cursor->size; i++) {
                // If the key is less than the current key
                if (x < cursor->key[i]) {
                    cursor = cursor->ptr[i];
                    break;
                }
                // If it's the last key of the node
                if (i == cursor->size - 1) {
                    cursor = cursor->ptr[i + 1];
                    break;
                }
            }
        }
        // If the node is a leaf 
        for (int i = 0; i < cursor->size; i++) {
            // If the key is found
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
        //insert the new key at the leaf node   
        while (cursor->IS_LEAF == false) {
            parent = cursor;
            for (int i = 0; i < cursor->size; i++) {
                // If the key is less than the current key
                if (x < cursor->key[i]) {
                    cursor = cursor->ptr[i];
                    break;
                }
                // If it's the last key of the node
                if (i == cursor->size - 1) {
                    cursor = cursor->ptr[i + 1];
                    break;
                }
            }
        }
        //if the leaf node is not full
        if (cursor->size < MAX_KEYS) {
            int i = 0;
            // Find the position of the new key
            while (x > cursor->key[i] && i < cursor->size)
                i++;
            // Shifting the keys to the right
            for (int j = cursor->size; j > i; j--) {
                cursor->key[j] = cursor->key[j - 1];
            }
            cursor->key[i] = x;
            cursor->size++;
            cursor->ptr[cursor->size] = cursor->ptr[cursor->size - 1]; //the last pointer of the leaf node is the same as the second last pointer
            cursor->ptr[cursor->size - 1] = NULL;
        }
        //if the leaf node is full
        else {
            Node<T>* newLeaf = new Node<T>; //create a new leaf node
            T virtualNode[MAX_KEYS + 1];
            //copy the keys of the current leaf node to the virtual node
            for (int i = 0; i < MAX_KEYS; i++) {
                virtualNode[i] = cursor->key[i];
            }
            int i = 0, j;
            //find the position of the new key
            while (x > virtualNode[i] && i < MAX_KEYS)
                i++;
            //shift the keys to the right
            for (int j = MAX_KEYS + 1; j > i; j--) {
                virtualNode[j] = virtualNode[j - 1];
            }
            //insert the new key
            virtualNode[i] = x; //the new key is inserted at the position 'i'
            newLeaf->IS_LEAF = true; 
            cursor->size = (MAX_KEYS + 1) / 2;
            newLeaf->size = MAX_KEYS + 1 - (MAX_KEYS + 1) / 2;
            cursor->ptr[cursor->size] = newLeaf;  //
            newLeaf->ptr[newLeaf->size] = cursor->ptr[MAX_KEYS];
            cursor->ptr[MAX_KEYS] = NULL;
            //copy the keys to the new leaf node
            for (i = 0; i < cursor->size; i++) {
                cursor->key[i] = virtualNode[i];
            }
            //copy the keys to the current leaf node
            for (i = 0, j = cursor->size; i < newLeaf->size; i++, j++) {
                newLeaf->key[i] = virtualNode[j];
            }
            //if the current leaf node is the root
            if (cursor == root) {
                Node<T>* newRoot = new Node<T>;
                newRoot->key[0] = newLeaf->key[0];
                newRoot->ptr[0] = cursor;
                newRoot->ptr[1] = newLeaf;
                newRoot->IS_LEAF = false;
                newRoot->size = 1;
                root = newRoot;
            }
            //if the current leaf node is not the root
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
        //
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