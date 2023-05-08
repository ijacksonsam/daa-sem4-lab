#include<iostream>
#include<fstream>
using namespace std;

class CountSort{
    int A[100], B[100];
    int n, k;
    public:
    void getinput(){
        cout << "n:";
        cin >> n;
        cout << "k:";
        cin >> k;
        cout << "num:";
        for (int i = 1; i <= n;i++)
            cin >> A[i];
    }
    void countsort(){
        int C[k] = {0};
        for (int j = 1; j <= n;j++)
            C[A[j]]++;
        for (int i = 1; i < k;i++){
            C[i ] += C[i-1];
        }
        for (int i = n; i >= 1;i--){
            B[C[A[i]]] = A[i];
            C[A[i]]--;
        }
        display();
    }
    void display(){
        cout << "\no/p" << endl;
        for (int i = 1; i <= n;i++)
            cout << B[i]<<'\t';
    }
};

class RadixSort{
    int A[100], B[100];
    int n;
    public:
    void getinput(){
        cout << "n:";
        cin >> n;
        cout << "num:";
        for (int i = 1; i <= n;i++)
            cin >> A[i];
    }
    void display(){
        cout << "\no/p" << endl;
        for (int i = 1; i <= n;i++)
            cout << B[i]<<'\t';
    }
    void countsort(int exp){
        int C[10] = {0};
        for (int j = 1; j <= n;j++)
            C[(A[j] / exp) % 10]++;
        for (int i = 1; i < 10;i++)
            C[i] += C[i - 1];
        for (int j = n; j >= 1;j--){
            B[C[(A[j]/exp)%10]]=A[j];
            C[(A[j] / exp) % 10]--;
        }
        for (int i = 1;i<=n;i++){
            A[i] = B[i];
        }
    }

    int maxvalue(){
        int m = A[1];
        for (int i = 1;i<=n;i++){
            if(A[i]>m){
                m = A[i];
            }
        }
        return m;
    }

    void radixsort(){
        int m=maxvalue();
        for (int i = 1; m / i > 0;i*=10){
            countsort(i);
        }
        display();
    }
};

struct node{
    float data;
    node *next;
};
struct hnode{
    int count;
    node *first;
};

class BucketSort;

class HashTable{
    hnode ht[10010];
    int n;
    friend class BucketSort;

    public:
    HashTable(int len){
        n = len;
        for (int i = 0; i < n;i++){
            ht[i].count = 0;
            ht[i].first = NULL;
        }
    }
    void insert(int h,float d){
        node *t = new node;
        t->data = d;
        node *ploc = ht[h].first;
        node *ppre = NULL;
        while(ploc!=NULL && ploc->data<d){
            ppre = ploc;
            ploc = ploc->next;
        }
        if(ppre==NULL){
            t->next = ht[h].first;
            ht[h].first = t;
        }else{
            t->next = ppre->next;
            ppre->next = t;
        }
    }
};

class BucketSort{
    float A[10010];
    int n;
    public:
    void getInput(){
        cout << "enter n:";
        cin >> n;
        ifstream fin("uni_rand.txt");
        for (int i = 1; i <= n;i++){
            fin >> A[i];
        }
        fin.close();
    }

    void bucketsort(){
        cout << "\nbefore sort-->" << endl;
        for (int i = 1; i <= n;i++){
            cout << A[i] << "\t";
        }
        HashTable H(n);
        for (int i = 1; i <= n;i++){
            int hi = A[i] * n;
            H.insert(hi, A[i]);
        }
        int j = 1;
        for (int i = 0; i < n;i++){
            node *t = H.ht[i].first;
            while(t!=NULL){
                A[j] = t->data;
                j++;
                t = t->next;
            }
        }
        cout << "\nafter sort-->" << endl;
        for (int i = 1; i <= n;i++){
            cout << A[i] << "\t";
        }
    }
};

int main(){
    // CountSort cs;
    // cs.getinput();
    // cs.countsort();
    // RadixSort rs;
    // rs.getinput();
    // rs.radixsort();

    BucketSort bs;
    bs.getInput();
    bs.bucketsort();
    return 0;
}