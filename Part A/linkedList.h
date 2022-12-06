#pragma once
#include"include.h"
class StudentList;
void readData(StudentList&); //prototype of global function
//student Node 
class Student {
private:
public:
    int ID;
    string Name, DoB, regDate, address, qualification;
    char gender;
    Student* Next;
    Student* Prev;
    string reference;
    Student();
    Student(int, string, string, string, string, string, char, string);
};
Student::Student() {

}
Student::Student(int id, string name, string dob, string reg, string add, string qual, char gen, string ref) {
    ID = id;
    Name = name;
    DoB = dob;
    regDate = reg;
    address = add;
    qualification = qual;
    Next = NULL;
    gender = gen;
    reference = ref;
}

//linked list class

class StudentList {
private:
    int maxID;
    Student* Head;
public:
    Student* tail;
    StudentList();
    Student* getHead();
    void setHead(Student*);
    string getLastReference();
    int getMaxID();
    void addStudent(int, string, string, string, string, string, char, string);
    void displayList();
    void sortListByName(); //sort list with respect to their name
    void sortListByID(); //sort list with respect to their ID
    void sortListByDoB(); //sort list with respect to their DoB
    void sortListByRegDate(); //sort list with respect to their regDate
    void copyList(StudentList&); //copy list to another list
    void deleteStudent(int);
    ~StudentList();
};

StudentList::StudentList() {
    maxID = 0;
    Head = NULL;
    readData(*this);
}
Student* StudentList::getHead() {
    return Head;
}
void StudentList::setHead(Student* node) {
    Head = node;
}
int StudentList::getMaxID() {
    return maxID;
}
string StudentList::getLastReference() {
    for (int i = 0;i < tail->reference.length();i++)
    {
        if (tail->reference[i] == 'R')
        {
            string temp = tail->reference.substr(i + 1, tail->reference.length());
            int num = stoi(temp);
            num++;
            temp = to_string(num);
            temp = tail->reference.substr(0, i + 1) + temp;
            return temp;
        }
    }
    return "";
}

void StudentList::addStudent(int id, string name, string dob, string reg, string add, string qual, char gen, string ref) {
    Student* newStudent = new Student(id, name, dob, reg, add, qual, gen, ref);
    if (Head == NULL) {
        Head = newStudent;
        tail = newStudent;
        Head->Next = NULL;
        Head->Prev = NULL;
    }
    else {
        tail->Next = newStudent;
        newStudent->Prev = tail;
        tail = newStudent;
        tail->Next = NULL;
    }
    if (id > maxID)
        maxID = id;
}

void StudentList::displayList() {
    Student* temp = Head;
    while (temp != NULL) {
        cout << temp->ID << " " << temp->Name << " " << temp->DoB << " " << temp->regDate << " " << temp->address << " " << temp->qualification << endl;
        temp = temp->Next;
    }
}
void StudentList::sortListByName() {
    // sortList on the basis of name
    Student* temp = Head;
    while (temp != NULL) {
        Student* temp2 = temp->Next;
        while (temp2 != NULL) {
            if (temp->Name.compare(temp2->Name) > 0) {
                swap(temp->ID, temp2->ID);
                swap(temp->Name, temp2->Name);
                swap(temp->DoB, temp2->DoB);
                swap(temp->regDate, temp2->regDate);
                swap(temp->address, temp2->address);
                swap(temp->gender, temp2->gender);
                swap(temp->qualification, temp2->qualification);
                swap(temp->reference, temp2->reference);
            }
            temp2 = temp2->Next;
        }
        if (temp->Next == NULL)
            tail = temp;
        temp = temp->Next;
    }
}
void StudentList::sortListByID() {
    // sortList on the basis of name
    Student* temp = Head;
    while (temp != NULL) {
        Student* temp2 = temp->Next;
        while (temp2 != NULL) {
            if (temp->ID > temp2->ID) {
                swap(temp->ID, temp2->ID);
                swap(temp->Name, temp2->Name);
                swap(temp->DoB, temp2->DoB);
                swap(temp->regDate, temp2->regDate);
                swap(temp->address, temp2->address);
                swap(temp->gender, temp2->gender);
                swap(temp->qualification, temp2->qualification);
                swap(temp->reference, temp2->reference);
            }
            temp2 = temp2->Next;
        }
        if (temp->Next == NULL)
            tail = temp;
        temp = temp->Next;
    }
}
void StudentList::sortListByDoB() {
    // sortList on the basis of name
    Student* temp = Head;
    while (temp != NULL) {
        Student* temp2 = temp->Next;
        while (temp2 != NULL) {
            if (temp->DoB.compare(temp2->DoB) > 0) {
                swap(temp->ID, temp2->ID);
                swap(temp->Name, temp2->Name);
                swap(temp->DoB, temp2->DoB);
                swap(temp->regDate, temp2->regDate);
                swap(temp->address, temp2->address);
                swap(temp->gender, temp2->gender);
                swap(temp->qualification, temp2->qualification);
                swap(temp->reference, temp2->reference);
            }
            temp2 = temp2->Next;
        }
        if (temp->Next == NULL)
            tail = temp;
        temp = temp->Next;
    }
}
void StudentList::sortListByRegDate() {
    // sortList on the basis of name
    Student* temp = Head;
    while (temp != NULL) {
        Student* temp2 = temp->Next;
        while (temp2 != NULL) {
            if (temp->regDate.compare(temp2->regDate) > 0) {
                swap(temp->ID, temp2->ID);
                swap(temp->Name, temp2->Name);
                swap(temp->DoB, temp2->DoB);
                swap(temp->regDate, temp2->regDate);
                swap(temp->address, temp2->address);
                swap(temp->gender, temp2->gender);
                swap(temp->qualification, temp2->qualification);
                swap(temp->reference, temp2->reference);
            }
            temp2 = temp2->Next;
        }
        if (temp->Next == NULL)
            tail = temp;
        temp = temp->Next;
    }
}
void StudentList::copyList(StudentList& list) {
    Student* temp = Head;
    while (temp != NULL) {
        list.addStudent(temp->ID, temp->Name, temp->DoB, temp->regDate, temp->address, temp->qualification, temp->gender, temp->reference);
        temp = temp->Next;
    }
}
void StudentList::deleteStudent(int id) {
    Student* temp = Head;
    Student* prev = Head;
    while (temp != NULL) {
        if (temp->ID == id) {
            if (temp == Head) {
                Head = Head->Next;
                delete temp;
                break;
            }
            else {
                prev->Next = temp->Next;
                delete temp;
                break;
            }
        }
        else {
            prev = temp;
            temp = temp->Next;
        }
    }
}



StudentList::~StudentList() {
    Student* temp = Head;
    while (temp != NULL) {
        Student* temp2 = temp;
        temp = temp->Next;
        delete temp2;
    }
}


//global functions

void splitData(string& data, int& id, string& name, string& DoB, char& gender, string& regDate, string& address, string& qualification) {
    string strOfId;  // because we are reading string from file, later on it'll be store in id variable using stoi
    int entryNo = 1;
  //   for(int i =0; i< data.length(); i++){ if(data[i] == '\t'){cout <<  '*';}else{cout << data[i];}}cout << endl;
    for (int i = 0; i < data.length(); i++) {
        if (data[i] == '\t') {
            entryNo++;
        }
        else {
            switch (entryNo)
            {
            case 1: { strOfId += data[i]; }break;
            case 2: { name += data[i];    }break;
            case 3: { DoB += data[i];     }break;
            case 4: { gender = data[i];    }break;
            case 5: { regDate += data[i];    }break;
            case 6: { address += data[i];    }break;
            case 7: { qualification += data[i];    }break;
            }
        }
    }
    if (strOfId != "")
        id = stoi(strOfId);
}


void readData(StudentList& list) {
    fstream iFile;
    int fileNo = 1;
    while (fileNo <= 12) {                      //until 13, but file no. 6 has some problem in format, throwing error
        string fileName = "Fall2022DSDataFile00";
        string reference;
        if (fileNo > 9) { fileName = "Fall2022DSDataFile0"; }
        fileName += to_string(fileNo);
        iFile.open("./DatasetFall2022DSproject/" + fileName + ".txt");
        if (iFile.is_open()) {
            while (!(iFile.eof())) {
                string stdData = "";
                string stdName, dob, regDate, address, qualification;
                int id;
                char gender;
                getline(iFile, stdData);
                splitData(stdData, id, stdName, dob, gender, regDate, address, qualification);
                reference = 'F' + to_string(fileNo) + 'L' + to_string(id + 1);
                list.addStudent(id, stdName, dob, regDate, address, qualification, gender, reference);
            }

        }
        else {
            cout << "Could not open file\n";
        }
        iFile.close();
        fileNo++;
    }

}