// remake of Challenge 2: Adding List Based Integers
// Maria Cresap
//#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <string>
//#include <stdexcept>
using namespace std;

template <typename T>
struct Node { //struct node
    T data;
    Node<T> *next;
    Node(T &, Node<T> *);
};

//list declaration
template <typename T>
class List {
    /*protected:
        struct Node { //struct node
            T data;
            Node<T> *next;
            Node(T &, Node<T> *);
        };
        Node *head;*/
    public:
        List();
        ~List();
        //size_t size() const;
        //int& at(const size_t i);
        void push_front(T);
        void print();
        Node<T> *head;
};

//node constructor
template <typename T>
Node<T>::Node(T &d, Node<T> *n){
    data = d;
    next = n;
}

//list implementation
template <typename T>
List<T>::List(){
    head = nullptr;
}

template <typename T>
List<T>::~List(){
    Node<T> *temp = head;
    while (head!=nullptr){
        head = temp->next;
        delete temp;
        temp = head;
    }
}
/*
template <typename int>
size_t List<int>::size() const {
    size_t size=0;
    for (Node* curr=head; curr!=nullptr; curr=curr->next){
        size++;
    }
    return size;
}
*/

//new node created with data value and places at end of list
//push front
template <typename T>
void List<T>::push_front(T data) {
   /* if (head == nullptr){ //if list is empty
        head = new Node{data, nullptr};
        return;
    }*/
    /*Node *curr=head;
    Node *tail=head;
    while (curr) {
        tail=curr;
        curr=curr->next;
    }
    //tail points to last node
    tail->next=new Node{data, nullptr};*/
    Node<T> *temp = new Node<T>(data, head);
    head = temp;
}
//print which outputs contents of list in correct direction
template <typename T>
void List<T>::print(){
    Node<T> *temp = head;
    while (temp != nullptr){
        cout << temp->data;
        temp = temp->next;
    }
}

template <typename T>
void add(List<T> &num1, List<T> &num2, List<T> &sum){
    T v1, v2, sumvals;
    T carry = 0;

    Node<T> *p1 = num1.head;
    Node<T> *p2 = num2.head;

    while (p1 != nullptr || p2!= nullptr || carry>0){
        if (p1 == nullptr) //if value at end of list
            v1 = 0;
        else 
            v1=p1->data; //if not at end of 1st list
        if (p2 == nullptr) //if value at end of list
            v2 = 0;
        else
            v2 = p2->data; //if not at end of 2nd list
        sumvals = v1+v2+carry; //add 2 values and carry over from previous addition

        if (sumvals >= 10){
            sumvals = sumvals % 10; //remainder
            carry = 1;
        }
        else
            carry = 0;

        sum.push_front(sumvals);

        if (p1 != nullptr)
            p1 = p1->next; //move pointer to next if not at end/null
        if (p2 != nullptr)
            p2 = p2->next;
    }
}

//Main Execution
int main(int argc, char *argv[]){
    string n1;
    string n2; //n1 and n2 for taking in inputs
    int temp=0;
    int temp2=0;
    while (cin >> n1 >> n2){
        List<int> num1, num2, sum;
        for (unsigned int i=0; i < n1.length(); i++){
            temp = (int) n1[i] - '0';
            num1.push_front(temp);
        }
        for (unsigned int i=0; i < n2.length(); i++){
            temp2 = (int) n2[i] - '0';
            num2.push_front(temp2);
        }
        add(num1, num2, sum);
        sum.print();
        cout << endl;
    }

    return 0;
}
