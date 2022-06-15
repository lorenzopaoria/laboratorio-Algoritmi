#include<mem.h> //memcopy
#include<iostream>
#include<vector>
#include<queue>

using namespace std;

template <class H, class T> 
class AdjGraph{

private:

    H **keyMap; //array di puntatori ad H
    T ***W; //matrice di puntatori ad elementi W (pesi)
    int maxLength;
    int nodeNum, edgeNum;

    void DFS_VISIT(int s, int& t, vector<int>& pred, vector<int>& discovery, vector<int>& end, vector<int>& color){

        discovery[s] = ++t;
        color[s] = 1;

        for(int i=0;i<nodeNum; i++){
            if( W[s][i] != nullptr && color[i] == 2){ //adiacente non scoperto
                pred[i] = s;
                DFS_VISIT(i, t, pred, discovery, end, color);
            }
        }

        end[s] = ++t;
        color[s] = 0;
    }

public:

    AdjGraph(int _maxLength) : maxLength(_maxLength){

        keyMap = new H*[maxLength];
        W = new T**[maxLength];

        for(int i=0; i<maxLength; i++){
            W[i] = new T*[maxLength];
            for(int j=0; j<maxLength; j++) W[i][j] = nullptr;
            keyMap[i] = nullptr;
        }

        nodeNum = edgeNum = 0;
              
    }

    ~AdjGraph(){
        for(int i = 0; i<maxLength; i++){
            for(int j = 0; j < maxLength; j++){
                delete W[i][j];
                delete keyMap[i];
            }
            delete[] W[i];
        }
        delete[] W;
        delete[] keyMap;
    }

    //ritorna l'indice dove è contenuto il valore Key
    int findIndex(H key){
        for(int i = 0; i<nodeNum; i++)
            if(*keyMap[i] == key)
                return i;
        return -1;
    }

    //aggiunge un nodo a keyMap
    AdjGraph<H, T>* addNode(H const& key){
        if(nodeNum>=maxLength) return this;
        keyMap[nodeNum++] = new H(key);
        return this;
    }

    AdjGraph<H, T>* removeNode(H const& key){

        int index = findIndex(key);
        if(index < 0 || nodeNum <=0) return this;
        delete keyMap[index]; //1
        for(int i = index+1; i<nodeNum; i++) //2
            keyMap[i-1] = keyMap[i];
        delete keyMap[nodeNum--]; //valore duplicato alla fine di keyMap

        //3
        for(int i = 0; i<maxLength; i++){
            int count = (W[index][i] != nullptr) + (W[i][index] != nullptr) - (i == maxLength>>1);
            delete W[index][i]; delete W[i][index];
            edgeNum -= count;
        }

        //4: shiftare le righe e le colonne
        for(int i = index + 1; i < maxLength; i++)
            for(int j = 0; j < maxLength; j++){
                W[i-1][j] = W[i][j];
                W[j][i-1] = W[j][i]; 
            }

        return this;

    }

    AdjGraph<H, T>* addEdge(H const& u, H const& v, T const& w){
        int uIndex = findIndex(u);
        int vIndex = findIndex(v);

        //cout<<"addEdge: u = "<<uIndex<<", v = "<<vIndex<<endl;
        if( uIndex < 0 || vIndex < 0 || edgeNum >= maxLength*maxLength ) return this;

        W[uIndex][vIndex] = new T(w);
        edgeNum++;
        return this;
    }

    AdjGraph<H, T>* removeEdge(H const& u, H const& v){
        int uIndex = findIndex(u);
        int vIndex = findIndex(v);
        if( uIndex < 0 || vIndex < 0 || edgeNum <=0 ) return this;

        W[uIndex][vIndex] = nullptr;
        edgeNum--;
        return this;
        
    }

    int getNodeNum(){ return nodeNum; }
    int getEdgeNum(){ return edgeNum; }

    void printNodes(){
        cout<<"[    ";
        for(int i = 0; i<nodeNum; i++) cout<<*keyMap[i]<<"    ";
        cout<<"]\n";
    }

    void printW(){
        for(int i=0 ; i< nodeNum; i++)
        {               
            for(int j = 0; j < nodeNum; j++){
                if( W[i][j] == nullptr) cout<<"inf      ";
                else cout<<*W[i][j]<<"      ";
            }
            cout<<'\n';
        }
                
    }

    void DFS(vector<int>& pred, vector<int>& discovery, vector<int>& end){

        pred = vector<int>(nodeNum, -1);
        discovery = vector<int>(nodeNum, -1);
        end = vector<int>(nodeNum, -1);

        vector<int> color(nodeNum, 2); //0 black 1 grey 2 white
        
        int time = 0;
        for(int i=0; i<nodeNum; i++)
            if( color[i] == 2 )
                DFS_VISIT(i,time, pred, discovery, end, color);

    }

    void BFS(H source, vector<int>& pred, vector<int>& dist){

        pred = vector<int>(nodeNum, -1);
        dist = vector<int>(nodeNum, -1);
        vector<int> color(nodeNum, 2); //0 black 1 grey 2 white
        queue<int> q = queue<int>();

        int index = findIndex(source);
        q.push(index);
        color[index] = 1;
        dist[index] = 0;

        while ( !q.empty() ){
            int cur = q.front(); q.pop();
            for(int i=0; i<nodeNum; i++){
                if(W[cur][i] != nullptr && color[i] == 2){
                    q.push(i);
                    color[i] = 1;
                    pred[i] = cur;
                    dist[i] = dist[cur]+1;
                }
            }
            color[cur] = 0;
        }

    }



};
