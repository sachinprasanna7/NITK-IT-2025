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
    
    Node(int data){
        this->data = data;
        this->next = NULL;
    }
};

class Queue {
    private:
    Node *front;
    Node *rear;
    
    public:
    
    Queue(){
        front = rear = NULL; 
    }
    
    void enQueue(int x){
 
        Node* newNode = new Node(x);
 
        if (rear == NULL){
            front = rear = newNode;
            return;
        }
        
        rear->next = newNode;
        rear = newNode;
    }
 
    void deQueue(){
        
        if (front == NULL){
            cout<<"Underflow"<<endl;
            return;
        }
        int ans = front -> data;
    
        Node* oldNode = front;
        front = front->next;
 
        if (front == NULL)
            rear = NULL;
        
        oldNode -> next = NULL;
        delete (oldNode);
        
    }
    
    int size(){
        

        if(front == NULL){
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
        
        if(front == NULL && rear == NULL)
            return true;
        return false;
    }
    
    void display(){
        
        if(front == NULL){
            cout<<"Queue is Empty"<<endl;;
            return;
        }
        Node* temp = front;
        
        while(temp != rear){
            cout<< temp -> data <<"   ";
            temp = temp -> next;
        }
        
        cout << rear -> data << endl;
        
        return;
    }
    
};


int main() {
    
    cout<<"*****QUEUE OPERATIONS*****"<<endl<<endl;
    
    cout<<"Enter the first 10 elements of the Queue :"<<endl;
    
    
    Queue q;
    int data,num;
    
    for(int i = 0; i<10; i++){
        cout<<"Enter element "<<i+1<<": ";
        cin>>data;
        q.enQueue(data);
    }
    
    cout<<endl<<endl;
    
    cout<<"Enter the numbers for the following operations:\n1 - enQueue\n2 - deQueue\n3 - Size of Dequeue\n4 - Check if Queue is empty\n5 - Display Queue\n6 - Exit";
    cout<<endl;
    cout<<"Enter Number: ";
    cin>>num;
    if(num == 6){
        cout<<"*****THANK YOU*****";
    };
    
    while(num !=6){
        int inp;
        if(num>6 || num<1){
            cout<<"INVALID NUMBER, RE ENTER!"<<endl;
        }
        else if(num == 1){
            cout<<"Enter value to be Enqueued: ";
            cin>>inp;
            q.enQueue(inp);
        }
        else if(num == 2){
            if(q.isEmpty()){
                q.deQueue();
            }
            else{
                cout<<"Queue has been deQueued"<<endl;
                q.deQueue();
            }
        }
        else if(num == 3){
            cout<<"The size of the Queue is : "<<q.size()<<endl;;
        }
        else if(num == 4){
            if(q.isEmpty())
                cout<<"Queue is EMPTY"<<endl;
            else
                cout<<"Queue is NOT EMPTY"<<endl;
        }
        else if(num == 5){
            cout<<"The Queue is :"<<endl;
            q.display();
        }
        cout<<"Enter Number: ";
        cin>>num;
    }
    
    cout<<endl<<"*****THANK YOU*****";
    
    
    
    

    return 0;
}
