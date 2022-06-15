#ifndef HASHTABLE_H
#define HASHTABLE_H

#include<list>
#include<cmath>

using namespace std;

template<class T>
class HashTable{

private:

	int size;
	list<T> **arr;

	int inline hashdiv(T key){ return fmod(key, size); }

public:

	HashTable(int _size): size(_size){
		arr = new list<T>*[_size];
		for(int i=0; i<size; i++) arr[i] = new list<T>();
	}

	~HashTable(){
		for(int i = 0; i<size; i++) delete arr[i];
		delete [] arr;
	}

	void insert(T key){ arr[hashdiv(key)]->push_back(key);}

	int getDim(int i){ return arr[i]->size(); }


};

#endif