#include <iostream>
#include <cstdlib>
#include <ctime>

const int SIZE = 500;

using namespace std;


/*******MERGE SORT*******/

void merge(int *arr, int start, int end) {

    int mid = (start+end)/2;

    int len1 = mid-start+1;
    int len2 = end-mid;

    int *first = new int[len1];
    int *second = new int[len2];

    int ctr = start;
    for(int i=0; i<len1; i++) {
        first[i] = arr[ctr++];
    }

    ctr = mid+1;
    for(int i=0; i<len2; i++) {
        second[i] = arr[ctr++];
    }
   
    int i1 = 0;
    int i2 = 0;
    ctr = start;

    while ((i1 < len1) && (i2 < len2)) {
        if(first[i1] < second[i2]) {
            arr[ctr++] = first[i1++];
        }
        else{
            arr[ctr++] = second[i2++];
        }
    }   

    while(i1 < len1) {
        arr[ctr++] = first[i1++];
    }

    while(i2 < len2) {
        arr[ctr++] = second[i2++];
    }

    delete []first;
    delete []second;

}

void mergeSort(int *arr, int start, int end) {

    if(start >= end) {
        return;
    }
    int mid = (start+end)/2;
    mergeSort(arr, start, mid);
    mergeSort(arr, mid+1, end);
    merge(arr, start, end);
}


/******RANDOMISED QUICK SORT******/

int Partition(int arr[], int start, int end){

    srand(time(NULL));
    int RandomPivot = start + rand() % (end - start);
    swap(arr[RandomPivot], arr[start]);

    int pivot = arr[start]; 

    int cnt = 0;
    for(int i = start+1; i<=end; i++) {
        if(arr[i] <= pivot){
            cnt++;
        }
    }

    int pivotIndex = start + cnt;
    swap(arr[pivotIndex], arr[start]);

    int i = start;
    int j = end;

    while ((i<pivotIndex) && (j>pivotIndex)) {
        while(arr[i] <= pivot){
            i++;
        }
        while(arr[j] > pivot){
            j--;
        }
        if(i < pivotIndex && j > pivotIndex){
            swap(arr[i++], arr[j--]);
        }
    }

    return pivotIndex;
}


void RandomisedQuickSort(int arr[], int start, int end) {

    if(start >= end) 
        return;

    int partitionIndex = Partition(arr, start, end);
    RandomisedQuickSort(arr, start, partitionIndex-1);
    RandomisedQuickSort(arr, partitionIndex+1, end);

}

int main(){

    srand(time(nullptr));

    int A[500];
    int B[500];

    for (int i = 0; i < 500; i++){
        int temp = rand() % 1001;
        A[i] = temp;
        B[i] = temp; 
    }

    cout<<"Printing the Random 500 Elements generated:\n\n";

    for (int i = 0; i < 500; i++){
        cout<<A[i]<<"  ";
    }

    cout<<"\n\nArray After Merge Sorting is:\n\n";

    mergeSort(A,0,SIZE-1);

    for (int i = 0; i < 500; i++){
        cout<<A[i]<<"  ";
    }

    cout<<"\n\n\n\n";

    cout<<"Array after Randomised Quick Sorting is:\n\n";

    RandomisedQuickSort(B,0,SIZE-1);

    for (int i = 0; i < 500; i++){
        cout<<B[i]<<"  ";
    }

    cout<<"\n\n***PROGRAM OVER***";
  
    return 0;
}