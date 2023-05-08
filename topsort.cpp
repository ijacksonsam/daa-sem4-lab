#include<iostream>
using namespace std;

enum vcolor
{
    WHITE,
    GRAY,
    BLACK
};

struct node{
    int ver;
    node *next;
};

struct vnode{
    string name;
    int d, f, pi ;
    vcolor color;
    node *adjptr;
};

class Graph{
    int n ,time;
    vnode vertex[10];
    node *list;

    public:     
    void createGraph(){
        cout<<"enter n:";cin>>n;
			for(int i=1;i<=n;i++){
				int m;
				cout<<"\nenter vertex name:";
				cin>>vertex[i].name;
				vertex[i].adjptr=NULL;
				cout<<"enter m:";cin>>m;
				node* cur=NULL;
				for(int j=1;j<=m;j++){
					node *t=new node;
					cout<<"adjnode "<<j<<" :";cin>>t->ver;
					if(cur==NULL)
						vertex[i].adjptr=t;
					else
						cur->next=t;
					t->next=NULL;
					cur=t;
				}
			}
    }

    void DFS_VISIT(int u){
        time++;
        vertex[u].d = time;
        vertex[u].color = GRAY;
        node *t = vertex[u].adjptr;
        while(t!=NULL){
            int v = t->ver;
            if(vertex[v].color==WHITE){
                vertex[v].pi = u;
                DFS_VISIT(v);
            }
            t = t->next;
        }
        time++;
        vertex[u].f = time;
        node *temp = new node;
        temp->ver = u;
        temp->next = list;
        list = temp;
    }

    void DFS(){
        time = 0;
        for (int i = 1; i <= n;i++){
            vertex[i].color = WHITE;
            vertex[i].pi = -1;
        }
        list = NULL;
        for (int i = 1; i <= n;i++){
            if(vertex[i].color==WHITE){
                DFS_VISIT(i);
            }
        }
    }

    void TOPSORT(){
        cout<<"linear ordering of vertices:";
        DFS();
        node *t=list;
        while(t!=NULL){
            cout << vertex[t->ver].name << "\t";
            t = t->next;
        }
    }
};

int main(){
    Graph g;
    g.createGraph();
    g.TOPSORT();
    return 0;
}