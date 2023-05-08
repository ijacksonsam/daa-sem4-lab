#include<iostream>
#include<string>

using namespace std;

class SM{
    char P[100], T[100];
    int pi[100], m, n;
    public:
    void getInput(){
        string s1, s2;
        cout << "enter text:";
        cin >> s1;
        cout << "enter pattern:";
        cin >> s2;
        n = s1.length();
        m = s2.length();
        for (int i = 0; i < n;i++){
            T[i + 1] = s1[i];
        }
        for (int i = 0; i < m;i++){
            P[i + 1] = s2[i];
        }
    }

    int PREPROCESS(){
        int p = 0;
        int q = 4999;
        int d = 10;
        for (int i = 1; i <= m;i++)
            p = (d * p + P[i]) % q;
        return p;
    }

    void RK_MATCHER(){
        int q = 4999, d = 10;
        int p = PREPROCESS();
        int h = 1;
        for (int i = 1; i<= m - 1;i++){
            h *= d;
            h %= q;
        }
        int t = 0;
        for (int i = 1; i <= m;i++){
            t = (d * t + T[i]) % q;
        }
        for (int s = 0; s <= n - m;s++){
            int flag = 0;
            if(t==p){
                for (int j = 1; j <= m;j++){
                    if(P[j]!=T[s+j]){
                        flag = 1;
                        break;
                    }
                }
                if(flag==0)
                    cout << "valid shift rk=" << s<<endl;
            }
            if(s<n-m)
                t = (d * (t - h * T[s + 1]) + T[s + m + 1]) % q;
            if(t<0)
                t += q;
        }
    }

    void COMPUTE_PREFIX(){
        int k = 0;
        pi[1] = 0;
        for (int q = 2; q <= m;q++){
            while(k>0 && P[k+1]!=P[q])
                k = pi[k];
            if(P[k+1]==P[q])
                k++;
            pi[q] = k;
        }
    }

    void KMP(){
        COMPUTE_PREFIX();
        int q = 0;
        for (int i = 1; i <= n;i++){
            while(q>0 && P[q+1]!=T[i])
                q = pi[q];
            if(P[q+1]==T[i]){
                q++;
                if(q==m){
                    cout << "valid shift in kmp = " << i - m << endl;
                    q = pi[q];
                }
            }
        }
    }
};

int main(){
    SM sm;
    sm.getInput();
    // sm.RK_MATCHER();
    sm.KMP();
    return 0;
}