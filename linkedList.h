#include <iostream>
using namespace std;

//student Node 
class Student{
    private:
       int ID;
       string Name, DoB, regDate, address, qualification;
       char gender;
       Student * Next;
    public:
       Student(int, string, string, string, string, string, char);
};

Student()::Student(int id, string name, string dob, string reg, string add, string qual, char gen){
    ID = id;
    Name = name;
    DoB = dob;
    regDate = reg;
    address = add;
    qualification;
    Next = NULL;
}

