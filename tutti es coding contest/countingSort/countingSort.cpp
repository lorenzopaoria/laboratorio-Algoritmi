#include <iostream>
#include <fstream>
using namespace std;

int findMin(int* arr, int n){
    int min;
    min=arr[0];
    for(int i=0;i<n;i++){
        if(arr[i]<min){
            min=arr[i];
        }
    }
    return min;
}

int findMax(int* arr,int n){
    int max;
    max=arr[0];
    for(int i=0;i<n;i++){
        if(arr[i]>max){
            max=arr[i];
        }
    }
    return max;
}

template <class T>

void printArr(T* arr,int n, ofstream &out){
    for(int i=0;i<n;i++) out<<arr[i]<<" ";
}   

int* countingSort(int* arr,int n, ofstream &out){
    int max=findMax(arr,n);
    int min=findMin(arr,n);
    int range=max-min+1;
    int* arrC= new int[range];

    for(int i=0;i<range;i++) arrC[i]=0;

    for(int i=0;i<n;i++) arrC[arr[i]-min]++;

    int j=0;
    for(int i=0;i<range;i++){
        while(arrC[i]>0){
            arr[j]=i+min;
            arrC[i]--;
            j++;
        }
    }
    delete[] arrC;
    return arr;
}

int main(){
    ifstream in("input.txt");
    ofstream out("output.txt");

    for(int i = 0; i < 100; i++){
        string type; in >> type;
        int n; in >> n;
        int* vett = new int[n];
        for(int j = 0; j < n; j++) in >> vett[j];
        vett = countingSort(vett, n, out);
        printArr(vett, n, out);
        delete [] vett;
   
        out << endl;
    }
}