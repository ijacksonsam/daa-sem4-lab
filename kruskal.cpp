#include<iostream>
#include<fstream>

using namespace std;

struct node{
    int wt, from, to;
    bool status;
    node *next;
};

class Graph{
    string vertex[20];
    int parent[20], rank[20] ,n ,m;
    node *elist;

    public:
    void createGraph(){
        ifstream fin("krus_input.txt");
        fin>>n;
        for (int i = 1; i <= n;i++){
            fin >> vertex[i];
        }
        //no.of edges
        fin >> m;
        elist = NULL;
        for (int i = 1; i <= m;i++){
            node *t = new node;
            fin >> t->from;
            fin >> t->to;
            fin >> t->wt;
            t->status = false;
            t->next = NULL;
            if(elist==NULL || elist->wt > t->wt){
                t->next = elist;
                elist = t;
            }
            else{
                node *temp = elist;
                while(temp->next!=NULL && temp->next->wt < t->wt){
                    temp = temp->next;
                }
                t->next = temp->next;
                temp->next = t;
            }
        }
    }

    void MakeSet(int i){
        parent[i] = i;
        rank[i] = 0;
    }

    int FindSet(int v){
        while(v!=parent[v]){
            v = parent[v];
        }
        return v;
    }

    void Union(int u,int v){
        if(rank[u]>rank[v])
            parent[v] = u;
        else{
            parent[u] = v;
            if(rank[u]==rank[v])
                rank[v]++;
        }
    }

    void FindSpanningTree(){
        for (int i = 1; i <= m;i++){
            MakeSet(i);
        }
        int count = 1, totalwt = 0;
        node *temp = elist;
        cout << "edges included in mwst:" << endl;
        while(temp != NULL && count <= n-1){
            int i = FindSet(temp->from);
            int j = FindSet(temp->to);
            if(i!=j){
                temp->status = true;
                count++;
                totalwt += temp->wt;
                // cout << vertex[temp->from] << "-->" << vertex[temp->to] << endl;
                cout << temp->from << "-->" << temp->to << endl;
                Union(i, j);
            }
            temp = temp->next;
        }
        cout << "total weight =" << totalwt;
    }
};

int main(){
    Graph g;
    g.createGraph();
    g.FindSpanningTree();
    return 0;
}