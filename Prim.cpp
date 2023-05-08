#include<iostream>
#include<fstream>
using namespace std;

class PQ;

struct node{
    int ver, wt;
    node *next;
};

struct vnode{
    string name;
    int key, pi, qid;
    bool inQueue;
    node *adjptr;
};

class Graph{
    vnode vertex[10];
    int n;
    friend class PQ;
    public:
    void createGraph(){
        ifstream fin("priminput.txt");
        int m;
        fin >> n;
        for (int i = 1; i <= n;i++){
            fin >> vertex[i].name;
            fin >> m;//no. of adj vertices
            vertex[i].adjptr = NULL;
            node *cur = NULL;
            for (int j = 1; j <= m;j++){
                node *t = new node;
                fin >> t->ver;
                fin >> t->wt;
                t->next = NULL;
                if(cur==NULL){
                    vertex[i].adjptr = t;
                }else{
                    cur->next = t;
                }
                cur = t;
            }
        }
    }

    void display(){
        cout << "\nthe input graph ---->" << endl;
        for (int i = 1; i <= n;i++){
            cout << vertex[i].name;
            node *t = vertex[i].adjptr;
            while(t!=NULL){
                cout << "-->(" << vertex[t->ver].name << "," << t->wt << ")";
                t = t->next;
            }
            cout << endl;
        }
    }
    void PRIMS(int s);
};

class PQ{
    int heapsize;
    int Q[10];
    Graph *G;
    public:
    void MIN_HEAPIFY(int i){
        int smallest = i;
        int l, r;
        l = 2 * i;
        r = 2 * i + 1;
        if(l<=heapsize && G->vertex[Q[l]].key < G->vertex[Q[i]].key)
            smallest = l;
        if(r<=heapsize && G->vertex[Q[r]].key < G->vertex[Q[smallest]].key)
            smallest = r;
        if(smallest!=i){
            int t = Q[i];
            Q[i] = Q[smallest];
            Q[smallest] = t;
            G->vertex[Q[i]].qid = i;
            G->vertex[Q[smallest]].qid = smallest;
            MIN_HEAPIFY(smallest);
        }
    }

    void CREATE_PQ(Graph *g){
        G = g;
        heapsize = G->n;
        for (int i = 1; i <= heapsize;i++){
            G->vertex[i].qid = i;
            G->vertex[i].inQueue = true;
            Q[i] = i;
        }
        for (int i = heapsize / 2; i >= 1;i--){
            MIN_HEAPIFY(i);
        }
    }

    bool isEmpty(){
        if(heapsize==0)
            return true;
        return false;
    }
    
    int EXTRACT_MIN(){
        int x=Q[1];
        G->vertex[Q[1]].inQueue = false;
        Q[1] = Q[heapsize];
        G->vertex[Q[1]].qid = 1;
        heapsize--;
        MIN_HEAPIFY(1);
        return x;
    }

    void DECREASE_KEY(int i,int w){
        G->vertex[Q[i]].key = w;
        while(i>1 && G->vertex[Q[i/2]].key > G->vertex[Q[i]].key){
            int t = Q[i];
            Q[i] = Q[i / 2];
            Q[i / 2] = t;
            G->vertex[Q[i]].qid = i;
            G->vertex[Q[i/2]].qid = i/2;
            i = i / 2;
        }
    }
};

void Graph::PRIMS(int s){
    PQ pq;
    for (int i = 1; i <= n;i++){
        vertex[i].key = 9999;
        vertex[i].pi = -1;
    }
    int total = 0;
    vertex[s].key = 0;
    pq.CREATE_PQ(this);
    cout << "\nedges in mwst are:"<<endl;
    while(!pq.isEmpty()){
        int u = pq.EXTRACT_MIN();
        if(vertex[u].pi!=-1){
            cout << vertex[vertex[u].pi].name << "-->" << vertex[u].name << endl;
            total += vertex[u].key;
        }
        node *t = vertex[u].adjptr;
        while(t!=NULL){
            int v = t->ver;
            if(vertex[v].inQueue && t->wt<vertex[v].key){
                pq.DECREASE_KEY(vertex[v].qid, t->wt);
                vertex[v].pi = u;
            }
            t = t->next;
        }
    }
    cout << "total cost = " << total;
}

int main(){
    Graph g;
    g.createGraph();
    g.display();
    g.PRIMS(1);
    return 0;
}