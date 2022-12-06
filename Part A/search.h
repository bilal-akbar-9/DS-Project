#pragma once
#include"include.h"
#include"linkedList.h"
#include"BPlusTree.h"

void general_search(StudentList& list) {
    int choose = 0;
    cout << "Choose from the following:\n1.Search by name\n2.Search by ID\n3.Search by DOB\n";
    cin >> choose;
    if (choose == 1) {
        string name;
        cout << "Enter name: ";
        cin.ignore();
        getline(cin, name);
        time_t start, end;
        time(&start);
        BPLusTree<string> tree("name.txt");
        Student* nodePtr = list.getHead();
        list.sortListByName();
        while (nodePtr != nullptr) {
            tree.insertString(nodePtr->Name);
            nodePtr = nodePtr->Next;
        }
        PointToLinkedList(tree, list);
        tree.displayParticularString(name);
        time(&end);
        double time_taken = double(end - start); // calulate diffrence
        cout << "duration: " << fixed << time_taken << setprecision(10) << " s \n";
        tree.writeToIndexesFile();
    }
    else if (choose == 2) {
        int Id;
        cout << "Enter Id: ";
        cin >> Id;
        BPLusTree<int> tree("ID.txt");
        Student* nodePtr = list.getHead();
        list.sortListByID();
        while (nodePtr != nullptr) {
            tree.insert(nodePtr->ID);
            nodePtr = nodePtr->Next;
        }
        PointToLinkedList(tree, list);
        tree.displayParticular(Id);
        tree.writeToIndexesFile();
    }
    else if (choose == 3)
    {
        string DoB;
        cout << "Enter DOB: ";
        cin.ignore();
        getline(cin, DoB);
        time_t start, end;
        time(&start);
        BPLusTree<string> tree("DOB.txt");
        Student* nodePtr = list.getHead();
        list.sortListByDoB();
        while (nodePtr != nullptr) {
            tree.insertString(nodePtr->DoB);
            nodePtr = nodePtr->Next;
        }
        PointToLinkedList(tree, list);
        tree.displayParticularString(DoB);
        time(&end);
        double time_taken = double(end - start); // calulate diffrence
        cout << "duration: " << fixed << time_taken << setprecision(10) << " s \n";
        tree.writeToIndexesFile();
    }
    else {
        cout << "Invalid input\n";
    }
}
void range_Search(StudentList& list) {
    int choose = 0;
    cout << "Choose from the following:\n1.Search by name\n2.Search by ID\n3.Search by DOB\n";
    cin >> choose;
    if (choose == 1) {
        int start, end;
        cout << "Enter the start of the range: ";
        cin >> start;
        cout << "Enter the end of the range: ";
        cin >> end;
        BPLusTree<int> tree("ID.txt");
        Student* nodePtr = list.getHead();
        list.sortListByID();
        while (nodePtr != nullptr) {
            tree.insert(nodePtr->ID);
            nodePtr = nodePtr->Next;
        }
        PointToLinkedList(tree, list);
        tree.displayBetweenRange(tree.getRoot(), start, end);
    }
    else if (choose == 2) {
        string start, end;
        cout << "Enter the start of the range: ";
        cin.ignore();
        getline(cin, start);
        cout << "Enter the end of the range: ";
        getline(cin, end);
        BPLusTree<string> tree("name.txt");
        Student* nodePtr = list.getHead();
        list.sortListByName();
        while (nodePtr != nullptr) {
            tree.insertString(nodePtr->Name);
            nodePtr = nodePtr->Next;
        }
        PointToLinkedList(tree, list);
        tree.stringBasedRangeSearch(start, end);
    }
    else if (choose == 3) {
        string start, end;
        cout << "Enter the start of the range: ";
        cin.ignore();
        getline(cin, start);
        cout << "Enter the end of the range: ";
        getline(cin, end);
        BPLusTree<string> tree("DOB.txt");
        Student* nodePtr = list.getHead();
        list.sortListByDoB();
        while (nodePtr != nullptr) {
            tree.insertString(nodePtr->DoB);
            nodePtr = nodePtr->Next;
        }
        PointToLinkedList(tree, list);
        tree.stringBasedRangeSearch(start, end);
    }
    else {
        cout << "Invalid input\n";
    }
}
void query_combination_search(StudentList& list) {
    int choose = 0;
    while (choose != 4) {
        cout << "1.And\n2.Or\n3.Not\n4. Exit\n";
        cin >> choose;
        if (choose == 1)
        {
            int pick = 0;
            cout << "Choose from the given options\n1.ID and gender\n2.DOB and ID\n3.DoB and qualification\n";
            cin >> pick;
            if (pick == 1) {
                cout << "Enter the starting ID: ";
                int start, end;
                char gen;
                cin >> start;
                cout << "Enter the ending ID: ";
                cin >> end;
                int pick1 = 0;
                while (pick1 != 1 && pick1 != 2) {
                    cout << "Pick a gender\n1.Male\n2.Female\n";
                    cin >> pick1;
                }
                if (pick1 == 1)
                    gen = 'M';
                else
                    gen = 'F';
                BPLusTree<int> tree("ID.txt");
                Student* nodePtr = list.getHead();
                list.sortListByID();
                while (nodePtr != nullptr) {
                    tree.insert(nodePtr->ID);
                    nodePtr = nodePtr->Next;
                }
                PointToLinkedList(tree, list);
                tree.displayBetweenRange(start, end, gen);               
            }
            else if (pick == 2) {
                cout << "Enter the starting ID: ";
                int start, end;
                string DoB;
                cin >> start;
                cout << "Enter the ending ID: ";
                cin >> end;
                BPLusTree<int> tree("ID.txt");
                Student* nodePtr = list.getHead();
                list.sortListByID();
                while (nodePtr != nullptr) {
                    tree.insert(nodePtr->ID);
                    nodePtr = nodePtr->Next;
                }
                PointToLinkedList(tree, list);
                tree.displayBetweenRange(start, end, DoB);
            }
            else if (pick == 3) {
                string DoB,qual;
                cout << "Enter the DoB: ";
                cin.ignore();
                getline(cin, DoB);
                cout << "Enter the qualification: ";
                cin.ignore();
                getline(cin, qual);
                BPLusTree<string> tree("DOB.txt");
                Student* nodePtr = list.getHead();
                list.sortListByDoB();
                while (nodePtr != nullptr) {
                    tree.insert(nodePtr->ID);
                    nodePtr = nodePtr->Next;
                }
                PointToLinkedList(tree, list);
                tree.displayQuery(DoB,qual);
            }
        }
    }
}
void Search(StudentList& list) {
    int choose = 0;
    while (choose != 4) {
        cout << "1.General Search\n2.Query Combination Search\n3.Range search\n4. Exit\n";
        cin >> choose;
        if (choose == 1)
            general_search(list);
        else if (choose == 2) {
            query_combination_search(list);
        }
        else if (choose == 3) {
            range_Search(list);
        }
        else if (choose == 4) {
            break;
        }
        else {
            cout << "Invalid input\n";
        }

    }
}
