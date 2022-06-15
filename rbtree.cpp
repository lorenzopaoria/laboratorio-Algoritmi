//RB_NODE

#ifndef RBNODE_H
#define RBNODE_H



template<class T>
class RBNode{
public:
	T key;
	static const bool BLACK = 0;
	static const bool RED = 1;
	bool color; //0 => nero, 1 => rosso
	RBNode<T>* parent, left, right;

	RBNode<T>* getUncle(){
		if( parent == nullptr || parent->parent == nullptr) return nullptr;
		if( parent == parent->parent->left) return parent->parent->right;
		else return parent->parent->right;
	}

	RBNode<T>* getBrother(){
		if(parent == nullptr) return nullptr;
		if( this == parent->left) return parent->right;
		else return parent->left;
	}

	RBNode(T _key, bool _color = RBNode<T>::RED, RBNode<T>* _parent = nullptr, RBNode<T>* _left = nullptr, RBNode<T>* _right = nullptr):
	key(_key), color(_color), parent(_parent), left(_left), right(_right){}

};


#endif

//RB_TREE

#ifndef RBTREE_H
#define RBTREE_H

template<class T>
class RBTree{

private:

	RBNode<T>* root;
	RBNode<T>* NIL;

	RBNode<T>* searchInsert(T key){
		Node<T>* curr = root;
		while(true){
			if(key < curr->key ){
				if( curr->left == nullptr) return curr;
				else curr = curr->left;
			}else{
				if( curr->right == nullptr) return curr;
				else curr = curr->right;
			}
		}
		return nullptr;
	}

	void deleteTree(RBNode<T>* n){
		if(n == nullptr) return;
		deleteTree(n->left);
		deleteTree(n->right);
		delete n;
	}

	//se insert è true, si inserisce il nodo; se è false, si effettua una fixup
	void insert_fixup(RBNode<T>* n, bool insert){

		if(n == nullptr) return;

		//FIXUP: se la root è rossa
		if(!insert && root->color == RBNode<T>::RED){
			root->color = RBNode<T>::BLACK;
			return;
		}
		//INSERT caso 1: il nodo da inserire è una root
		if(root == nullptr){
			root = n;
			insert_fixup(n, false);
			root->color = RBNode<T>::BLACK;
			return;	
		}
		 
		RBNode<T>* p;
		if(!insert) p = n->parent;
		else{
			p = searchInsert(key); //parent del nodo da inserire
			//inseriamo il nodo nel posto corretto
			if( key < p->key ) p->left = n; 
			else p->right = n;
			//caso 2: il padre del nuovo nodo è un nodo nero
			if(p->color == RBNode<T>::BLACK) return;
		}

		//caso 3: padre e zio rossi (lo zio è il fratello del padre)
		if(p->color == RBNode<T>::RED && p->getBrother()->color == Node<T>::RED ){
			p->color == RBNode<T>::BLACK;
			p->getBrother()->color = RBNode<T>::BLACK;
			p->parent->color = RBNode<T>::RED;
			//FIX-UP SUL NONNO
			insert_fixup(p->parent, false); //fix-up
		}
	}

public:
	RBTree(RBNode<T>* _root = nullptr): root(_root) {}
	RBTree(T key){ root = new RBNode<T>(key, RBNode<T>::BLACK); }
	~RBTree(){ deleteTree(root); }


	void insert(T key){
		RBNode<T> *n = new RBNode<T>(key, RB<T>::RED);
		insert_fixup(n, true); 
	}

};

#endif