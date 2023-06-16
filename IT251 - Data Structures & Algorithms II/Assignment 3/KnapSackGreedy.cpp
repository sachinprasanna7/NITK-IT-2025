#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool sortByFirst(const pair<int, int>& a, const pair<int, int>& b) {
    if (a.first == b.first) {
        return a.second < b.second; //sort in ascending order by second element if first elements are equal
    }
    return a.first > b.first; //sort in descending order by first element
}

bool sortBySecond(const pair<int, int>& a, const pair<int, int>& b){
    if (a.second != b.second) {
        return a.second < b.second;   //sort in ascending order by second element
    } else {
        return a.first > b.first; //sort in descending order by first element
    }
}

bool cmp(const pair<pair<int, int>, float>& a, const pair<pair<int, int>, float>& b) {
    return a.second > b.second; //sort in descending order
}


float maxProfit(vector <pair <int, int>> &profitandWeight, int weight, int n){

    sort(profitandWeight.begin(), profitandWeight.end(), sortByFirst);

    float answer = 0;

    int i = 0;

    while (weight > 0 && i < n){
        if(profitandWeight[i].second > weight){
            answer += profitandWeight[i].first * (float(weight)/profitandWeight[i].second);
            weight = 0;
        }
        else{
            answer += profitandWeight[i].first;
            weight -= profitandWeight[i].second;
        }
        i++;
    }

    return answer;
}


float minWeight(vector <pair <int, int>> &profitandWeight, int weight, int n){

    sort(profitandWeight.begin(), profitandWeight.end(), sortBySecond);

    float answer = 0;

    int i = 0;

    while (weight > 0 && i < n){
        if(profitandWeight[i].second > weight){
            answer += profitandWeight[i].first * (float(weight)/profitandWeight[i].second);
            weight = 0;
        }
        else{
            answer += profitandWeight[i].first;
            weight -= profitandWeight[i].second;
        }
        i++;
    }

    return answer;
}

float maxProfitWeight(vector <pair <pair <int,int>, float>> &profitWeightRatio, int weight, int n){
    
    sort(profitWeightRatio.begin(), profitWeightRatio.end(), cmp);

    float answer = 0;

    int i = 0;

    while (weight > 0 && i < n){
        if(profitWeightRatio[i].first.second > weight){
            answer += profitWeightRatio[i].first.first * (float(weight)/profitWeightRatio[i].second);
            weight = 0;
        }
        else{
            answer += profitWeightRatio[i].first.first;
            weight -= profitWeightRatio[i].first.second;
        }
        i++;
    }
    return answer;
}

int main(){

    int n,w;
    cout<<"Enter number of Objects: ";
    cin>>n;

    cout<<"Enter weight (Capacity) of Knapsack: ";
    cin>>w;

    vector <pair <int, int>> profitandWeight;
    vector <pair <pair <int,int>, float>> profitWeightRatio;

    //1 is profit, 2 is  weight

    cout<<"Enter Profit and Weight of Each object:\n ";

    for(int i = 0 ; i < n ; i++){
        int weightofObject, profitofObject;
        cin>>profitofObject>>weightofObject;
        profitandWeight.push_back(make_pair(profitofObject, weightofObject));
        profitWeightRatio.push_back(make_pair(make_pair(profitofObject, weightofObject), float(profitofObject)/weightofObject));

    }

    sort(profitWeightRatio.begin(), profitWeightRatio.end(), cmp);

    cout<<"\n***KNAPSACK PROBLEM BY GREEDY ALGORITHMS BY SUPPORTING FRACTIONAL SUPPORT***\n\n";

    cout<<"1.Selecting items based on which item yields the highest profit initially -> "<<maxProfit(profitandWeight, w, profitandWeight.size())<<endl;
    cout<<"2.Selecting items based on which item yields the lowest weight initially -> "<<minWeight(profitandWeight, w, profitandWeight.size())<<endl;
    cout<<"3.Selecting items based on which item yields the highest profit/weight ratio initially -> "<<maxProfitWeight(profitWeightRatio, w, profitWeightRatio.size())<<endl<<endl;

    return 0;
}