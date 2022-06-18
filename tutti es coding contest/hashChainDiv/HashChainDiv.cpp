#include<iostream> 
#include <list> 
#include <fstream>
using namespace std;

template <class T> class HashTable{  		 
	public:	     	
		virtual HashTable<T>* insertKey(T x)=0;
	    virtual HashTable<T>* deleteKey(T key)=0;		
		virtual int searchKey(T key) = 0;	
};


template <class T> class ChainedHashTable : public HashTable<T>{
	private:
		int slots;
		int size;
		list<T>* table;

	protected:
		list<T>* getTable(){return this->table;}
  	public:
		virtual int computeHashFunction(T x) = 0;
	
		int getSlotNumber(){return slots;}

		int getSize(){return size;}

		void printHashTable(ofstream &out){
			for (int i = 0; i < this->getSlotNumber(); i++){
				out << i;
				for (auto x : table[i]) out << " --> [" << x << "]";
				out << endl;
			}
		}

		ChainedHashTable<T>(int x){
			this->slots = x;
			table = new list<T>[slots];
			size = 0;		
		}

		int searchKey(T key){
			int index = computeHashFunction(key);
			for (auto i = table[index].begin(); i != table[index].end(); i++){
				if (*i == key) return index;
			}
			return -1;	
		}

		int getBucketDim(int indx){
			//if(table[indx]nullptr) return 0;
            return table[indx].size();//non posso controllare se un oggetto esiste o meno
        }


		void searchKey(T key, int* pos1, int* pos2){
			*pos1 = computeHashFunction(key);
			for (auto i = table[*pos1].begin(); i != table[*pos1].end(); i++){
				if (*i == key){				
					*pos2 = (int) distance(table[*pos1].begin(), i);
					return;
				}
			}		 
			*pos2 = -1;
			return;
		}

		ChainedHashTable<T>* insertKey(T key){
			int index, pos2;		
			searchKey(key, &index, &pos2);		
			if (pos2 == -1){			
				table[index].push_front(key);
				size++;
			}
			return this;
		}

		ChainedHashTable<T>* deleteKey(T key){		
			int pos1 = -1;
			int pos2 = -1;
			searchKey(key, &pos1, &pos2);
			if (pos2 != -1){
				auto i = table[pos1].begin();
				advance(i, pos2);
				table[pos1].erase(i);
				size--;
			}
			return this;
		}
};


template <class T> class DivisionChainedHashTable : public ChainedHashTable<T>{
	private:
		int computeHashFunction(T x){
		int h = ((int)x % this->getSlotNumber());
		return h;
		}
 	public:
		DivisionChainedHashTable<T>(int edge_number) : ChainedHashTable<T>(edge_number) {}
};

template <class T> void doTask(DivisionChainedHashTable<T>& hash,string type, ifstream& in, ofstream& out){

    int n;
    string temp;
    in>>n;
    for(int i =0; i<n; i++){
        in>>temp;
        if(type == "int") hash.insertKey( stoi(temp) );
        else if(type == "double" ) hash.insertKey( stod(temp) );
        else if(type == "char" ) hash.insertKey( temp[0] );
        else if(type == "bool" ) hash.insertKey( stoi(temp) );
    }

    for(int i=0; i<n; i++)
        out<<hash.getBucketDim(i)<<" ";
    out<<"\n";

}

int main(){

    ifstream in("input.txt");
    ofstream out("output.txt");

    string type;
    int bucket;

    for(int i=0; i<100; i++){
        in>>type;
        in>>bucket;
        if(type == "int"){
            DivisionChainedHashTable<int> hash(bucket);
            doTask(hash, type, in, out);
        }if(type == "double"){
            DivisionChainedHashTable<double> hash(bucket);
            doTask(hash, type, in, out);
        }if(type == "char"){
            DivisionChainedHashTable<char> hash(bucket);
            doTask(hash, type, in, out);
        }if(type == "bool"){
            DivisionChainedHashTable<bool> hash(bucket);
            doTask(hash, type, in, out);
        }
    }




}