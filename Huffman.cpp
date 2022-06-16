#include <iostream>
#include <vector>
#include <string>
#include "Heap.cpp"//standard heap

using namespace std;

template <class T> class HuffmanMinHeap : public MinBinaryHeap<T>{
	 public:
		HuffmanMinHeap(int size) : MinBinaryHeap<T>(size) {}
		HuffmanMinHeap(T** A, int size) : MinBinaryHeap<T>(A, size) {}
	
		double compare(T* a, T* b){ return ((double) b->getFrequency() - a->getFrequency()); }	
	
		void printKey(int i) const{ cout << ((this->getPriorityQueue())[i])->getKey() << "," << ((this->getPriorityQueue())[i])->getFrequency() << endl;}
};



template <class T> class Node{
	private:
		T key;
		int frequency;
		Node<T> *left, *right;	
	public:
		Node<T>(T key, int _frequency){
			this->key = key;
			left = right = NULL;		
			this->frequency = _frequency;
		}
	
		T getKey(){ return key; }
	
		int isLeaf(){return (getLeftNode()==NULL && getRightNode()==NULL); }
	
		int getFrequency(){ return frequency;}
	
		Node<T>* getLeftNode(){ return left;}
	
		Node<T>* getRightNode(){return right;}
	
		void setKey(T key){this->key = key;}
	
		void setFrequency(int frequency){this->frequency = frequency;}	
	
		void setLeft(Node<T>* left){ this->left = left;}
	
		void setRight(Node<T>* right){this->right = right;}
};





class HuffmanCode{ 	 
	private:	
		Node<char>* root;
		vector<pair<char,string>> map; //use hash table instead
		void buildCodes(Node<char>* root, string str){		  
			  if (root->isLeaf()){			  
				  for (size_t i = 0; i < map.size(); i++){
					  if (root->getKey() == map[i].first){
						  map[i].second=str;
						  return;
					  }
				  }
			  }
			  buildCodes(root->getLeftNode(), str + "0");
			  buildCodes(root->getRightNode(), str + "1");
		  }

		void buildRecursiveCodes(){ buildCodes(root, ""); }

	  public:	  
		  HuffmanCode(char* chars,  int* frequencies, size_t size){
			  root = NULL;
			  HuffmanMinHeap<Node<char>>* heap = new HuffmanMinHeap<Node<char>>(size);	
			  map = vector<pair<char,string>>(size);
			  for (size_t i = 0; i < size; i++){
				  map[i] = pair<char, string>(chars[i], "");
			  }
			  for (size_t i = 0; i < size; i++){			  
				  Node<char> tmp = Node<char>(chars[i], frequencies[i]);				  
				  heap->enqueue(tmp);				 
			  }			  
			  for (size_t i = 0; i < size-1; i++){
				  Node<char>* f = heap->extractMin();
				  Node<char>* s = heap->extractMin();			 
				  Node<char> c = Node<char>('\0', f->getFrequency() + s->getFrequency());
				  c.setLeft(f);
				  c.setRight(s);
				  heap->enqueue(c);
			  }
			  root = heap->extractMin();
			  delete heap;
			  buildIterativeCodes();
		  }	  

		  Node<char>* getHuffmanTree(){return root;}	  

		  vector<pair<char, string>>& getCodes(){return map;}

		  void printCodes(){
			for (auto t : map)		  
			  cout << t.first << ":" << t.second << endl;		  
		  }

		  string encode(string& s){
			  string result = "";
			  for (auto c : s){
				  size_t i = 0;
				  for (; i < map.size(); i++){
					  if (map[i].first == c){
						  result.append(map[i].second);
						  break;
					  }
				  }
				  if (i == map.size()) return "";
			  }
			  return result;
		  }

		  string decode(string& s){
			  if (s.empty())
				  return "";
			 string result = "";
			 string tmp = "";
			 size_t i = 0;
			 while(i < s.size()){ 			 
				 tmp+=s[i];				 	 
				 for (size_t j = 0; j < map.size(); j++){
					 if (tmp == map[j].second){					
						 result+=map[j].first;
						 tmp = "";
						 break;
					 }
				 }
				 i++;
			  }
			 return result;
		  } 
};
