#include<iostream>
#include<string.h>
#include<limits.h>

using namespace std;

class LCS{
    char X[100], Y[100],b[100][100];
    int c[100][100],m,n;
    public:
    LCS()
    {
        for (int i = 0; i < 100; i++)
        {
            for (int j = 0; j < 100; j++)
                c[i][j] = -1;
        }
    }
    void getInput(){
        string x1, y1;
        cout << "enter x:";
        cin >> x1;
        cout << "enter y:";
        cin >> y1;
        m = x1.length();
        n = y1.length();
        for (int i = 1; i <= m;i++)
            X[i] = x1[i - 1];
        for (int j = 1; j <= n;j++)
            Y[j] = y1[j - 1];
    }

    void lcs_bu(){
        for (int i = 0; i <= m;i++){
            c[i][0] = 0;
        }
        for (int j = 1; j <= n;j++){
            c[0][j] = 0;
        }
        for (int i = 1; i <= m;i++){
            for (int j = 1; j <= n;j++){
                if(X[i]==Y[j]){
                    c[i][j] = c[i - 1][j - 1] + 1;
                    b[i][j] = 'd';
                }
                else{
                    if(c[i-1][j]>=c[i][j-1]){
                        c[i][j] = c[i - 1][j];
                        b[i][j] = 't';
                    }else{
                        c[i][j] = c[i][j - 1];
                        b[i][j] = 'l';
                    }
                }
            }
        }
        cout << "\nlcs bu =" << c[m][n] << endl;
        printlcs(m, n);
    }

    void printlcs(int i,int j){
        if(i==0 || j==0){
            return;
        }
        else if(b[i][j]=='l')
            printlcs(i, j - 1);
        else if(b[i][j]=='t')
            printlcs(i - 1, j);
        else{
            printlcs(i - 1, j - 1);
            cout << X[i] << '\t';
        }
    }

    int lcs_td(int i,int j){
        if(c[i][j]>=0)
            return c[i][j];
        if (i == 0 || j==0){
            c[i][j] = 0;
            return c[i][j];
        }
        else{
            if(X[i]==Y[j]){
                c[i][j] = lcs_td(i - 1, j - 1) + 1;
                b[i][j] = 'd';
            }else{
                c[i - 1][j] = lcs_td(i - 1, j);
                c[i][j - 1] = lcs_td(i, j - 1);
                if(c[i-1][j]>=c[i][j-1]){
                    c[i][j] = c[i - 1][j];
                    b[i][j] = 't';
                }else{
                    c[i][j] = c[i][j-1];
                    b[i][j] = 'l';
                }
            }
            return c[i][j];
        }
    }

    void call_lcs_td(){
        cout << "\nlcs td =" << lcs_td(m,n) << endl;
        printlcs(m, n);
    }
};

int main(){
    LCS l;
    l.getInput();
    // l.lcs_bu();
    l.call_lcs_td();
    return 0;
}