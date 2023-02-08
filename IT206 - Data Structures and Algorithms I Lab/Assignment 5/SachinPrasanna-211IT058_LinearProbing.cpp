#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

const int SIZE = 503;

class HashTableLinearProbing{

    private:

        int table[SIZE];
        int Collisions = 0;
    
    public:

        int hashFunction(int key){
            return (13*key) % SIZE;
        }

        HashTableLinearProbing(){
            for(int i = 0; i < SIZE ; i++) {
                table[i] = -1;    // -1 signifies that the slot in table is Unoccupied
            }
        }

        void Insert_Into_Hash_Table(int key){

            
            int LinearProbeIndex = hashFunction(key);

            while(table[LinearProbeIndex] != -1){
                Collisions++;
                LinearProbeIndex = (LinearProbeIndex + 1) % SIZE;
            }

            table[LinearProbeIndex] = key;  
        }

        int Number_Of_Collisions(){
            return Collisions;
        }

        void Print_Hash_Table(){
            for(int i = 0 ; i < SIZE ; i++){
                cout<< i <<": "<< table[i] << endl;
            }
        }




};


int main(){

    srand(time(nullptr));

    HashTableLinearProbing map;

    cout<<"\nThe Random Numbers Generated are :\n\n";

    for (int i = 0; i < 500; i++){
        int num = rand() % 1001;
        cout<<num<<", ";
        map.Insert_Into_Hash_Table(num);
    }

    cout<<"\n\nTHE RESULTANT HASH TABLE AFTER INSERTING THE RANDOM KEYS USING LINEAR PROBING:\n\n";
    cout<<"INDEX : KEY STORED\n\n";

    map.Print_Hash_Table();

    cout<<"\n\nThe Number of Collisions are: "<<map.Number_Of_Collisions();
  
    return 0;
}