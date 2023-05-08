#include<iostream>
#include<string>
#include<math.h>
using namespace std;

struct charnode{
    char c;
    int freq, codelen;
    string code;
    charnode *left, *right, *parent;
};

class PQ{
    int heapsize;
    charnode **Q;
    public:
    void MIN_HEAPIFY(int i){
        int smallest = i;
        int l = 2 * i + 1;
        int r = 2 * i + 2;
        if(l<=heapsize && Q[l]->freq<Q[smallest]->freq)
            smallest = l;
        if(r<=heapsize && Q[r]->freq<Q[smallest]->freq)
            smallest = r;
        if(smallest!=i){
            charnode *t = Q[i];
            Q[i] = Q[smallest];
            Q[smallest] = t;
            MIN_HEAPIFY(smallest);
        }
    }

    void CREATE_PQ(charnode *C[],int n){
        heapsize = n - 1;
        Q = new charnode*[n];
        for (int i = 0; i < n;i++){
            Q[i] = C[i];
        }
        for (int i = (heapsize - 1) / 2; i >= 0;i--)
            MIN_HEAPIFY(i);
    }

    void insert(charnode *z){
        heapsize++;
        Q[heapsize] = z;
        int i = heapsize;
        while(i>=0 && Q[(i-1)/2]->freq>Q[i]->freq){
            Q[i] = Q[(i - 1) / 2];
            i = (i - 1) / 2;
        }
        Q[i] = z;
    }

    charnode *EXTRACT_MIN(){
        charnode *t = Q[0];
        Q[0] = Q[heapsize];
        heapsize--;
        MIN_HEAPIFY(0);
        return t;
    }

};

class Huffman{
    int n;
    charnode **C;
    public:
    Huffman(char ch[],int f[],int len){
        n = len;
        C = new charnode *[len];
        for (int i = 0; i < n;i++){
            C[i] = new charnode;
            C[i]->c = ch[i];
            C[i]->freq = f[i];
            C[i]->code = "";
            C[i]->codelen = 0;
            C[i]->left = C[i]->right = C[i]->parent = NULL;
        }
    }

    charnode *BuildTree(){
        PQ q;
        q.CREATE_PQ(C, n);
        for (int i = 1; i <= n - 1;i++){
            charnode *z, *x, *y;
            z = new charnode;
            z->code = "";
            z->codelen = 0;
            z->parent = NULL;
            x = q.EXTRACT_MIN();
            y = q.EXTRACT_MIN();
            x->parent = y->parent = z;
            z->left = x;
            z->right = y;
            z->freq = x->freq + y->freq;
            q.insert(z);
        }
        return q.EXTRACT_MIN();
    }

    void findcode(charnode *z){
        if(z->codelen>0)
            return;
        if(z->parent==NULL){
            z->code = "";
            z->codelen = 0;
        }else{
            findcode(z->parent);
            z->codelen = z->parent->codelen + 1;
            if(z==z->parent->left)
                z->code = z->parent->code + "0";
            else
                z->code = z->parent->code + "1";
        }
    }

    void display(){
        cout << "\nchar\tfreq\tcode\tcodelen" << endl;
        for (int i = 0; i < n;i++){
            findcode(C[i]);
            cout << C[i]->c << '\t' << C[i]->freq << '\t' << C[i]->code << '\t' << C[i]->codelen << endl;
        }
    }

    int filesize(){
        int fs = 0;
        for (int i = 0; i < n;i++){
            // findcode(C[i]);
            fs += C[i]->codelen * C[i]->freq;
        }
        return fs;
    }
};

int main(){
    int n;
	char a[20];
	int f[20];
	cout << "Enter No. of characters: ";
	cin >> n;
	cout << "Enter the char & freq: "<< endl;
	for(int i=0;i<n;i++)
	   cin >> a[i] >> f[i];
	Huffman H(a,f,n);
	cout << endl;	
    charnode *root=H.BuildTree();
    H.display();
    int tot_freq=0;
    for (int i=0; i<n; i++)
    	tot_freq += f[i];
    int FL_FS = (int)(log2(n)+1) * tot_freq;
    int VL_FS = H.filesize();
    cout << "\nfixed size length=" << FL_FS<<endl;
    cout << "variable size length=" << VL_FS<<endl;
    cout << "compression ratio =" << (1 - (double)VL_FS / FL_FS) * 100;
    return 0;
}