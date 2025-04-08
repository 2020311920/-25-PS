#include <bits/stdc++.h>

using namespace std;

int main() {
    int N,M;
    
    cin>>N>>M;
    vector<int> v(M,1); //M개의 원소를 가진 벡터
    
    for(int i=0;i<pow(N,M);i++){
        for(int j=0;j<M;j++) cout<<v[j]<<" ";
        cout<<"\n";
        
        int ind = M-1;
        v[ind]++;
        
        for(int j=ind;j>=1;j--){
            if(v[j]>N){
                v[j]=1;
                v[j-1]++;
            }
        }
    }
    
}

