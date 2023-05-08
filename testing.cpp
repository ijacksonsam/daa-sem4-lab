#include <iostream>

using namespace std;

class sorting{
    int A[100];
    int n;
    public:
    void getInput(){
        cout<<"n:";cin>>n;
        cout<<"num:";
        for(int i=1;i<=n;i++)
            cin>>A[i];
    }
    
    void display(){
        for (int i = 1; i <= n;i++)
            cout << A[i] << '\t';
    }
    
    void maxheapify(int i){
        int largest, l, r;
        largest = i;
        l = 2 * i;
        r = 2 * i + 1;
        int hs = n;

        if(l<=n && A[l]>A[i])
            largest = l;
        if(r<=n && A[r]>A[largest])
            largest = r;
        if(largest!=i){
            int t = A[i];
            A[i] = A[largest];
            A[largest] = t;
            maxheapify(largest);
        }
    }

    void buildmaxheap(){
        for (int i = (n/2 ); i > 0;i--)
            maxheapify(i);
    }
    
    void heapsort(){
        int hs = n;
        buildmaxheap();
        for (int i = n; i > 1;i--){
            int temp = A[1];
            A[1] = A[i];
            A[i] = temp;
            hs--;
            maxheapify(1);
        }
        cout << "\nheapsort-->" << endl;
        display();
    }
    
};

int main()
{
    sorting s;
    s.getInput();
    s.heapsort();

    return 0;
}
