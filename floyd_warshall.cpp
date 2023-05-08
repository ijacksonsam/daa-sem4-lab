#include <iostream>
using namespace std;

class Graph
{
    int W[10][10], D[10][10], pi[10][10], n;

public:
    void createGraph()
    {
        cout << "enter n:";
        cin >> n;
        cout << "enter weight:";
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                cin >> W[i][j];
                D[i][j] = W[i][j];
                if(i==j || D[i][j]==9999)
                    pi[i][j] = -1;
                else
                    pi[i][j] = i;
            }
        }
    }
    void Floyd(){
        for (int k = 1; k <= n;k++){
            for (int i = 1; i <= n;i++){
                for (int j = 1; j <= n;j++){
                    if(D[i][j]>D[i][k]+D[k][j]){
                        D[i][j] = D[i][k] + D[k][j];
                        pi[i][j] = pi[k][j];
                    }
                }
            }
        }
        cout << "\nD matrix:" << endl;
        for (int i = 1; i <= n;i++){
            for (int j = 1; j <= n;j++){
                cout << D[i][j] << "\t";
            }
            cout << endl;
        }
        cout << "\npi matrix:" << endl;
        for (int i = 1; i <= n;i++){
            for (int j = 1; j <= n;j++){
                cout << pi[i][j] << "\t";
            }
            cout << endl;
        }
    }
};

int main(){
    Graph g;
    g.createGraph();
    g.Floyd();
    return 0;
}