/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <iostream>

using namespace std;

class Node{
    public:
    int data;
    Node* next;
    Node* prev;
    
    Node(int data){
        this -> data = data;
        this -> next = nullptr;
        this -> prev = nullptr;
    }
};

class Deque{
    public:
    Node *front;
    Node *rear;
    
    
    
    Deque(){
        this -> front = nullptr;
        this -> rear = nullptr;
    }
    
    void enQueueFront(int data){
        
        
        Node* newNode = new Node(data);
        
        if(front == nullptr){
            front = rear = newNode;
            return;
        }
        
        front -> prev = newNode;
        newNode -> next = front;
        front = newNode;
    }
    
    void enQueueRear(int data){
        
        Node* newNode = new Node(data);
        
        if(front == nullptr){
            front = rear = newNode;
            return;
        }
        
        rear -> next = newNode;
        newNode -> prev = rear;
        rear = newNode;
    }
    
    void deQueueFront(){
        
        if(front == nullptr){
            cout<<"Underflow";
            return;
        }
        
        if(!front->next)
        {
            front = nullptr;
            rear = nullptr;
        }
        
        else {
            front = front->next;
            front->prev = nullptr;
        }
    }
    
    void deQueueRear(){
        
        if(rear == nullptr){
            cout<<"Underflow";
            return;
        }
        
        if(!rear->prev)
        {
            front = nullptr;
            rear = nullptr;
        }
        
        else {
            rear = rear->prev;
            rear->next = nullptr;
        }
    }
    
    int size(){
        
        if(front == nullptr){
            return 0;
        }
        
        Node* temp = front;
        
        int count = 1;
        while(temp != rear){
            temp = temp -> next;
            count++;
        }
        
        return count;
        
    }
    
    bool isEmpty(){
        if(front == nullptr)
            return true;
            
        return false;
    }
    
    void display(){
        
        if(front == nullptr){
            cout<<"Dequeue is Empty"<<endl;
            return;
        }
        Node* temp = front;
        
        while(temp != rear){
            cout<< temp -> data << "   ";
            temp = temp -> next;
        }
        
        cout << rear -> data << endl;
        
        return;
    }
    
};

int main()
{
    
    cout<<"*****DEQUEUE OPERATIONS*****"<<endl<<endl;
    
    cout<<"Enter the first 10 elements of the Dequeue :"<<endl;
    
    
    Deque dq;
    int data,num;
    
    for(int i = 0; i<10; i++){
        cout<<"Enter element "<<i+1<<": ";
        cin>>data;
        dq.enQueueRear(data);
    }
    
    cout<<endl<<endl;
    
    cout<<"Enter the numbers for the following operations:\n1 - enQueueFront\n2 - enQueueRear\n3 - deQueueFront\n4 - deQueueRear\n5 - Size of Dequeue\n6 - Check if Dequeue is empty\n7 - Display Dequeue\n8 - Exit";
    cout<<endl;
    cout<<"Enter Number: ";
    cin>>num;
   
    while(num !=8){
        int inp;
        if(num>8 || num<1){
            cout<<"INVALID NUMBER, RE ENTER!"<<endl;
        }
        else if(num == 1){
            cout<<"Enter value to be Enqueued in front: ";
            cin>>inp;
            dq.enQueueFront(inp);
        }
        else if(num == 2){
            cout<<"Enter value to be Enqueued in rear: ";
            cin>>inp;
            dq.enQueueRear(inp);
        }
        else if(num == 3){
            if(dq.isEmpty()){
                dq.deQueueFront();
            }
            else{
                cout<<"Dequeue has been dequeued from the front"<<endl;
                dq.deQueueFront();
            }
        }
        else if(num == 4){
            if(dq.isEmpty()){
                dq.deQueueRear();
            }
            else{
                cout<<"Dequeue has been Dequeued from the rear"<<endl;
                dq.deQueueRear();
            }
        }
        else if(num == 5){
            cout<<"The size of the Dequeue is : "<<dq.size()<<endl;;
        }
        else if(num == 6){
            if(dq.isEmpty())
                cout<<"Dequeue is EMPTY"<<endl;
            else
                cout<<"Dequeue is NOT EMPTY"<<endl;
        }
        else if(num == 7){
            cout<<"The Dequeue is :"<<endl;
            dq.display();
        }
        cout<<"Enter Number: ";
        cin>>num;
    }
    
    cout<<endl<<"*****THANK YOU*****";
    
    
    return 0;
}
