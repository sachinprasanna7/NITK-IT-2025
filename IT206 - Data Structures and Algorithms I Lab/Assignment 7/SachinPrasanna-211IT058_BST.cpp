#include <iostream>
#include <queue>
#include <cstdlib>
#include <ctime>

using namespace std;


class Node{
    public:
    int data;
    Node* right;
    Node* left;

    Node(int data){
        this -> data = data;
        this -> right = nullptr;
        this -> left = nullptr;
    }
};

Node* Insert(Node* root, int data){

    if(root == nullptr){
        root = new Node(data);
        return root;
    }

    if(root -> data < data) 
        root -> right = Insert(root->right, data);

    else if(root -> data > data) 
        root -> left = Insert(root->left, data);
    
    return root;
    
}

int minimumValue(Node* root){
    
    Node* temp = root;
    while(temp -> left != nullptr)
        temp = temp -> left;
    return temp -> data;
}

Node* Delete(Node* &root, int data){

    if(root == nullptr)
        return root;
    
    if(root -> data == data){
        if(root -> right == nullptr && root -> left == nullptr){
            delete root;
            return nullptr;
        }

        if(root -> left != nullptr && root -> right == nullptr){
            Node* temp = root -> left;
            delete root;
            return temp;
        }

        if(root -> left == nullptr && root -> right != nullptr){
            Node* temp = root -> right;
            delete root;
            return temp;
        }

        if(root -> left != nullptr && root -> right != nullptr){
            int mini = minimumValue(root -> right);
            root -> data = mini;
            root -> right = Delete(root -> right, mini);
            return root;
        }
        return nullptr;
    }

    else if(root -> data > data){
        root -> left = Delete(root -> left, data);
        return root;
    }

    else{
        root -> right = Delete(root -> right, data);
        return root;
    }

}

void inOrder(Node* root){
    if(root == nullptr)
        return;
    
    inOrder(root->left);
    cout<< root -> data<<" ";
    inOrder(root -> right);
}

bool isFound(int arr[], int key, int n){

    for(int i = 0; i < n ; i++){
        if(arr[i] == key)
            return true;
    }
    return false;
}

void swap(Node* root, Node* temp){
    temp = root->left;
    root->left = root->right;
    root->right = temp;
}

void mirror(Node* root){
    if (root == nullptr)
        return;
    else{
        Node* temp;
        mirror(root->left);
        mirror(root->right);
        swap(root, temp);
    }
}

int main(){
  
    /**Inserting 25 Distinct Random Keys into the Binary Tree**/

    srand(time(nullptr));
    int Keys[25];
    Keys[0] = rand()%100;
    Node* root = nullptr;
    for(int i = 1; i < 25; i++){
        int key;
        do{
            key = rand()%100;
        } while(isFound(Keys, key, i));
        Keys[i] = key;   
    }
    
    cout<<"\n\nRandom Keys to be Inserted:\n";
    for(int i = 0; i < 25 ; i++){
        cout<<Keys[i]<<" ";
        
    }

    for(int i = 0; i < 25 ; i++){
        root = Insert(root, Keys[i]);
    }

    cout<<"\n\n***BINARY SEARCH TREE OF SIZE 25 CREATED***";

    cout<<"\n\nInorder Traversal of the Created Binary Search Tree:\n";
    inOrder(root);

    cout<<"\n\nDeleting 12th Element ("<<Keys[11]<<") from the Binary Search Tree and Inorder Traversal after Deletion:\n";
    root = Delete(root, Keys[11]);
    inOrder(root);

    cout<<"\n\nDeleting 13th Element ("<<Keys[12]<<") from the Binary Search Tree and Inorder Traversal after Deletion:\n";
    root = Delete(root, Keys[12]);
    inOrder(root);

    cout<<"\n\nDeleting 14th Element ("<<Keys[13]<<") from the Binary Search Tree and Inorder Traversal after Deletion:\n";
    root = Delete(root, Keys[13]);
    inOrder(root);

    cout<<"\n\n***MIRRORING THE BINARY TREE***";

    mirror(root);

    cout<<"\n\nInorder Traversal of the Mirrored Binary Search Tree:\n";
    inOrder(root);
    cout<<"\n\nEND OF PROGRAM";

    return 0;
}