#pragma once
#include"./include.h"
//forward declaration
template <class T>
class BPLusTree;
template <class T = int>
class Node {
    bool isLeaf; //indicating if it's a leaf 
    T* key;
    int size;   //size is the number of keys in a node, it changes with the addition of more keys
    Node** ptr; //double pointer to create 
    Student** studentPtr;
    friend class BPLusTree<T>;
    template <class Y>
    friend void PointToLinkedList(BPLusTree<Y>&, StudentList&);
public:
    Node();
};
template <class T>
Node<T>::Node() {
    key = new T[maxNumberOfKeys];
    ptr = new Node * [maxNumberOfKeys + 1];
    studentPtr = new Student * [maxNumberOfKeys];
}
// BP tree
template <class T = int>
class BPLusTree {
    string fileName;
    Node<T>* root;
    Node<T>* findingTheParent(Node<T>*, Node<T>*); //this is used to find the parent of the node
    //writing the tree in a file
    void writeTree(Node<T>*, ofstream&);
    void insertInInternalNode(int, Node<T>*, Node<T>*); //this function is used to insert a key in the internal node
    void insertInInternalNodeString(string, Node<T>*, Node<T>*); //this function is used to insert a key in the internal node
    //why different functions for int and string? because we can't compare two strings with > or < operators
public:
    BPLusTree(string);
    string getFileName();
    Student* displayParticular(T); //searching a key in the tree
    void displayParticularString(string);
    void displayThroughleafs(Node<T>*); //displaying the keys in the tree
    void insert(int); //inserting a key in the tree
    void insertString(string); //inserting a key in the tree
    Node<T>* getRoot(); //returning the root of the tree
    void display(Node<T>*); //displaying the tree
    void writeToIndexesFile();
    void countTheNumberOfkeysinLeaves();
    void displayQuery(string, string);
    void displayBetweenRange(int x1, int x2, char gen);
    void displayBetweenRange(int x1, int x2, string gen);
    void displayBetweenRange(Node<T>*, int x, int y); //displaying the tree through the leaf nodes
    void stringBasedRangeSearch(string x, string y); //displaying the tree through the leaf nodes
    void deleteTree(Node<T>*); //deleting the tree
    ~BPLusTree();
};
template <class T>
BPLusTree<T>::BPLusTree(string fileName) :fileName(fileName) {
    root = NULL;
}
template <class T>
string BPLusTree<T>::getFileName() {
    return fileName;
}

template <class T>
// Insert Operation
void BPLusTree<T>::insert(int x /*it's the incoming value*/) {
    if (root == NULL) {
        root = new Node<T>;
        root->size = 1; //because only one key is added to the root
        root->isLeaf = true; //initially the root is the leaf
        root->key[0] = x; //the first key of the root now has the value 'x'
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
                    /// @brief //if the key is less than the current key, then we go to the left child
                    nodePtr = nodePtr->ptr[i];
                    break;
                }
                // If it's the last key of the node
                if (i == nodePtr->size - 1) {
                    //* if the control reaches the last key of the node.
                    nodePtr = nodePtr->ptr[i + 1];
                    break;
                }
            }
        }
        //if the leaf node is not full
        if (nodePtr->size < maxNumberOfKeys) {
            int i = 0;
            // Find the position of the new key
            while (x > nodePtr->key[i] && i < nodePtr->size)
                i++;
            // Shifting the keys to the right
            for (int j = nodePtr->size; j > i; j--) {
                nodePtr->key[j] = nodePtr->key[j - 1];
            }
            nodePtr->size++;
            nodePtr->key[i] = x;

            nodePtr->ptr[nodePtr->size] = nodePtr->ptr[nodePtr->size - 1];
             //the last pointer of the leaf node is the same as the second last pointer

            nodePtr->ptr[nodePtr->size - 1] = NULL;
        }
        //if the leaf node is full
        else {
            //create a virtual key array
            T virtualNode[maxNumberOfKeys + 2];
            //create a new leaf node
            Node<T>* newLeaf = new Node<T>;
            //copy the keys of the current leaf node to the virtual node
            for (int i = 0; i < maxNumberOfKeys; i++) {
                virtualNode[i] = nodePtr->key[i];
            }
            int i = 0, j;
            //find the position of the new key
            while (x > virtualNode[i] && i < maxNumberOfKeys)
                i++;
            //shift the keys to the right
            for (int j = maxNumberOfKeys + 1; j > i; j--) {
                virtualNode[j] = virtualNode[j - 1];
            }
            //insert the new key
            virtualNode[i] = x; //the new key is inserted at the position 'i'
            nodePtr->size = (maxNumberOfKeys + 1) / 2;

            nodePtr->ptr[nodePtr->size] = newLeaf;  //
            nodePtr->ptr[maxNumberOfKeys] = NULL;

            newLeaf->isLeaf = true;

            newLeaf->size = maxNumberOfKeys + 1 - (maxNumberOfKeys + 1) / 2;
            newLeaf->ptr[newLeaf->size] = nodePtr->ptr[maxNumberOfKeys];
            //copy the keys to the new leaf node
            for (i = 0; i < nodePtr->size; i++) {
                //copy the keys to the current leaf node
                nodePtr->key[i] = virtualNode[i];
            }
            //copy the keys to the current leaf node
            for (i = 0, j = nodePtr->size; i < newLeaf->size; i++, j++) {
                //copy the keys to the new leaf node
                newLeaf->key[i] = virtualNode[j];
            }
            //if the current leaf node is the root
            if (nodePtr == root) {
                Node<T>* tempRoot = new Node<T>;
                tempRoot->ptr[1] = newLeaf;
                tempRoot->ptr[0] = nodePtr;
                tempRoot->size = 1;
                tempRoot->key[0] = newLeaf->key[0];
                tempRoot->isLeaf = false;
                root = tempRoot;
            }
            //if the current leaf node is not the root
            else {
                //insert the new key in the internal node
                insertInInternalNode(newLeaf->key[0], parent, newLeaf);
            }
        }
    }
}
template <class T>
void BPLusTree<T>::countTheNumberOfkeysinLeaves() {
    Node<T>* nodePtr = root;
    while (nodePtr->isLeaf == false) {
        nodePtr = nodePtr->ptr[0];
    }
    int count = 0;
    while (nodePtr != NULL) {
        for (int i = 0; i < nodePtr->size; i++) {
            cout << nodePtr->key[i] << " ";
            count++;
        }
        nodePtr = nodePtr->ptr[nodePtr->size];
    }
    cout << "The count is " << count << endl;
}
// Insert Operation
template <class T>
void BPLusTree<T>::insertInInternalNode(int x, Node<T>* nodePtr, Node<T>* children) {
    // If the node is not full
    if (nodePtr->size < maxNumberOfKeys) {
        int i = 0;
        // Find the position of the new key
        while (x > nodePtr->key[i] && i < nodePtr->size)
            i++;
        // Shifting the keys to the right
        for (int j = nodePtr->size; j > i; j--) {
            // Shifting the keys to the right
            nodePtr->key[j] = nodePtr->key[j - 1];
        }
        for (int j = nodePtr->size + 1; j > i + 1; j--) {
            // Shifting the pointers to the right
            nodePtr->ptr[j] = nodePtr->ptr[j - 1];
        }
        nodePtr->ptr[i + 1] = children;
        nodePtr->size++;
        nodePtr->key[i] = x;
    }
    // If the node is full 
    else {
        Node<T>* newInternalNode = new Node<T>;
        T tempKey[maxNumberOfKeys + 2];
        Node<T>* tempPtr[maxNumberOfKeys + 3];
        // Copying the keys to the virtual arrays
        for (int i = 0; i < maxNumberOfKeys; i++) {
            // Copying the keys to the virtual arrays
            tempKey[i] = nodePtr->key[i];
        }
        for (int i = 0; i < maxNumberOfKeys + 1; i++) {
            // Copying the pointers to the virtual array
            tempPtr[i] = nodePtr->ptr[i];
        }
        int i = 0;
        int j;
        // Find the position of the new key
        while (x > tempKey[i] && i < maxNumberOfKeys)
            i++;
        // Shifting the keys to the right
        for (int j = maxNumberOfKeys + 1; j > i; j--) {
            tempKey[j] = tempKey[j - 1];
        }
        tempKey[i] = x;
        // Shifting the pointers to the right
        for (int j = maxNumberOfKeys + 2; j > i + 1; j--) {
            tempPtr[j] = tempPtr[j - 1];
        }
        newInternalNode->isLeaf = false;

        tempPtr[i + 1] = children;

        newInternalNode->size = maxNumberOfKeys - (maxNumberOfKeys + 1) / 2;
        nodePtr->size = (maxNumberOfKeys + 1) / 2;
        // Copying the first half of the keys to the original node
        for (i = 0, j = nodePtr->size + 1; i < newInternalNode->size; i++, j++) {
            newInternalNode->key[i] = tempKey[j];
        }
        // Copying the first half of the pointers to the original node
        for (i = 0, j = nodePtr->size + 1; i < newInternalNode->size + 1; i++, j++) {
            newInternalNode->ptr[i] = tempPtr[j];
        }
        // If the node is the root
        if (nodePtr == root) {
            Node<T>* tempRoot = new Node<T>;

            tempRoot->ptr[0] = nodePtr;

            tempRoot->key[0] = nodePtr->key[nodePtr->size];
            tempRoot->isLeaf = false;
            // Copying the second half of the keys to the new node
            tempRoot->ptr[1] = newInternalNode;
            tempRoot->size = 1;
            // Updating the root
            root = tempRoot;
        }
        else {
            insertInInternalNode(nodePtr->key[nodePtr->size], findingTheParent(root, nodePtr), newInternalNode);
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
        if (nodePtr->size < maxNumberOfKeys) {
            int i = 0;
            // Find the position of the new key
            while (x.compare(nodePtr->key[i]) > 0 && i < nodePtr->size)
                i++;
            // Shifting the keys to the right
            for (int j = nodePtr->size; j > i; j--) {
                nodePtr->key[j] = nodePtr->key[j - 1];
            }
            nodePtr->size++;
            nodePtr->key[i] = x;

            nodePtr->ptr[nodePtr->size] = nodePtr->ptr[nodePtr->size - 1];
             //the last pointer of the leaf node is the same as the second last pointer

            nodePtr->ptr[nodePtr->size - 1] = NULL;
        }
        //if the leaf node is full
        else {
            Node<T>* newLeaf = new Node<T>; //create a new leaf node
            T virtualNode[maxNumberOfKeys + 2];
            //copy the keys of the current leaf node to the virtual node
            for (int i = 0; i < maxNumberOfKeys; i++) {
                virtualNode[i] = nodePtr->key[i];
            }
            int i = 0, j;
            //find the position of the new key
            while (x.compare(virtualNode[i]) > 0 && i < maxNumberOfKeys)
                i++;
            //shift the keys to the right
            for (int j = maxNumberOfKeys + 1; j > i; j--) {
                virtualNode[j] = virtualNode[j - 1];
            }
            //insert the new key
           //insert the new key
            virtualNode[i] = x; //the new key is inserted at the position 'i'
            nodePtr->size = (maxNumberOfKeys + 1) / 2;
            nodePtr->ptr[nodePtr->size] = newLeaf;  //

            nodePtr->ptr[maxNumberOfKeys] = NULL;

            newLeaf->isLeaf = true;

            newLeaf->size = maxNumberOfKeys + 1 - (maxNumberOfKeys + 1) / 2;
            newLeaf->ptr[newLeaf->size] = nodePtr->ptr[maxNumberOfKeys];
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
                Node<T>* tempRoot = new Node<T>;
                tempRoot->ptr[1] = newLeaf;
                tempRoot->ptr[0] = nodePtr;
                tempRoot->size = 1;
                tempRoot->key[0] = newLeaf->key[0];
                tempRoot->isLeaf = false;
                root = tempRoot;
            }
            //if the current leaf node is not the root
            else {
                //insert the new key in the internal node
                insertInInternalNodeString(newLeaf->key[0], parent, newLeaf);
            }
        }
    }
}

template <class T>
void BPLusTree<T>::insertInInternalNodeString(string x, Node<T>* nodePtr, Node<T>* children) {
    // If the node is not full
    if (nodePtr->size < maxNumberOfKeys) {
        int i = 0;
        // Find the position of the new key
        while (x.compare(nodePtr->key[i]) > 0 && i < nodePtr->size)
            i++;
        // Shifting the keys to the right
        for (int j = nodePtr->size; j > i; j--) {
            // Shifting the keys to the right
            nodePtr->key[j] = nodePtr->key[j - 1];
        }
        for (int j = nodePtr->size + 1; j > i + 1; j--) {
            // Shifting the pointers to the right
            nodePtr->ptr[j] = nodePtr->ptr[j - 1];
        }
        nodePtr->ptr[i + 1] = children;
        nodePtr->size++;
        nodePtr->key[i] = x;
    }
    // If the node is full 
    else {
        Node<T>* newInternalNode = new Node<T>;
        T tempKey[maxNumberOfKeys + 2];
        Node<T>* tempPtr[maxNumberOfKeys + 3];
        // Copying the keys  to the virtual arrays
        for (int i = 0; i < maxNumberOfKeys; i++) {
            // Copying the keys to the virtual arrays
            tempKey[i] = nodePtr->key[i];
        }
        // Copying the pointers to the virtual array
        for (int i = 0; i < maxNumberOfKeys + 1; i++) {
            tempPtr[i] = nodePtr->ptr[i];
        }
        int i = 0;
        int j;
       // Find the position of the new key
        while (x.compare(tempKey[i]) > 0 && i < maxNumberOfKeys)
            i++;
        // Shifting the keys to the right
        for (int j = maxNumberOfKeys + 1; j > i; j--) {
            tempKey[j] = tempKey[j - 1];
        }
        tempKey[i] = x;
        // Shifting the pointers to the right
        for (int j = maxNumberOfKeys + 2; j > i + 1; j--) {
            tempPtr[j] = tempPtr[j - 1];
        }
        newInternalNode->isLeaf = false;

        tempPtr[i + 1] = children;

        newInternalNode->size = maxNumberOfKeys - (maxNumberOfKeys + 1) / 2;
        nodePtr->size = (maxNumberOfKeys + 1) / 2;
        // Copying the first half of the keys to the original node
        for (i = 0, j = nodePtr->size + 1; i < newInternalNode->size; i++, j++) {
            newInternalNode->key[i] = tempKey[j];
        }
        // Copying the first half of the pointers to the original node
        for (i = 0, j = nodePtr->size + 1; i < newInternalNode->size + 1; i++, j++) {
            newInternalNode->ptr[i] = tempPtr[j];
        }
        // If the node is the root
        if (nodePtr == root) {
            Node<T>* tempRoot = new Node<T>;

            tempRoot->ptr[0] = nodePtr;

            tempRoot->key[0] = nodePtr->key[nodePtr->size];
            tempRoot->isLeaf = false;
            // Copying the second half of the keys to the new node
            tempRoot->ptr[1] = newInternalNode;
            tempRoot->size = 1;
            // Updating the root
            root = tempRoot;
        }
        else {
            insertInInternalNodeString(nodePtr->key[nodePtr->size], findingTheParent(root, nodePtr), newInternalNode);
        }
    }
}
template <class T>
Node<T>* BPLusTree<T>::getRoot() {
    return root;
}
template <class T>
void BPLusTree<T>::writeTree(Node<T>* nodePtr, ofstream& file) {
    static bool first = true;
    if (nodePtr != NULL) {
        for (int i = 0; i < nodePtr->size; i++) {
            file << nodePtr->key[i] << " ";
        }
        file << "\n";
        if (nodePtr->isLeaf != true) {
            for (int i = 0; i < nodePtr->size + 1; i++) {
                writeTree(nodePtr->ptr[i], file);
            }
        }
    }
}
template <class T>
void BPLusTree<T>::writeToIndexesFile() {
    ofstream file;
    file.open("./Indexes/" + fileName, ios::out);
    writeTree(root, file);
    file.close();
}
template <class T>
void BPLusTree<T>::displayBetweenRange(int x, int y, char gen) {
    Node<T>* nodePtr = root;
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
        if (nodePtr->key[j] >= x && nodePtr->studentPtr[j]->gender == gen)
            cout << nodePtr->studentPtr[j]->ID << " " << nodePtr->studentPtr[j]->Name << " " << nodePtr->studentPtr[j]->DoB << " " << nodePtr->studentPtr[j]->gender << " " << nodePtr->studentPtr[j]->address << endl;
        j++;
        if (j == nodePtr->size) {
            nodePtr = nodePtr->ptr[nodePtr->size];
            j = 0;
        }
    }
}
template <class T>
void BPLusTree<T>::displayBetweenRange(int x, int y, string DoB) {
    Node<T>* nodePtr = root;
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
        if (nodePtr->key[j] >= x && nodePtr->studentPtr[j]->DoB == DoB)
            cout << nodePtr->studentPtr[j]->ID << " " << nodePtr->studentPtr[j]->Name << " " << nodePtr->studentPtr[j]->DoB << " " << nodePtr->studentPtr[j]->gender << " " << nodePtr->studentPtr[j]->address << endl;
        j++;
        if (j == nodePtr->size) {
            nodePtr = nodePtr->ptr[nodePtr->size];
            j = 0;
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
            cout << nodePtr->studentPtr[j]->ID << " " << nodePtr->studentPtr[j]->Name << " " << nodePtr->studentPtr[j]->DoB << " " << nodePtr->studentPtr[j]->gender << " " << nodePtr->studentPtr[j]->address << endl;
        j++;
        if (j == nodePtr->size) {
            nodePtr = nodePtr->ptr[nodePtr->size];
            j = 0;
        }
    }
}
template <class T>
void BPLusTree<T>::displayQuery(string DoB, string qual) {
    if (root == NULL) {
        cout << "Tree is empty\n";
    }
    else {
        Node<T>* nodePtr = root;
        // If the node is not a leaf
        while (nodePtr->isLeaf == false) {

            for (int i = 0; i < nodePtr->size; i++) {
                // If the key is less than the current key
                if (DoB.compare(nodePtr->key[i]) < 0) {
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
            if (DoB.compare(nodePtr->key[i]) == 0) {
                if (qual.compare(nodePtr->studentPtr[i]->qualification) == 0)
                    cout << nodePtr->studentPtr[i]->ID << " " << nodePtr->studentPtr[i]->Name << " " << nodePtr->studentPtr[i]->DoB << " " << nodePtr->studentPtr[i]->address << " " << nodePtr->studentPtr[i]->reference << endl;
                int j = i;
                while (DoB.compare(nodePtr->key[j]) == 0) {
                    j++;
                    if (DoB.compare(nodePtr->key[j]) == 0) {
                        if (qual.compare(nodePtr->studentPtr[j]->qualification) == 0)
                            cout << nodePtr->studentPtr[j]->ID << " " << nodePtr->studentPtr[j]->Name << " " << nodePtr->studentPtr[j]->DoB << " " << nodePtr->studentPtr[j]->address << " " << nodePtr->studentPtr[j]->reference << endl;
                    }
                    if (j == nodePtr->size) {
                        nodePtr = nodePtr->ptr[nodePtr->size];
                        j = 0;
                        if (qual.compare(nodePtr->studentPtr[j]->qualification) == 0)
                            cout << nodePtr->studentPtr[j]->ID << " " << nodePtr->studentPtr[j]->Name << " " << nodePtr->studentPtr[j]->DoB << " " << nodePtr->studentPtr[j]->address << " " << nodePtr->studentPtr[j]->reference << endl;
                    }
                }
                return;
            }
        }
        cout << "Not found\n";
    }

}
template <class T>
void BPLusTree<T>::stringBasedRangeSearch(string x, string y) {
    Node<T>* nodePtr = root;
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
    int j = 0;
    while (nodePtr->key[j].compare(y) <= 0)
    {
        if (nodePtr->key[j].compare(x) >= 0)
            cout << nodePtr->studentPtr[j]->ID << " " << nodePtr->studentPtr[j]->Name << " " << nodePtr->studentPtr[j]->DoB << " " << nodePtr->studentPtr[j]->gender << " " << nodePtr->studentPtr[j]->address << endl;
        j++;
        if (j == nodePtr->size) {
            nodePtr = nodePtr->ptr[nodePtr->size];
            j = 0;
        }
    }
}

template <class T>
// Search operation
Student* BPLusTree<T>::displayParticular(T x) {
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
                return nodePtr->studentPtr[i];
            }
        }
        cout << "Not found\n";
        return nullptr;
    }
    return nullptr;
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
                cout << nodePtr->studentPtr[i]->ID << " " << nodePtr->studentPtr[i]->Name << " " << nodePtr->studentPtr[i]->DoB << " " << nodePtr->studentPtr[i]->address << " " << nodePtr->studentPtr[i]->reference << endl;
                int j = i;
                while (x.compare(nodePtr->key[j]) == 0) {
                    j++;
                    if (x.compare(nodePtr->key[j]) == 0)
                        cout << nodePtr->studentPtr[j]->ID << " " << nodePtr->studentPtr[j]->Name << " " << nodePtr->studentPtr[j]->DoB << " " << nodePtr->studentPtr[j]->address << ' ' << nodePtr->studentPtr[j]->reference << endl;
                    if (j == nodePtr->size) {
                        nodePtr = nodePtr->ptr[nodePtr->size];
                        j = 0;
                        cout << nodePtr->studentPtr[j]->ID << " " << nodePtr->studentPtr[j]->Name << " " << nodePtr->studentPtr[j]->DoB << " " << nodePtr->studentPtr[j]->address << ' ' << nodePtr->studentPtr[j]->reference << endl;
                    }
                }
                return;
            }
        }
        cout << "Not found\n";
    }
}
template <class T>
void PointToLinkedList(BPLusTree<T>& tree, StudentList& list) {
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
            if (cursor->ptr[cursor->size] == NULL) {
                cout << "The tree is not big enough\n";
            }
            cursor = cursor->ptr[cursor->size];

            i = 0;
        }
    }
}
//Finding the parent
template <class T>
Node<T>* BPLusTree<T>::findingTheParent(Node<T>* nodePtr, Node<T>* children) {
    Node<T>* parent;
    //if the cursor is null, then return null
    if (nodePtr->isLeaf /*The leafs*/ || /*The parent of the leafs*/(nodePtr->ptr[0])->isLeaf) {
        return NULL;
    }
    //if the child is the first pointer of the cursor, then return the cursor
    for (int i = 0; i < nodePtr->size + 1; i++) {
        //finding the parent of the children
        if (nodePtr->ptr[i] == children) {
            //The children has been found
            parent = nodePtr; /*//!The parent value equals to nodePtr*/
            return parent;
        }
        //if the child is not the first pointer of the cursor, then recursively call the function
        else {
            //recursively call the function
            parent = findingTheParent(nodePtr->ptr[i], children);
            //if the parent is not null, then return the parent
            if (parent != NULL) {
                //The parent has been found
                return parent;
            }
        }
    }
    return parent;
}

template <class T>
void BPLusTree<T>::deleteTree(Node<T>* nodePtr) {
    //delete the BplusTree along with studentPtr, key and Ptr
    if (nodePtr == NULL)
        return;
    if (nodePtr != NULL && nodePtr->isLeaf == true) {
        //The leaves doesn't have any ptr pointing to nodes that why only single array is been deleted
        delete[] nodePtr->key;
        delete[] nodePtr->ptr;
        delete[] nodePtr->studentPtr;
        delete nodePtr;
    }
    else if (nodePtr != NULL && nodePtr->isLeaf == false) {
        for (int i = 0; i < nodePtr->size + 1; i++) {
            deleteTree(nodePtr->ptr[i]);
        }
        delete[] nodePtr->key;
        delete[] nodePtr->ptr;
        delete[] nodePtr->studentPtr;
        delete nodePtr;
    }
}
template<class T>
BPLusTree<T>::~BPLusTree()
{
    //delete tree
    deleteTree(root);
}

