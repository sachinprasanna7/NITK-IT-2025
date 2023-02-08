#include <iostream>

using namespace std;

class Node{                //This is for the initial longer linked list, for inputting values
    public:
    int data;
    Node* right;
    Node* left;
    
    Node(int data) {
        this -> data = data;
        this -> right = NULL;
        this -> left = NULL;
    }
};

void insertNode(Node* &temp, int d){
    
    Node* nodeToInsert = new Node(d);
    temp -> right = nodeToInsert;
    temp = nodeToInsert;

}

void insertNodeRight(Node* &temp2, int d){
    
    Node* nodeToInsert = new Node(d);
    temp2 -> right = nodeToInsert;
    temp2 = nodeToInsert;
}

void insertNodeLeft(Node* &temp1, int d){
    
    Node* nodeToInsert = new Node(d);
    temp1 -> left = nodeToInsert;
    temp1 = nodeToInsert;
}


void printLinkedList(Node* &head, Node* &head1){
    
    Node* upPrint = head;
    cout<<"UPPER LINKED LIST: "<<endl;
    while(upPrint != NULL){
        cout<<upPrint -> data<<endl;
            if(upPrint -> left != NULL){
                cout<<"MIDDLE NODE :"<< upPrint -> data<<endl;
                cout<<"RIGHT LINKED LIST: "<<endl;
            }
        upPrint = upPrint -> right;
    }
    
    upPrint = head1 -> left;
    
    cout<<"LEFT LINKED LIST: "<<endl;
    while(upPrint != NULL){
        cout<<upPrint -> data<<endl;
        upPrint = upPrint -> left;
    }
}

void insertAtUpperHead(Node* &head, int d){
    
    Node* newNode = new Node(d);
    newNode -> right = head;
    newNode = head;
    
}

/*****************SEARCHING FOR ELEMENT IN LINKED LIST*************/

void search(Node* head, Node* head1, int val){
    
    Node* searcher = head;
    int i = 1;
    while (searcher != head1){
        if (searcher -> data == val){
            cout<<val<<" found at "<<i<<" position in the UPPER part of Linked List"<<endl;
            return;
        }
        searcher = searcher -> right;
        i++;
    }
    
    i = 0;
    while(searcher != NULL){
        if(searcher -> data == val){
            cout<<val<<" found at "<<i<<" position in the LEFT part of Linked List"<<endl;
            return;
        }
        searcher = searcher -> left;
        i++;
        
    }
    
    searcher = head1;
    
    i = 0;
    
    while(searcher != NULL){
        if(searcher -> data == val){
            cout<<val<<" found at "<<i<<" position in the RIGHT part of Linked List"<<endl;
            return;
        }
        searcher = searcher -> right;
        i++;
    }
    
    cout<<"ELEMENT IS NOT FOUND IN LINKED LIST"<<endl;
    return;
}

/*****************INSERTING ELEMENT IN LINKED LIST*************/

void insert(Node* &head, Node* &head1, Node* &temp1, Node* &temp2, int pos, int d){
    
    Node* inserter = head;
    Node* prev = NULL;
    int count = 1;
    while(count<=pos && inserter != head -> right){
        
        if(count == pos && inserter == head){
            Node* newNode = new Node(d);
            newNode -> right = head;
            head = newNode;
            return;
        }
        else if(count == pos){
            Node* newNode = new Node(d);
            prev -> right = newNode;
            newNode -> right = inserter;
            return;
        }
        prev = inserter;
        inserter = inserter -> right;
        count++;
    }
    
    //Now we will traverse right part of linked List
    
    while(count<=pos && inserter != temp2 -> right){
        
        if(count == pos && inserter == temp2){
            
            Node* newNode = new Node(d);
            inserter -> right = newNode;
            temp2 = newNode;
            return;
        }
        
        else if(count == pos){
            Node* newNode = new Node(d);
            prev -> right = newNode;
            newNode -> right = inserter;
            return;
        }
        prev = inserter;
        inserter = inserter -> right;
        count++;
    }
    
    //Now we will traverse left part of Linked List
    
    prev = head1;
    inserter = head1 -> left;
    
    while(count <= pos && inserter != temp1 -> left){
        
        if(count == pos && inserter == temp1){
            
            Node* newNode = new Node(d);
            inserter -> left = newNode;
            temp1 = newNode;
            return;
        }
        
        else if(count == pos){
            Node* newNode = new Node(d);
            prev -> left = newNode;
            newNode -> left = inserter;
            return;
        }
        prev = inserter;
        inserter = inserter -> left;
        count++;
    }
    
    return;
    
}

/*****************DELETING ELEMENT IN LINKED LIST*************/

void Delete(Node* &head, Node* &head1, Node* &temp1, Node* &temp2, int pos){
    
    Node* inserter = head;
    Node* prev = NULL;
    int count = 1;
    while(count<=pos && inserter != head1 -> right){
        
        if(count == pos && inserter == head){                      //If node to be deleted is the topmost Upper node
            Node* deletestartnode = head;
            head = head -> right;
            delete (deletestartnode);
            return;
        }
        
        else if(count == pos && inserter != head1){
            prev -> right = inserter -> right;
            inserter -> right = NULL;
            delete(inserter);
            return;
        }
        
        else if (count == pos && inserter == head1){    //If node to be deleted is middle (ROOT) node
            prev -> right = inserter -> right;
            prev -> left = inserter -> left;
            inserter -> right = NULL;
            inserter -> left = NULL;
            head1 = prev;
            delete(inserter);
            return;
        }
        
        prev = inserter;
        inserter = inserter -> right;
        count++;
    }
    
    //Now we will go to right part of linked List
    
    while(count<=pos && inserter != temp2 -> right){
        
        if(count == pos && inserter == temp2){     //Deleting the leaf node of right Linked List
            temp2 = prev;
            prev -> right = NULL;
            delete(inserter);
            return;
        }
        
        else if(count == pos){
            prev -> right = inserter -> right;
            inserter -> right = NULL;
            delete(inserter);
            return;
        }
        prev = inserter;
        inserter = inserter -> right;
        count++;
    }
    
    //Now we will traverse left part of Linked List
    
    prev = head1;
    inserter = head1 -> left;
    
    while(count <= pos && inserter != temp1 -> left){
        
        if(count == pos && inserter == temp1){
            
            temp1 = prev;
            temp1 -> left = NULL;
            delete(inserter);
            return;
        }
        
        else if(count == pos){
            prev -> left = inserter -> left;
            inserter -> left = NULL;
            delete(inserter);
            return;
        }
        prev = inserter;
        inserter = inserter -> left;
        count++;
    }
}


int main(){
    
    Node* head = NULL;
    int split,d1,d2,elements;
    cout<<"Enter which position do you want the Linked List to split into 2 halves: ";
    cin>>split;
    
    cout<<"Enter the first element in linked list: ";
    cin>>d1;
    
    Node* node1 = new Node(d1);
    head = node1;
    
    Node* temp = head;
    
    int input_data;
    
    for(int i = 1 ; i<split ; i++){
        
        cout<<"Enter Element "<<i+1<<": ";
        cin>>input_data;
        insertNode(temp,input_data);
    }
    
    //Now ask the user to input to right or left linked list
    
    char ch;
    
    Node* head1 = temp;   //This node will point at the middle node, which is connected to other linked list
                          //head1 is our reference node which points in the middle node
                          
    Node* temp1 = head1;
    Node* temp2 = head1;
    
    cout<<"How many more elements to insert in linked list: ";
    cin>>elements;
    
    cout<<"Press L to insert to left part\n Press R to insert to right part:";
    
    while(elements){
        cin>>ch;
        if(ch == 'R'){
            cout<<"Enter value to be inserted: ";
            cin>>input_data;
            insertNodeRight(temp2, input_data);
            elements--;
        }
        else if(ch == 'L'){
            cout<<"Enter value to be inserted: ";
            cin>>input_data;
            insertNodeLeft(temp1, input_data);
            elements--;
        }
        
        else{
            cout<<"Wrong character picked, press L or R";
            continue;
        }
        
    }
    
    
    //Initial Linked list is created
    
    //Inserting into the linked list, asking the user to insert it in the UP linked list, LEFT or RIGHT 
    cout<<endl<<"The Entered Linked List is: "<<endl;
    printLinkedList(head, head1);
    cout<<endl<<endl;

    int find = 16;
    
    while(find){
        search(head,head1,find);
        find--;
    }
    
    cout<<endl<<endl;
    
    cout<<"Deleting Upper Leaf Node"<<endl;
    Delete(head,head1,temp1,temp2,1);
    cout<<endl;
    printLinkedList(head,head1);
    cout<<endl;
    cout<<"Inserting it back"<<endl;
    insert(head,head1,temp1,temp2,1,1);
    cout<<endl;
    printLinkedList(head, head1);
    cout<<endl;
    
    cout<<"Deleting Right Leaf Node"<<endl;
    Delete(head,head1,temp1,temp2,10);
    cout<<endl;
    printLinkedList(head,head1);
    cout<<endl;
    cout<<"Inserting it back"<<endl;
    insert(head,head1,temp1,temp2,9,10);
    cout<<endl;
    printLinkedList(head, head1); 
    cout<<endl;
    
    cout<<"Deleting Left Leaf Node"<<endl;
    Delete(head,head1,temp1,temp2,15);
    cout<<endl;
    printLinkedList(head,head1);
    cout<<endl;
    cout<<"Inserting it back"<<endl<<endl;
    insert(head,head1,temp1,temp2,14,15);
    cout<<endl;
    printLinkedList(head,head1);
    cout<<endl;
    
    int sample,val;
    cout<<"Enter position of element to be deleted and to be inserted again: ";
    cin>>sample;
    cout<<"Enter value of element to be inserted back in place:";
    cin>>val;
    cout<<endl<<"Deleting element in "<<sample<<" position";
    Delete(head,head1,temp1,temp2,sample);
    cout<<endl;
    printLinkedList(head,head1);
    cout<<endl;
    cout<<"Inserting it back with inputted element"<<endl<<endl;
    insert(head,head1,temp1,temp2,sample,val);
    cout<<endl;
    printLinkedList(head,head1);
    cout<<endl;
    
    cout<<"Deleting Middle Node"<<endl;
    Delete(head,head1,temp1,temp2,5);
    cout<<endl;
    printLinkedList(head,head1);
    
    cout<<endl<<endl;
    
    cout<<"****THE END****";
  
    return 0;
}