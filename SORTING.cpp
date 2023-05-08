#include<iostream>
#include<fstream>
#include<limits.h>
#include<time.h>
#include<stdlib.h>
using namespace std;

class SORTING{
    int A[10010];
    int n,hs;
    public:
    void init(){
        ofstream fout("rand_input.txt");
        srand((long int)clock());
        for (int i = 0; i < 100;i++)
            fout << rand() % 30 << '\t';
        fout.close();
    }

    void getInput(int len){
        n = len;
        ifstream fin("rand_input.txt");
        for (int i = 1; i <= n;i++){
            fin >> A[i];
        }
        fin.close();
    }

    void display(){
        for (int i = 1; i <= n;i++)
            cout << A[i] << '\t';
    }

    void dispfile(){
        ofstream fout("sort_output.txt");
        for (int i = 1; i <= n;i++)
            fout << A[i] << '\t';
        fout.close();
    }

    void insertionSort(){
        for (int i = 2; i <= n;i++){
            int key = A[i];
            int j = i - 1;
            while(j>0 && A[j]>key){
                A[j + 1] = A[j];
                j--;
            }
            A[j + 1] = key;
        }
        cout << "\ninseriton sort-->" << endl;
        display();
        // dispfile();
    }

    void merge(int p,int q,int r){
        int n1 = q - p + 1;
        int n2 = r - q;
        int L[n1 + 2], R[n2 + 2];
        for (int i = 1; i <= n1;i++)
            L[i] = A[p + i - 1];
        for (int j = 1; j <= n2;j++)
            R[j] = A[q + j];
        L[n1 + 1] = INT_MAX;
        R[n2 + 1] = INT_MAX;
        int i = 1, j = 1;
        for (int k = p; k <= r;k++){
            if(L[i]<=R[j]){
                A[k] = L[i];
                i++;
            }else{
                A[k] = R[j];
                j++;
            }
        }
    }

    void mergesort(int p,int r){
        if(p<r){
            int q = (p + r) / 2;
            mergesort(p, q);
            mergesort(q + 1, r);
            merge(p, q, r);
        }
    }

    void callms(){
        cout << "\n-->mergesort" << endl;
        mergesort(1, n);
        display();
    }

    void maxheapify(int i){
        int largest, l, r;
        largest = i;
        l = 2 * i;
        r = 2 * i + 1;
        if(l<=hs && A[l]>A[largest])
            largest = l;
        if(r<=hs && A[r]>A[largest])
            largest = r;
        if(largest!=i){
            int t = A[i];
            A[i] = A[largest];
            A[largest] = t;
            maxheapify(largest);
        }
    }

    void buildmaxheap(){
        for (int i = (n / 2); i > 0;i--)
            maxheapify(i);
    }

    void heapsort(){
        hs = n;
        buildmaxheap();
        for (int i = n; i > 1;i--){
            int t = A[i];
            A[i] = A[1];
            A[1] = t;
            hs--;
            maxheapify(1);
        }
        cout << "\nheapsort-->" << endl;
        display();
    }

    int partition(int p,int r){
        int x = A[r];
        int i = p - 1;
        for (int j = p; j < r;j++){
            if(A[j]<x){
                int t = A[i + 1];
                A[i + 1] = A[j];
                A[j] = t;
                i++;
            }
        }
        A[r] = A[i + 1];
        A[i + 1] = x;
        return i + 1;
    }

    void QuickSort(int p,int r){
        if(p<r){
            int q = partition(p, r);
            QuickSort(p, q - 1);
            QuickSort(q + 1, r);
        }
    }

    void callQS(){
        QuickSort(1, n);
        cout << "\nquicksort--->" << endl;
        display();
    }
};

int main(){
    SORTING s1,s2,s3,s4;
    // s.init();
    int n;
    cout << "enter n:";
    cin >> n;
    s1.getInput(n);
    s2.getInput(n);
    s3.getInput(n);
    s4.getInput(n);
    s1.insertionSort();
    s2.callms();
    s3.heapsort();
    s4.callQS();
    return 0;
}