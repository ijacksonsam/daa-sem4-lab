#include<iostream>
#include<fstream>
#include<limits.h>
#include<time.h>
#include<stdlib.h>
using namespace std;

struct res{
    int low, high, sum;
};

class MS{
    int A[10010], n;
    public:

    void init(){
        srand((long int)clock());
        ofstream fout("ms_input.txt");
        for (int i = 0; i < 10010;i++){
            int num = rand() % 30;
            if(rand()%2==0)
                fout << -1 * num<<"\t";
            else
                fout << num<<"\t";
        }
        fout.close();
    }

    void getInput(int len){
        ifstream fin("ms_input.txt");
        n = len;
        for (int i = 1; i <= n;i++)
            fin >> A[i];
        fin.close();
    }

    res bf(){
        res r;
        r.sum = INT_MIN;
        for (int i = 1; i <= n;i++){
            int sum = 0;
            for (int j = i; j <= n;j++){
                sum += A[j];
                if(sum>r.sum){
                    r.sum = sum;
                    r.low = i;
                    r.high = j;
                }
            }
        }
        cout << "\nbf method--> sum =" << r.sum << " ; low and high (" << r.low << "," << r.high << ")" << endl;
    }

    res findMaxCross(int l,int m,int h){
        int lsum, rsum, sum;
        lsum = rsum = INT_MIN;
        sum = 0;
        res r;
        for (int i = m; i >= l;i--){
            sum += A[i];
            if(sum>lsum){
                r.low = i;
                lsum = sum;
            }
        }
        sum = 0;
        for (int i = m + 1; i <= h;i++){
            sum += A[i];
            if(sum>rsum){
                r.high = i;
                rsum = sum;
            }
        }
        r.sum = lsum + rsum;
        return r;
    }

    res findMaxSubarray(int l,int h){
        res left, right, cross;
        if(l==h){
            res r;
            r.low = l;
            r.high = l;
            r.sum = A[l];
            return r;
        }
        int m = (l + h) / 2;
        left = findMaxSubarray(l, m);
        right = findMaxSubarray(m + 1, h);
        cross = findMaxCross(l, m, h);
        if(left.sum>=right.sum && left.sum>=cross.sum)
            return left;
        else if(right.sum>=left.sum && right.sum>=cross.sum)
            return right;
        else
            return cross;
    }

    void callMS(){
        res r=findMaxSubarray(1, n);
        cout << "\nrec ms method--> sum =" << r.sum << " ; low and high (" << r.low << "," << r.high << ")" << endl;
    }
};

int main(){
    MS ms1,ms2;
    int n;
    // ms1.init();
    cout << "enter n:";
    cin >> n;
    ms1.getInput(n);
    ms2.getInput(n);
    ms1.bf();
    ms2.callMS();
    return 0;
}