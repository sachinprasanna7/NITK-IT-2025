#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

const int SIZE = 101;

class HashNode {
    public:
        int key;
        HashNode *next;

    HashNode(int key){
        this->key = key;
        this->next = nullptr;
    }
};

class HashTableChaining {
    private:
        HashNode *table[SIZE];

    public:
        
        int hashFunction(int key){
            return (11*key) % SIZE;
        }

        HashTableChaining(){
            for (int i = 0; i < SIZE; i++){
                table[i] = nullptr;
            }
        }

        void Insert_Into_Hash_Table(int key){
            int index = hashFunction(key);
            HashNode *Node = new HashNode(key);
            Node -> next = table[index];
            table[index] = Node;
        }

        void Print_Hash_Table(){
            for(int i = 0 ; i < SIZE ; i++){
                cout<<i<<": ";
                HashNode *Node = table[i];
                    while(Node != nullptr){
                        cout<<Node -> key<<" -> ";
                        Node = Node -> next;
                }
                cout<<"NULL";
                cout<<endl;
            }
        }

        float Find_Average_Chain_Length(){
            
            return 500/float(101);

            /**Because there are 500 keys to be inserted and 101 slots in the Table, the average Chain Length
               will simply be the division of these 2 numbers and will be a constant.
               So, we do not have to do any computations here.

               Note - If a slot does not hold any key after the hashing process, then I have assumed Chain Length
               as 0.
            **/
        }        
};


int main(){
  
    srand(time(nullptr));

    HashTableChaining map;

    cout<<"\nThe Random Numbers Generated are :\n\n";

    for (int i = 0; i < 500; i++){
        int num = rand() % 1001;
        cout<<num<<", ";
        map.Insert_Into_Hash_Table(num);
    }

    cout<<"\n\nTHE RESULTANT HASH TABLE AFTER INSERTING THE RANDOM KEYS USING CHAINING TECHNIQUE:\n\n";
    cout<<"INDEX : CHAIN WITH KEYS\n\n";

    map.Print_Hash_Table();

    cout<<endl<<endl;

    cout<<"Average Chain Length is : "<<map.Find_Average_Chain_Length();

     return 0;
}