#include "./include.h"
//implement undirect graph using linked list

class Node {
    private:
        int data;
        Node * next;
    public:
        Node();
        Node(int);
        void setData(int);
        int getData();
        void setNext(Node *);
        Node * getNext();
};

Node::Node() {
    data = 0;
    next = NULL;
}

Node::Node(int d) {
    data = d;
    next = NULL;
}

void Node::setData(int d) {
    data = d;
}

int Node::getData() {
    return data;
}

void Node::setNext(Node * n) {
    next = n;
}

Node * Node::getNext() {
    return next;
}

class Graph{
    private:
       Node ** adjList;
         int size;
    public:
        Graph(int);
        void addEdge(int, int);
        void displayGraph();
        ~Graph();

};

Graph::Graph(int s) {
    size = s;
    adjList = new Node*[size];
    for (int i = 0; i < size; i++) {
        adjList[i] = NULL;
    }
}

void Graph::addEdge(int src, int dest) {
    Node * newNode = new Node(dest);
    newNode->setNext(adjList[src]);
    adjList[src - 2101] = newNode;
    newNode = new Node(src);
    newNode->setNext(adjList[dest]);
    adjList[dest - 2101] = newNode;
}

void Graph::displayGraph() {
    for (int i = 0; i < size; i++) {
        cout << i << " --> ";
        Node * temp = adjList[i];
        while (temp != NULL) {
            cout << temp->getData() << " ";
            temp = temp->getNext();
        }
        cout << endl;
    }
}

Graph::~Graph() {
    for (int i = 0; i < size; i++) {
        Node * temp = adjList[i];
        while (temp != NULL) {
            Node * temp2 = temp;
            temp = temp->getNext();
            delete temp2;
        }
    }
    delete [] adjList;
}

void splitString(string s, Graph &g){
         string source = "";
         string destination =  "";
           int valueNo = 1;      
    for(int i=0; i<s.length(); i++){
         if(s[i] == ':'){
             valueNo++; i++;
         }
          else if(s[i] == ' '){
                cout << source << " " << destination << endl;
                destination = "";
         }else{
            switch (valueNo)
               {
                   case 1:{
                       source += s[i];
                   }break;
                   case 2:{
                       destination += s[i];
                   }break;
               }
         }
    }
}

void readData(Graph &g){
    fstream iFile;
    iFile.open("./DatasetFall2022DSproject/friends.txt");
      if(iFile.is_open()){
              string data;
          while(!iFile.eof()){
              getline(iFile, data);
              splitString(data, g);
              cout << endl;
          }
      }else{
            cout << "File not found" << endl;
      }
}

int main() {
    Graph g(500);
    // g.addEdge(0, 1);
    // g.addEdge(0, 4);
    // g.addEdge(1, 2);
    // g.addEdge(1, 3);
    // g.addEdge(1, 4);
    // g.addEdge(2, 3);
    // g.addEdge(3, 4);
    // g.displayGraph();
    readData(g);
    return 0;
}
