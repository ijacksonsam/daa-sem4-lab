#include<iostream>
using namespace std;

struct node{
    int from,to,wt;
    node *next;
};

struct vnode{
    string name;
    int d, pi;
    node *adjptr;
};

class Graph{
    vnode vertex[10];
    node *elist;
    int m, n;
    public:
    void createGraph(){
        cout << "\nenter n:";
        cin >> n;
        cout << "enter vertex names:" << endl;
        for (int i = 1; i <= n;i++){
            cin >> vertex[i].name;
        }
        cout << "enter m:";
        cin >> m;
        elist = NULL;
        node *cur = NULL;
        for (int i = 1; i <= m;i++){
            node *t = new node;
            cout << "Enter index of from vertex: ";
 		    cin >> t->from;
 		    cout << "Enter index of to vertex: ";
		    cin >> t->to;
 		    cout << "Enter edge weight: "; 		    
 		    cin >> t->wt;
            t->next = NULL;
            if(elist==NULL)
                elist = t;
            else
                cur->next = t;
            cur = t;
        }
    }

    void INITIALIZE_SINGLE_SOURCE(int s){
        for (int i = 1; i <= n;i++){
            vertex[i].d = 9999;
            vertex[i].pi = -1;
        }
        vertex[s].d = 0;
    }

    void RELAX(int u,int v,int w){
        if(vertex[v].d>(vertex[u].d+w)){
            vertex[v].d = vertex[u].d + w;
            vertex[v].pi = u;
        }
    }

    bool BELLMAN_FORD(int s){
        INITIALIZE_SINGLE_SOURCE(s);
        for (int i = 1; i <= n - 1;i++){
            node *t = elist;
            while(t!=NULL){
                RELAX(t->from, t->to, t->wt);
                t = t->next;
            }
        }
        node *t = elist;
        while(t!=NULL){
            if(vertex[t->to].d>vertex[t->from].d+t->wt)
                return false;
            t = t->next;
        }
        return true;
    }

    void display(){
		cout << "vid\tName\tDist\tParent" << endl;
		for (int i=1; i<=n; i++){
			cout << i << "\t" << vertex[i].name << "\t" << vertex[i].d << "\t"<< vertex[i].pi << endl;
		}
		cout << endl;
	}
};

int main(){
    Graph g;
    g.createGraph();
    bool res=g.BELLMAN_FORD(1);
    if(res)
        g.display();
    else{
        cout << "graph contains negative values cycles...." << endl;
    }
    return 0;
}