#include <iostream>
#include <fstream>
#include <string>
using namespace std;

//student Node 
class Student{
    private:
    public:
       int ID;
       string Name, DoB, regDate, address, qualification;
       char gender;
       Student * Next;
       Student(int, string, string, string, string, string, char);
};

Student::Student(int id, string name, string dob, string reg, string add, string qual, char gen = 'A'){
    ID = id;
    Name = name;
    DoB = dob;
    regDate = reg;
    address = add;
    qualification;
    Next = NULL;
}

//linked list class

class StudentList{
    private:
       Student * Head;
    public:
       StudentList();
       void addStudent(int, string, string, string, string, string, char);
       void displayList();
       void deleteStudent(int);
       ~StudentList();
};

StudentList::StudentList(){
    Head = NULL;
}

void StudentList::addStudent(int id, string name, string dob, string reg, string add, string qual, char gen){
    Student * newStudent = new Student(id, name, dob, reg, add, qual, gen);
    if(Head == NULL){
        Head = newStudent;
    }
    else{
        Student * temp = Head;
        while(temp->Next != NULL){
            temp = temp->Next;
        }
        temp->Next = newStudent;
    }
}

void StudentList::displayList(){
    Student * temp = Head;
    while(temp != NULL){
        cout << temp->ID << " " << temp->Name << " " << temp->DoB << " " << temp->regDate << " " << temp->address << " " << temp->qualification << endl;
        temp = temp->Next;
    }
}

void StudentList::deleteStudent(int id){
    Student * temp = Head;
    Student * prev = Head;
    while(temp != NULL){
        if(temp->ID == id){
            if(temp == Head){
                Head = Head->Next;
                delete temp;
                break;
            }
            else{
                prev->Next = temp->Next;
                delete temp;
                break;
            }
        }
        else{
            prev = temp;
            temp = temp->Next;
        }
    }
}



StudentList::~StudentList(){
    Student * temp = Head;
    while(temp != NULL){
        Student * temp2 = temp;
        temp = temp->Next;
        delete temp2;
    }
}


//global functions

void splitData(string &data, int &id, string &name, string &DoB, char &gender, string &regDate, string &address, string &qualification){
        string strOfId;  // because we are reading string from file, later on it'll be store in id variable using stoi
          int entryNo =1;
    for(int i=0; i< data.length(); i++){
                  if(data[i] == '\t'){ 
                           entryNo++;
                    }else{
                          switch (entryNo)
                          {
                            case 1:{ strOfId += data[i]; }break;
                            case 2:{ name += data[i];    }break;
                            case 3:{ DoB += data[i];     }break;
                            case 4:{ gender = data[i];    }break;
                            case 5:{ regDate += data[i];    }break;
                            case 6:{ address += data[i];    }break;
                            case 7:{ qualification += data[i];    }break;
                          }
                    }
    }
    id = stoi(strOfId);
    
}


void readData(StudentList &list){
    fstream iFile;
      int fileNo = 1;
        while(fileNo != 6){                      //until 13, but file no. 6 has some problem in format, throwing error
      string fileName = "Fall2022DSDataFile00";
            fileName += to_string(fileNo);cout << fileName << ' '<< fileNo << endl; 
           iFile.open("./DatasetFall2022DSproject/" + fileName +".txt");
                  if(iFile.is_open()){
                       while(!(iFile.eof())){
                             string stdData = "";
                             string stdName, dob, regDate, address, qualification;
                             int id;
                             char gender;
                             getline(iFile, stdData);
                             splitData(stdData, id, stdName, dob, gender, regDate, address, qualification);
                             list.addStudent(id, stdName, dob, regDate, address, qualification, gender);
                       }
            
                  }else{
                    cout << "Could not open file\n";
                  }
            iFile.close();
            fileNo++;
        }
}