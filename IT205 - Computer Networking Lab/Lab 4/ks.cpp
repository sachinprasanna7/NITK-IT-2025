
#include <iostream>
#include <string>
#include <vector>

using namespace std;


//BYTE STUFFING CODE  

string byteStuffingEncoding(string code){
    
    vector <char> encode;
    encode.push_back('0');
    encode.push_back('2');
    encode.push_back(' ');
    encode.push_back('1');
    encode.push_back('6');
    encode.push_back(' ');
    for(int i = 0 ; i<code.size() ; i++){
        encode.push_back(code[i]);
        if(encode[encode.size() - 2] == '6' && encode[encode.size() - 3] == '1'){
            encode.push_back('1');
            encode.push_back('6');
            encode.push_back(' ');
        }
        if((i == code.size() - 1) && encode[encode.size() - 1] == '6' && encode[encode.size() - 2] == '1'){
            encode.push_back(' ');
            encode.push_back('1');
            encode.push_back('6');
        }
    }
    encode.push_back(' ');
    encode.push_back('1');
    encode.push_back('6');
    encode.push_back(' ');
    encode.push_back('0');
    encode.push_back('1');
    string final(encode.begin(), encode.end());
    return final;
}

string byteStuffingDecoding(string code){
    
    vector <char> decode;
    int i = 6;
    while (i < code.size() - 6){
        decode.push_back(code[i]);
        if(decode[decode.size() - 1] == '6' && decode[decode.size() - 2] == '1'){
            i = i + 4;
        }
        else
            i++;
    }
    string final(decode.begin(), decode.end());
    return final;
}

int overheadBytes(string code, string ans){

    int ct1= 0;
    int ct2 = 0;
    for(int i = 0; i < code.size(); i++){
        if(code[i] == ' ')
            ct1++;
    }

    for(int i = 0; i < ans.size(); i++){
        if(ans[i] == ' ')
            ct2++;
    }

    return (ct2 - ct1 - 4);
}


//BIT STUFFING CODE 

string sequence = "01111110";

string hexToBinary(string hex){
    string binary = "";
    for(int i=0;i<2;i++){
    if(hex[i] == '\0' || hex[i] == ' '){
        cout<<"Numbers inputted should be 1 byte"<<endl;
        return "";
    }

    switch(hex[i])
        {
            case '0':
                binary.append("0000");
                break;
            case '1':
                binary.append("0001");
                break;
            case '2':
                binary.append("0010");
                break;
            case '3':
                binary.append("0011");
                break;
            case '4':
                binary.append("0100");
                break;
            case '5':
                binary.append("0101");
                break;
            case '6':
                binary.append("0110");
                break;
            case '7':
                binary.append("0111");
                break;
            case '8':
                binary.append("1000");
                break;
            case '9':
                binary.append("1001");
                break;
            case 'A':
                binary.append("1010");
                break;
            case 'B':
                binary.append("1011");
                break;
            case 'C':
                binary.append("1100");
                break;
            case 'D':
                binary.append("1101");
                break;
            case 'E':
                binary.append("1110");
                break;
            case 'F':
                binary.append("1111");
                break;
            default:
                cout<<"Please enter only Hexadecimal characters!!";
        }
    }
    return binary;
}

string encodePacket(string packetData){
    int count=0;
    for(int i=0;i<packetData.length();i++){
        if(packetData[i] == '1'){
            count++;
            if(count == 5){
                packetData.insert(i+1,"0");
            }
        }
        else{
            count=0;
        }
    }
    return packetData;
}

vector<string> encodePackets(vector<string> binaryData){
    for(int i=0;i<binaryData.size();i++){
        binaryData[i] = encodePacket(binaryData[i]);
    }
    return binaryData;
}

string generateFrame(vector<string> bitStuffedBinaryData){
    string bitStuffedBinaryDataString = "";
    for(auto i: bitStuffedBinaryData){
        bitStuffedBinaryDataString.append(i);
        bitStuffedBinaryDataString.append(" ");

    }
    return sequence + "  " + bitStuffedBinaryDataString + " " + sequence;
}


int overheadBitsStuffing(vector<string> data){
    
    int count = 0;
    for(int i = 0; i < data.size() ; i++){
        if(data[i].size() == 9)
            count++;
    }

    return count;
}
string decodePacket(string packetData){
    int count=0;
    string packetDataNew = "";
    for(int i=0;i<packetData.length();i++){
        if(packetData[i] == '1'){
            count++;
            packetDataNew = packetDataNew+ packetData[i];
            if(count == 5){
                i++;
            }
        }else if(packetData[i] == '0'){
            count = 0;
            packetDataNew = packetDataNew+ packetData[i];
        }
    }
    return packetDataNew;
}

string decodePackets(string dataPacket){
    dataPacket = dataPacket + " ";
    string binaryData;
    string decodedData;
    for(int i=0;i<dataPacket.length();i++){
        if(dataPacket[i] == ' '){
            decodedData.append(decodePacket(binaryData));
            decodedData.append(" ");   
            binaryData.clear();
        }else{
            binaryData = binaryData + dataPacket[i];
        }
    }
    return decodedData;
}

string stripHeaderTrailer(string frame){
    return frame.substr(10,frame.length()-8-2-8-2);
}

void printVector(vector<string> vector){
    for(int i=0;i<vector.size();i++){
        cout<<vector[i]<<" ";
    }
    cout<<endl;
}



int main(){
    
    //Byte Stuffing
    
    string code;
    cout<<"*****BYTE STUFFING AND BIT STUFFING*****\n\n";
    cout<<"Enter your CODE in hexadecimal, one by one which will be inputted into the frame: ";
    getline(cin, code);
    
    cout<<"\n*****PERFORMING BYTE STUFFING*****\n\n";

    cout<<"INPUTTED CODE (Data to be sent): ";
    cout<<code;
    
    string ans = byteStuffingEncoding(code);
    
    cout<<"\n\nENCODED CODE (Frames which are sent by the sender to the receiver): "<<ans;

    cout<<"\n\nNumber of overhead Bytes according to Byte Stuffing is : "<<overheadBytes(code,ans);
    cout<<"\nNumber of overhead Bits according to Byte Stuffing is: "<<overheadBytes(code,ans)*8;
    
    string decode = byteStuffingDecoding(ans);
    
    cout<<"\n\nDECODED CODE (Data recieved by the reciever): "<<decode;

    cout<<"\n\nClearly Inputted Code and Decoded Code are the SAME!\n\n\n";
    
    //Bit Stuffing  
    
    cout<<"*****PERFORMING BIT STUFFING*****"<<endl;
    vector<string> binaryData;
    int i = 0;
    while(i<code.length()){
        string binary = hexToBinary(code.substr(i,2));
        if(binary == ""){
            return -1;
        }
        binaryData.push_back(binary);
        i+=3;
    }
    cout<<"INPUTTED CODE: ";
    printVector(binaryData);
    vector<string> bitStuffedBinaryData = encodePackets(binaryData);
    // cout<<"Bit Stuffed Input: ";
    // printVector(bitStuffedBinaryData);
    string frame = generateFrame(bitStuffedBinaryData);
    cout<<"\n\nENCODED CODE: "<<frame;

    cout<<"\n\nNumber of overhead Bits according to Bit Stuffing is: "<<overheadBitsStuffing(bitStuffedBinaryData);
    
    //decoding
    string dataPacket = stripHeaderTrailer(frame);
    string decodedData = decodePackets(dataPacket);
    cout<<"\n\nDECODED CODE : "<<decodedData<<endl;

    cout<<endl;
    
    return 0;
}
