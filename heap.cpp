#include <iostream>
#include <fstream>

using namespace std;

template <class T> class heap{
    private:
        T* arr;
        int heapsize;

        int left(int i){return i<<1;}
        int right(int i){return (i<<1)|1;}
        int parent(int i){return i>>1;}

    public:
        heap(){ heapsize=0; }

        void MaxHeapify(T* arr, int n){
            int l=left(i);
            int r=right(i);
            int max=i;

            if(l<=heapsize && arr[l]>arr[max]) max=l;
            if(r<=heapsize && arr[r]>arr[max]) max=r;

            if(max!=i){
                swap(arr[max],arr[i]);
                MaxHeapify(max);
            }
        }

        void MinHeapify(T* arr, int n){
            int l=left(i);
            int r=right(i);
            int min=i;

            if(l<=heapsize && arr[l]<arr[min]) min=l;
            if(r<=heapsize && arr[r]<arr[min]) min=r;
            if(min!=i){
                swap(arr[min],arr[i]);
                MinHeapify(min);
            }
        }
};
