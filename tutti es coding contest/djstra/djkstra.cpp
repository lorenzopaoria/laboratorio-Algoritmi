#include "Graph.cpp"
#include "BinaryHeap.cpp"
#include <fstream>
#include <string>

using namespace std;

template <class T> class PairMinHeap : public MinBinaryHeap<T>{//un heap dove ogni elemento è una coppia
public:
	PairMinHeap(int size) : MinBinaryHeap<T>(size) {}
	PairMinHeap(T** A, int size) : MinBinaryHeap<T>(A, size) {}
	double compare(T* a, T* b) { return (double)( ((*b).second) - ( (double) (*a).second) );}
	void printKey(int i) const {cout << (*(this->getPriorityQueue())[i]).first << " " << (*(this->getPriorityQueue())[i]).second << endl;}

	int findIndex(int index){
		for (int i = 1; i <= this->size(); i++){
			if((*(this->getPriorityQueue())[i]).first == index)
			  return i;
		}
		return -1;
	}
};




template <class H, class T> int Dijkstra(Graph<H, T>* graph, H keysrc, T*& distances, int*& predecessors){
	int src = graph->findIndex(keysrc);
	if (src == -1)
		return 0;
	int V = graph->getCurrentNodeNumber();
	distances = new T[V];
	predecessors = new int[V];	
	PairMinHeap<pair<int,T>>*q  = new PairMinHeap<pair<int,T>>(V);
	// Initially distance is for each node // manage the usage of the flag
	for (int i = 0; i < V; i++){
		if (i == src)		
			distances[i] = 0;		
		else		
			distances[i] = INT_MAX;
		predecessors[i] = -1;		
		q->enqueue(pair<int, T>(i, distances[i]));
	}	
	while (q->size()){//fino a quando ci sono elementi nella coda
		pair<int, T> top = *(q->extractMin());
		if (top.second == INT_MAX)
			break;
		int tmp = top.first;
		for (int i = 0; i < V; i++){ //looking for neighboors
			if (graph->getGraphIndexMatrix()[tmp][i] == 1){//se il nodo in pos temp i è adiacente allora possiamo rilassare
				T newval = distances[tmp] + graph->getGraphWeightMatrix()[tmp][i];
				if (newval < distances[i]){
					distances[i] = newval;
					predecessors[i] = tmp;
					int index = q->findIndex(i);
					q->decreaseKey(index, pair<int,T>(i,newval));
				}
			}
		}
	}
    delete q;
	return 1;
}





template <class H, class T> void printDistances(Graph<H, T>* graph, H key, T* distances, int* predecessors,ofstream &out){
	if (predecessors == NULL || graph->findIndex(key) < 0)
		return;	
	int src = graph->findIndex(key);
	int V = graph->getCurrentNodeNumber();
	for (int i = 0; i < V; i++)
		if (i != src){
			out << "Distance from " << key << " to " << *(graph->getKey(i)) << " is ";
			if (distances[i] != INT_MAX)
				cout << distances[i] << endl;
			else
				cout << "INF" << endl;
		}
	cout << "Printing predecessor list" << endl;
	for (int i = 0; i < V; i++){
	  if(i!=src)
		if (predecessors[i] > -1 )
			cout << "The predecessor of " << *(graph->getKey(i)) << " is " << *(graph->getKey(predecessors[i])) << endl;
		else 
			cout<< *(graph->getKey(i)) << " is unreacheable" << endl;		
	}
	return;
}


int main(){
	ifstream in("input.txt");
    ofstream out("output.txt");

    int n,m;
    string nodes,nodes1,nodes2,weight,type,comp1,comp2;
    int *predecessori=nullptr;
    int *distanze=nullptr;

    for(int i=0;i<100;i++){
        in>>n>>m>>type;
        if(type=="double"){
            Graph<double, int>* g = new Graph<double, int>(n);
            for(int j=0;j<n;j++){  
                in>>nodes;
                g->addNode(stod(nodes));
            }
            for(int k=0;k<m;k++){
                in>>nodes1>>nodes2>>weight;
                nodes1=nodes1.substr(1,3);
                weight=weight.substr(0,2);
                cout<<nodes1<<"       "<<nodes2<<"     "<<weight<<"             "<<endl;
                g->addEdge(stod(nodes1),stod(nodes2),stoi(weight));
            }
            in>>comp1>>comp2;   
            Dijkstra(g,stod(comp1),distanze,predecessori);
            out<<distanze[g->findIndex(stod(comp2))]<<endl;

        }
        
        if(type=="int"){
            Graph<int, int>* g = new Graph<int, int>(n);
            for(int j=0;j<n;j++){
                in>>nodes;
                g->addNode(stoi(nodes));
            }
            for(int k=0;k<m;k++){
                in>>nodes1>>nodes2>>weight;
                nodes1=nodes1.substr(1,2);
                weight=weight.substr(0,2);
                cout<<nodes1<<"       "<<nodes2<<"     "<<weight<<"             "<<endl;
                g->addEdge(stoi(nodes1),stoi(nodes2),stoi(weight));
            }
            in>>comp1>>comp2;
            Dijkstra(g,stoi(comp1),distanze,predecessori);
            out<<distanze[g->findIndex(stoi(comp2))]<<endl;

        }
    }
}