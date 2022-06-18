#include <iostream>
#include <fstream>

using namespace std;

template <class T> class Heap{

    private:
        T* arr;
        int heapSize;

        int left(int i){return i<<1;}
        int right(int i){return (i<<1)|1;}
        int parent(int i){return i>>1;}

    public:
        Heap(){ heapSize=0; }

        void Heapify(int i){
            int l=left(i);
            int r=right(i);
            int max=i;

            if(l<= heapSize && arr[l]>arr[max])
                max=l;
            if(r<= heapSize && arr[r]>arr[max])
                max=r;
            if(max!=i){
                swap(arr[i],arr[max]);
                Heapify(max);
            }
        }

        void Build(T* arr2,int n){
            heapSize=n;
            arr=arr2;
            cout<<"dentro build prima del for"<<endl;
            for(int s=heapSize/2;s>0;s--){
                cout<<"richiamo heapify"<<endl;
                Heapify(s);
                
            }
        }

        void print(ofstream &out){
            for(int i=1; i<=heapSize;i++)
                out<<arr[i]<<"\t";
            out<<"\n";
        }
};

int main(){
    ifstream in("input.txt");
    ofstream out("output.txt");

    for(int i=0;i<100; i++){
        string type; in>>type;
        int n;in>> n;
        cout<<type<<endl;
        if(type=="int"){
            Heap<int>* t = new Heap<int>();
            int* vett = new int[200];
            for(int j = 1; j <= n; j++){
                int tmp; in >> tmp;
                vett[j] = tmp;
            }
            cout<<"prima build"<<endl;
            t->Build(vett, n);
            cout<<"prima della print"<<endl;
            t->print(out);
            cout<<"arriva qua";
            delete t;
            delete []vett;
            
        }else if(type == "bool"){
            Heap<bool>* t = new Heap<bool>();
            bool* vett = new bool[200];
            for(int j = 1; j <= n; j++){
                bool tmp; in >> tmp;
                vett[j] = tmp;
            }
            t->Build(vett, n);
            t->print(out);
            delete t;
            delete []vett;
        
        }else if(type == "double"){
            Heap<double>* t = new Heap<double>();
            double* vett = new double[200];
            for(int j = 1; j <= n; j++){
            double tmp; in >> tmp;
            vett[j] = tmp;
        }
        t->Build(vett, n);
        t->print(out);
        delete t;
        delete []vett;
        
        }else if(type == "char"){
            Heap<char>* t = new Heap<char>();
            char* vett = new char[200];
            for(int j = 1; j <= n; j++){
                char tmp; in >> tmp;
                vett[j] = tmp;
            }
            t->Build(vett, n);
            t->print(out);
            delete t;
            delete []vett;
        }    
    }

}