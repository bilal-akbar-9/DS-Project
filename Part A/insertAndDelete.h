#pragma once
#include"include.h"
#include"linkedList.h"
#include"BPlusTree.h"
void writeToStudentFiles(StudentList& list)
{
    int fileIdCoordinates[2][13] =
    {
        {0,101,200,351,501,600,1001,2001,2501,4001,5001,6101},
        {100,199,350,500,599,1000,2000,2500,4000,5000,6100,10000}
    };
    Student* nodePtr = list.getHead();
    for (int j = 1, i = 0; i <= 12; i++, j++) {
        fstream file;
        if (j < 9)
            file.open("./DatasetFall2022DSproject/Fall2022DSDataFile00" + to_string(j) + ".txt", ios::out);
        else if (j > 9 && j <= 12)
            file.open("./DatasetFall2022DSproject/Fall2022DSDataFile0" + to_string(j) + ".txt", ios::out);
        while (nodePtr != nullptr && (nodePtr->ID >= fileIdCoordinates[0][i] && nodePtr->ID <= fileIdCoordinates[1][i])) {
            file << nodePtr->ID << "\t" << nodePtr->Name << "\t" << nodePtr->DoB << "\t" << nodePtr->gender << "\t" << nodePtr->regDate << "\t" << nodePtr->address << "\t" << nodePtr->qualification << endl;
            nodePtr = nodePtr->Next;
        }
        file.close();
    }
}
void insert(StudentList& list)
{
    int ID = list.getMaxID() + 1;
    string name, dob, reg, add, qual;
    char gen;
    cout << "The ID is :" << ID << endl;
    cout << "Enter Name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter Date of Birth: ";
    getline(cin, dob);
    cout << "Enter Registration Date: ";
    getline(cin, reg);
    cout << "Enter Address: ";
    getline(cin, add);
    cout << "Enter Qualification: ";
    getline(cin, qual);
    cout << "Enter gender: ";
    cin >> gen;
     //append to the list
    list.addStudent(ID, name, dob, reg, add, qual, gen);
    fstream dataFile;
    //add data to the file
    dataFile.open("./DatasetFall2022DSproject/Fall2022DSDataFile012.txt", ios::app);
    dataFile << endl << ID << "\t" << name << "\t" << dob << "\t" << gen << "\t" << reg << "\t" << add << "\t" << qual;
        dataFile.close();
}
void Delete(StudentList& list) {
    cout << "Enter ID of the student you want to delete: ";
    int id;
    cin >> id;
    BPLusTree<int> tree("ID.txt");
    Student* nodePtr = list.getHead();
    list.sortListByID(); // sort the list with respect to their ID
    while (nodePtr != NULL) {
        tree.insert(nodePtr->ID);
        nodePtr = nodePtr->Next;
    }
    PointToLinkedList(tree, list);
    nodePtr = tree.displayParticular(id);
    if (nodePtr == NULL) {
        cout << "Student not found" << endl;
    }
    else {
        if (nodePtr != list.getHead()) {
            if (nodePtr->Next != NULL) {
                nodePtr->Prev->Next = nodePtr->Next;
                nodePtr->Next->Prev = nodePtr->Prev;
            }
            else {
                nodePtr->Prev->Next = NULL;
            }
        }
        else {
            list.setHead(nodePtr->Next);
            nodePtr->Next->Prev = NULL;
        }
        writeToStudentFiles(list);
        cout << "Student deleted" << endl;
    }
}
void insertAndDelete(StudentList& list) {
    int choose = 0;
    while (choose != 3)
    {
        cout << "1.Insert\n2.Delete\n3.Exit\n";
        cin >> choose;
        if (choose == 1) {
            insert(list);
        }
        else if (choose == 2) {
            Delete(list);
        }
        else if (choose == 3) {
            break;
        }
        else {
            cout << "Invalid input\n";
        }
    }

}