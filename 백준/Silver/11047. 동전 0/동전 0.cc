#include <iostream>

using namespace std;

int main() {
    int N, K;
    cin>>N>>K;
    
    int coinArr[N];
    
    for(int i=0;i<N;i++){
        cin>>coinArr[i];
    }
    
    int count=0;
    
    for(int i=N-1;i>=0;i--){
        if(coinArr[i]<=K){
            count+=K/coinArr[i];
            K-=(K/coinArr[i])*coinArr[i];
            
            if(K==0) break;
        }
    }
    cout<<count;
}