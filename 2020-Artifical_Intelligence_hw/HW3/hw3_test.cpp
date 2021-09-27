#include <iostream>
#include <queue>
#include <math.h>
#include <algorithm>
#include <vector>
#include <stack>
using namespace std;

void print(int *v,int h,int w){
    for(int i=0;i<h;i++){
        for(int j=0;j<w;j++){
            cout << *(v+i*w+j)<< " ";
            *(v+i*w+j) = 1;
        }
        cout << endl;
    }
}
int main(){
    int n;
    cin >> n;
    int v[3][3];
    print((int *)v,3,3);
    //abs(a,n);
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            cout << v[i][j]<< " ";
        }
        cout << endl;
    }
}
