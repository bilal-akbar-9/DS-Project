#pragma once
#include"./include.h"
//forward declaration
template <class T>
class BPLusTree;
int MAX_KEYS = 5;
template <class T=int>
class Node {
    bool isLeaf; //indicating if it's a leaf 
    T* key;
    int size;   //size is the number of keys in a node, it changes with the addition of more keys
    Node** ptr; //double pointer to create 
    Student** studentPtr;
    friend class BPLusTree<T>;
    template <class Y>
    friend void PointToLinkedList(BPLusTree<Y>&, StudentList&);
    template <class Y>
    friend void PointToLinkedListString(BPLusTree<Y>&, StudentList&);
public:
    Node();
};
template <class T>
Node<T>::Node() {
    key = new T[MAX_KEYS];
    ptr = new Node * [MAX_KEYS + 1];
    studentPtr = new Student * [MAX_KEYS];
}
// BP tree
template <class T=int>
class BPLusTree {
    Node<T>* root;
    Node<T>* findParent(Node<T>*, Node<T>*); //this is used to find the parent of the node
    void insertInternalNode(int, Node<T>*, Node<T>*); //this function is used to insert a key in the internal node
    void insertInternalNodeString(string, Node<T>*, Node<T>*); //this function is used to insert a key in the internal node
    //why different functions for int and string? because we can't compare two strings with > or < operators
public:
    BPLusTree();
    void displayParticular(T); //searching a key in the tree
    void displayParticularString(string);
    void displayThroughleafs(Node<T>*); //displaying the keys in the tree
    void insert(int); //inserting a key in the tree
    void insertString(string); //inserting a key in the tree
    Node<T>* getRoot(); //returning the root of the tree
    void display(Node<T>*); //displaying the tree
    void displayBetweenRange(Node<T>*, int x, int y); //displaying the tree through the leaf nodes
    void deleteTree(Node<T>*); //deleting the tree
    ~BPLusTree();
};
template <class T>
BPLusTree<T>::BPLusTree() {
    root = NULL;
}
// Find the parent
template <class T>
Node<T>* BPLusTree<T>::findParent(Node<T>* nodePtr, Node<T>* child) {
    Node<T>* parent;
    //if the nodePtr is null, then return null
    if (nodePtr->isLeaf || (nodePtr->ptr[0])->isLeaf) {
        return NULL;
    }
    //if the child is the first pointer of the nodePtr, then return the nodePtr
    for (int i = 0; i < nodePtr->size + 1; i++) {
        //
        if (nodePtr->ptr[i] == child) {
            parent = nodePtr;
            return parent;
        }
        //if the child is not the first pointer of the nodePtr, then recursively call the function
        else {
            parent = findParent(nodePtr->ptr[i], child);
            if (parent != NULL) {
                return parent;
            }
        }
    }
    return parent;
}

template <class T>
// Insert Operation
void BPLusTree<T>::insert(int x /*it's the incoming value*/) {
    if (root == NULL) {
        root = new Node<T>;
        root->key[0] = x; //the first key of the root now has the value 'x'
        root->isLeaf = true; //initially the root is the leaf
        root->size = 1; //because only one key is added to the root
    }
    else {
        Node<T>* nodePtr = root;
        Node<T>* parent;
        //insert the new key at the leaf node   
        while (nodePtr->isLeaf == false) {
            parent = nodePtr;
            for (int i = 0; i < nodePtr->size; i++) {
                // If the key is less than the current key
                if (x < nodePtr->key[i]) {
                    nodePtr = nodePtr->ptr[i];
                    break;
                }
                // If it's the last key of the node
                if (i == nodePtr->size - 1) {
                    nodePtr = nodePtr->ptr[i + 1];
                    break;
                }
            }
        }
        //if the leaf node is not full
        if (nodePtr->size < MAX_KEYS) {
            int i = 0;
            // Find the position of the new key
            while (x > nodePtr->key[i] && i < nodePtr->size)
                i++;
            // Shifting the keys to the right
            for (int j = nodePtr->size; j > i; j--) {
                nodePtr->key[j] = nodePtr->key[j - 1];
            }
            nodePtr->key[i] = x;
            nodePtr->size++;
            nodePtr->ptr[nodePtr->size] = nodePtr->ptr[nodePtr->size - 1]; //the last pointer of the leaf node is the same as the second last pointer
            nodePtr->ptr[nodePtr->size - 1] = NULL;
        }
        //if the leaf node is full
        else {
            Node<T>* newLeaf = new Node<T>; //create a new leaf node
            T virtualNode[MAX_KEYS + 2];
            //copy the keys of the current leaf node to the virtual node
            for (int i = 0; i < MAX_KEYS; i++) {
                virtualNode[i] = nodePtr->key[i];
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
            newLeaf->isLeaf = true;
            nodePtr->size = (MAX_KEYS + 1) / 2;
            newLeaf->size = MAX_KEYS + 1 - (MAX_KEYS + 1) / 2;
            nodePtr->ptr[nodePtr->size] = newLeaf;  //
            newLeaf->ptr[newLeaf->size] = nodePtr->ptr[MAX_KEYS];
            nodePtr->ptr[MAX_KEYS] = NULL;
            //copy the keys to the new leaf node
            for (i = 0; i < nodePtr->size; i++) {
                nodePtr->key[i] = virtualNode[i];
            }
            //copy the keys to the current leaf node
            for (i = 0, j = nodePtr->size; i < newLeaf->size; i++, j++) {
                newLeaf->key[i] = virtualNode[j];
            }
            //if the current leaf node is the root
            if (nodePtr == root) {
                Node<T>* newRoot = new Node<T>;
                newRoot->key[0] = newLeaf->key[0];
                newRoot->ptr[0] = nodePtr;
                newRoot->ptr[1] = newLeaf;
                newRoot->isLeaf = false;
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

// Insert Operation
template <class T>
void BPLusTree<T>::insertInternalNode(int x, Node<T>* nodePtr, Node<T>* child) {
    // If the node is not full
    if (nodePtr->size < MAX_KEYS) {
        int i = 0;
        // Find the position of the new key
        while (x > nodePtr->key[i] && i < nodePtr->size)
            i++;
        // Shifting the keys to the right
        for (int j = nodePtr->size; j > i; j--) {
            nodePtr->key[j] = nodePtr->key[j - 1];
        }
        // Inserting the new key
        for (int j = nodePtr->size + 1; j > i + 1; j--) {
            nodePtr->ptr[j] = nodePtr->ptr[j - 1];
        }
        nodePtr->key[i] = x;
        nodePtr->size++;
        nodePtr->ptr[i + 1] = child;
    }
    // If the node is full 
    else {
        Node<T>* newInternal = new Node<T>;
        T virtualKey[MAX_KEYS + 2];
        Node<T>* virtualPtr[MAX_KEYS + 3];
        // Copying the keys  to the virtual arrays
        for (int i = 0; i < MAX_KEYS; i++) {
            virtualKey[i] = nodePtr->key[i];
        }
        // Copying the pointers to the virtual array
        for (int i = 0; i < MAX_KEYS + 1; i++) {
            virtualPtr[i] = nodePtr->ptr[i];
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
        newInternal->isLeaf = false;
        nodePtr->size = (MAX_KEYS + 1) / 2;
        newInternal->size = MAX_KEYS - (MAX_KEYS + 1) / 2;
        // Copying the first half of the keys to the original node
        for (i = 0, j = nodePtr->size + 1; i < newInternal->size; i++, j++) {
            newInternal->key[i] = virtualKey[j];
        }
        // Copying the first half of the pointers to the original node
        for (i = 0, j = nodePtr->size + 1; i < newInternal->size + 1; i++, j++) {
            newInternal->ptr[i] = virtualPtr[j];
        }
        // If the node is the root
        if (nodePtr == root) {
            Node<T>* newRoot = new Node<T>;
            newRoot->key[0] = nodePtr->key[nodePtr->size];
            newRoot->ptr[0] = nodePtr;
            newRoot->ptr[1] = newInternal;
            newRoot->isLeaf = false;
            newRoot->size = 1;
            root = newRoot;
        }
        else {
            insertInternalNode(nodePtr->key[nodePtr->size], findParent(root, nodePtr), newInternal);
        }
    }
}
template <class T>
void BPLusTree<T>::insertString(string x /*it's the incoming value*/) {
    if (root == NULL) {
        root = new Node<T>;
        root->key[0] = x; //the first key of the root now has the value 'x'
        root->isLeaf = true; //initially the root is the leaf
        root->size = 1; //because only one key is added to the root
    }
    else {
        Node<T>* nodePtr = root;
        Node<T>* parent;
        //insert the new key at the leaf node   
        while (nodePtr->isLeaf == false) {
            parent = nodePtr;
            for (int i = 0; i < nodePtr->size; i++) {
                // If the key is less than the current key
                if (x.compare(nodePtr->key[i]) < 0) {
                    nodePtr = nodePtr->ptr[i];
                    break;
                }
                // If it's the last key of the node
                if (i == nodePtr->size - 1) {
                    nodePtr = nodePtr->ptr[i + 1];
                    break;
                }
            }
        }
        //if the leaf node is not full
        if (nodePtr->size < MAX_KEYS) {
            int i = 0;
            // Find the position of the new key
            while /*compare returns 0 if the secound string is bigger than the first one */ (x.compare(nodePtr->key[i]) > 0 && i < nodePtr->size)
                i++;
            // Shifting the keys to the right
            for (int j = nodePtr->size; j > i; j--) {
                nodePtr->key[j] = nodePtr->key[j - 1];
            }
            nodePtr->key[i] = x;
            nodePtr->size++;
            nodePtr->ptr[nodePtr->size] = nodePtr->ptr[nodePtr->size - 1]; //the last pointer of the leaf node is the same as the second last pointer
            nodePtr->ptr[nodePtr->size - 1] = NULL;
        }
        //if the leaf node is full
        else {
            Node<T>* newLeaf = new Node<T>; //create a new leaf node
            T virtualNode[MAX_KEYS + 2];
            //copy the keys of the current leaf node to the virtual node
            for (int i = 0; i < MAX_KEYS; i++) {
                virtualNode[i] = nodePtr->key[i];
            }
            int i = 0, j;
            //find the position of the new key
            while (x.compare(virtualNode[i]) > 0 && i < MAX_KEYS)
                i++;
            //shift the keys to the right
            for (int j = MAX_KEYS + 1; j > i; j--) {
                virtualNode[j] = virtualNode[j - 1];
            }
            //insert the new key
            virtualNode[i] = x; //the new key is inserted at the position 'i'
            newLeaf->isLeaf = true;
            nodePtr->size = (MAX_KEYS + 1) / 2;
            newLeaf->size = MAX_KEYS + 1 - (MAX_KEYS + 1) / 2;
            nodePtr->ptr[nodePtr->size] = newLeaf;  //
            newLeaf->ptr[newLeaf->size] = nodePtr->ptr[MAX_KEYS];
            nodePtr->ptr[MAX_KEYS] = NULL;
            //copy the keys to the new leaf node
            for (i = 0; i < nodePtr->size; i++) {
                nodePtr->key[i] = virtualNode[i];
            }
            //copy the keys to the current leaf node
            for (i = 0, j = nodePtr->size; i < newLeaf->size; i++, j++) {
                newLeaf->key[i] = virtualNode[j];
            }
            //if the current leaf node is the root
            if (nodePtr == root) {
                Node<T>* newRoot = new Node<T>;
                newRoot->key[0] = newLeaf->key[0];
                newRoot->ptr[0] = nodePtr;
                newRoot->ptr[1] = newLeaf;
                newRoot->isLeaf = false;
                newRoot->size = 1;
                root = newRoot;
            }
            //if the current leaf node is not the root
            else {
                insertInternalNodeString(newLeaf->key[0], parent, newLeaf);
            }
        }
    }
}

template <class T>
void BPLusTree<T>::insertInternalNodeString(string x, Node<T>* nodePtr, Node<T>* child) {
    // If the node is not full
    if (nodePtr->size < MAX_KEYS) {
        int i = 0;
        // Find the position of the new key
        while (x.compare(nodePtr->key[i]) > 0 && i < nodePtr->size)
            i++;
        // Shifting the keys to the right
        for (int j = nodePtr->size; j > i; j--) {
            nodePtr->key[j] = nodePtr->key[j - 1];
        }
        // Inserting the new key
        for (int j = nodePtr->size + 1; j > i + 1; j--) {
            nodePtr->ptr[j] = nodePtr->ptr[j - 1];
        }
        nodePtr->key[i] = x;
        nodePtr->size++;
        nodePtr->ptr[i + 1] = child;
    }
    // If the node is full 
    else {
        Node<T>* newInternal = new Node<T>;
        T virtualKey[MAX_KEYS + 2];
        Node<T>* virtualPtr[MAX_KEYS + 3];
        // Copying the keys  to the virtual arrays
        for (int i = 0; i < MAX_KEYS; i++) {
            virtualKey[i] = nodePtr->key[i];
        }
        // Copying the pointers to the virtual array
        for (int i = 0; i < MAX_KEYS + 1; i++) {
            virtualPtr[i] = nodePtr->ptr[i];
        }
        int i = 0, j;
        // Find the position of the new key
        while (x.compare(virtualKey[i]) > 0 && i < MAX_KEYS)
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
        newInternal->isLeaf = false;
        nodePtr->size = (MAX_KEYS + 1) / 2;
        newInternal->size = MAX_KEYS - (MAX_KEYS + 1) / 2;
        // Copying the first half of the keys to the original node
        for (i = 0, j = nodePtr->size + 1; i < newInternal->size; i++, j++) {
            newInternal->key[i] = virtualKey[j];
        }
        // Copying the first half of the pointers to the original node
        for (i = 0, j = nodePtr->size + 1; i < newInternal->size + 1; i++, j++) {
            newInternal->ptr[i] = virtualPtr[j];
        }
        // If the node is the root
        if (nodePtr == root) {
            Node<T>* newRoot = new Node<T>;
            newRoot->key[0] = nodePtr->key[nodePtr->size];
            newRoot->ptr[0] = nodePtr;
            newRoot->ptr[1] = newInternal;
            newRoot->isLeaf = false;
            newRoot->size = 1;
            root = newRoot;
        }
        else {
            insertInternalNodeString(nodePtr->key[nodePtr->size], findParent(root, nodePtr), newInternal);
        }
    }
}
template <class T>
Node<T>* BPLusTree<T>::getRoot() {
    return root;
}
// Print the tree
template <class T>
void BPLusTree<T>::display(Node<T>* nodePtr) {
    if (nodePtr != NULL) {
        //
        for (int i = 0; i < nodePtr->size; i++) {
            cout << nodePtr->key[i] << " ";
        }
        cout << "\n";
        if (nodePtr->isLeaf != true) {
            for (int i = 0; i < nodePtr->size + 1; i++) {
                display(nodePtr->ptr[i]);
            }
        }
    }
}

template <class T>
void BPLusTree<T>::displayBetweenRange(Node<T>* nodePtr, int x, int y) {
    while (nodePtr->isLeaf == false) {
        for (int i = 0; i < nodePtr->size; i++) {
            // If the key is less than the current key
            if (x < nodePtr->key[i]) {
                nodePtr = nodePtr->ptr[i];
                break;
            }
            // If it's the last key of the node
            if (i == nodePtr->size - 1) {
                nodePtr = nodePtr->ptr[i + 1];
                break;
            }
        }
    }
    int j = 0;
    while (nodePtr->key[j] <= y)
    {
        if (nodePtr->key[j] >= x)
            cout << nodePtr->studentPtr[j]->jD << " " << nodePtr->studentPtr[j]->Name << " " << nodePtr->studentPtr[j]->DoB << " " << nodePtr->studentPtr[j]->gender << " " << nodePtr->studentPtr[j]->address << endl;
        j++;
        if (j == nodePtr->size){
            nodePtr = nodePtr->ptr[nodePtr->size];
            j = 0;
        }
    }
}

template <class T>
// Search operation
void BPLusTree<T>::displayParticular(T x) {
    if (root == NULL) {
        cout << "Tree is empty\n";
    }
    else {
        Node<T>* nodePtr = root;
     // If the node is not a leaf
        while (nodePtr->isLeaf == false) {

            for (int i = 0; i < nodePtr->size; i++) {
                // If the key is less than the current key
                if (x < nodePtr->key[i]) {
                    nodePtr = nodePtr->ptr[i];
                    break;
                }
                // If it's the last key of the node
                if (i == nodePtr->size - 1) {
                    nodePtr = nodePtr->ptr[i + 1];
                    break;
                }
            }
        }
        // If the node is a leaf 
        for (int i = 0; i < nodePtr->size; i++) {
            // If the key is found
            if (nodePtr->key[i] == x) {
                cout << nodePtr->studentPtr[i]->ID << " " << nodePtr->studentPtr[i]->Name << " " << nodePtr->studentPtr[i]->DoB << " " << nodePtr->studentPtr[i]->gender << " " << nodePtr->studentPtr[i]->address << endl;
                return;
            }
        }
        cout << "Not found\n";
    }
}

template <class T>
// Search operation
void BPLusTree<T>::displayParticularString(string x) {
    if (root == NULL) {
        cout << "Tree is empty\n";
    }
    else {
        Node<T>* nodePtr = root;
     // If the node is not a leaf
        while (nodePtr->isLeaf == false) {

            for (int i = 0; i < nodePtr->size; i++) {
                // If the key is less than the current key
                if (x.compare(nodePtr->key[i]) < 0) {
                    nodePtr = nodePtr->ptr[i];
                    break;
                }
                // If it's the last key of the node
                if (i == nodePtr->size - 1) {
                    nodePtr = nodePtr->ptr[i + 1];
                    break;
                }
            }
        }
        // If the node is a leaf 
        for (int i = 0; i < nodePtr->size; i++) {
            // If the key is found
            if (x.compare(nodePtr->key[i]) == 0) {
                cout << nodePtr->studentPtr[i]->ID << " " << nodePtr->studentPtr[i]->Name << " " << nodePtr->studentPtr[i]->DoB << " " << nodePtr->studentPtr[i]->gender << " " << nodePtr->studentPtr[i]->address << endl;
                return;
            }
        }
        cout << "Not found\n";
    }
}
template <class T>
void BPLusTree<T>::displayThroughleafs(Node<T>* nodePtr) {
    //display the leafs
    while (nodePtr->isLeaf == false) {
        nodePtr = nodePtr->ptr[0];
    }
    while (nodePtr != NULL) {
        for (int i = 0; i < nodePtr->size; i++) {
            cout << nodePtr->studentPtr[i]->Name << "\n";
        }
        nodePtr = nodePtr->ptr[nodePtr->size];
    }
}
template <class T>
void PointToLinkedList(BPLusTree<T>& tree, StudentList& list) {
    list.sortListByID();
    Node<T>* cursor = tree.getRoot();
    while (cursor->isLeaf == false) {
        cursor = cursor->ptr[0];
    }
    Student* nodePtr = list.getHead();
    int i = 0;
    while (nodePtr != NULL) {
        cursor->studentPtr[i] = nodePtr;
        nodePtr = nodePtr->Next;
        i++;
        if (i == cursor->size) {
            cursor = cursor->ptr[cursor->size];
            //why?
            i = 0;
        }
    }
}
template <class T>
void PointToLinkedListString(BPLusTree<T>& tree, StudentList& list) {
    list.sortListByName();
    Node<T>* cursor = tree.getRoot();
    while (cursor->isLeaf == false) {
        cursor = cursor->ptr[0];
    }
    Student* nodePtr = list.getHead();
    int i = 0;
    while (nodePtr != NULL) {
        cursor->studentPtr[i] = nodePtr;
        nodePtr = nodePtr->Next;
        i++;
        if (i == cursor->size) {
            cursor = cursor->ptr[cursor->size];
            i = 0;
        }
    }
}
template <class T>
void BPLusTree<T>::deleteTree(Node<T>* nodePtr) {
    if (nodePtr != NULL) {
        if (nodePtr->isLeaf == true) {
            delete[] nodePtr->key;
            delete[] nodePtr->ptr;
            delete[] nodePtr->studentPtr;
        }
        if (nodePtr->isLeaf != true) {
            for (int i = 0; i < nodePtr->size + 1; i++) {
                deleteTree(nodePtr->ptr[i]);
            }
        }
        delete nodePtr;
    }
}
template<class T>
BPLusTree<T>::~BPLusTree()
{
    //delete tree
    deleteTree(root);
}