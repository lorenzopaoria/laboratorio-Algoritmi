#include <iostream>
#include <fstream>
using namespace std;


template <class H>
class Heap{
private:
    H* vett;
    int heapsize;
    int maxdim;

    int left(int i){return i << 1;}
    int right(int i){return (i << 1) | 1;}
    int parent(int i){return i >> 1;}

public:
    Heap(int x): maxdim(x){
        heapsize = 0;
        vett = new H[maxdim];
    }
    ~Heap(){delete [] vett;}

    void Heapify(int i){
        int l = left(i);
        int r = right(i);
        int min = i;

        if(l <= heapsize && vett[l] < vett[min])
            min = l;
        if(r <= heapsize && vett[r] < vett[min])
            min = r;
        if(min != i){
            swap(vett[min], vett[i]);
            Heapify(min);
        }
    }
    
     void recursiveHeapify(int i){
        int p= parent(i);
        int min = i;
  
        if(i>1 && vett[min]<vett[p]){
          swap(vett[min],vett[p]);
          recursiveHeapify(vett[p]);
        }
    }

    void enqueue(H x){
        heapsize++;
        vett[heapsize] = x;

        int i = heapsize;
        while(i > 1 && vett[parent(i)] > vett[i]){
            swap(vett[parent(i)], vett[i]);
            i = parent(i);
        }
    }

    void modifyKey(int i, H newVal){
        if(newVal>vett[i]){
            vett[i]=newVal;
            Heapify(vett[i]);
        }else if(newVal<vett[i]){
            vett[i]=newVal;
            recursiveHeapify(vett[i]);
        }else vett[i]=newVal;  
    }

    bool isHeap (){
      if(heapsize==1) return true;//se esiste root
      for(int i=1;i<=heapsize/2;i++){
        if(right(i)<=heapsize){
          if(vett[left(i)]<vett[i] || vett[right(i)]<vett[i]){
            return false;
          }
        }
      }
      return true;    
    }

    void print(ofstream &out){
        for(int i = 1; i <= heapsize; i++)
            out << vett[i] << " ";
        out << endl;
    }
};


int main(){
  ifstream in("input.txt");
  ofstream out("output.txt");


  for(int i = 0; i < 100; i++){
    string type; in >> type;
    int n; in >> n;
    if(type == "int"){
      Heap<int>* t = new Heap<int>(500);

      for(int j = 1; j <= n; j++){
        int tmp; in >> tmp;
        t->enqueue(tmp);
      }
      if(t->isHeap()) cout<<"è un heap";
      else cout<<"non è un heap"<<endl;
      t->print(out);
      delete t;

    }
    else if(type == "bool"){
      Heap<bool>* t = new Heap<bool>(500);

      for(int j = 1; j <= n; j++){
        bool tmp; in >> tmp;
        t->enqueue(tmp);
      }
      t->isHeap();
      t->print(out);
      delete t;
    }
    else if(type == "double"){
      Heap<double>* t = new Heap<double>(500);

      for(int j = 1; j <= n; j++){
        double tmp; in >> tmp;
        t->enqueue(tmp);
      }
      t->isHeap();
      t->print(out);
      delete t;

    }
    else if(type == "char"){
      Heap<char>* t = new Heap<char>(500);

      for(int j = 1; j <= n; j++){
        char tmp; in >> tmp;
        t->enqueue(tmp);
      }
      t->isHeap();
      t->print(out);
      delete t;
    }
  }
}
