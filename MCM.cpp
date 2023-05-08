#include<iostream>
#include<limits.h>
using namespace std;

class MCM{
    int P[100], M[10][10], s[10][10];
    int p, n;
    public:
    MCM(){
        for (int i = 1; i <= n;i++){
            for (int j = 1; j <= n;j++){
                M[i][j] = -1;
            }
        }
    }
    void getInput(){
        cout << "enter p:";
        cin >> p;
        n = p - 1;
        cout << "enter p arr:";
        for (int i = 0; i < p; i++)
        {
            cin >> P[i];
        }          
    }

    void mcm_bu(){
        for (int i = 1; i <= n;i++)
            M[i][i] = 0;
        for (int l = 1; l <= n - 1;l++){
            for (int i = 1; i <= n - l;i++){
                int j = i + l;
                M[i][j] = INT_MAX;
                for (int k = i; k < j;k++){
                    int q = M[i][k] + M[k + 1][j] + P[i - 1] * P[k] * P[j];
                    if(q<M[i][j]){
                        M[i][j] = q;
                        s[i][j] = k;
                    }
                }
            }
        }
        cout << "\nnumber of scalar mult(bu) =" << M[1][n] << endl;
    }

    void printmcm(int i,int j){
        if(i==j){
            cout << "A" << i;
        }else{
            cout << "(";
            printmcm(i, s[i][j]);
            printmcm(s[i][j] + 1, j);
            cout << ")";
        }
    }

    void callpmcm(){
        printmcm(1, n);
    }

    int mcm_td(int i,int j){
        if(M[i][j]>=0)
            return M[i][j];
        if(i==j){
            M[i][j] = 0;
            return M[i][j];
            return 0;
        }else{
            M[i][j] = INT_MAX;
            for (int k = i; k < j;k++){
                int q = mcm_td(i, k) + mcm_td(k + 1, j) + P[i - 1] * P[k] * P[j];
                if(q<M[i][j]){
                    M[i][j] = q;
                    s[i][j] = k;
                }
            }
            return M[i][j];
        }
    }

    void call_td(){
        cout << "\nnumber of scalar mult(td) =" << mcm_td(1,n) << endl;
    }

};

int main(){
    MCM m;
    m.getInput();
    // m.mcm_bu();
    m.call_td();
    m.callpmcm();
    return 0;
}