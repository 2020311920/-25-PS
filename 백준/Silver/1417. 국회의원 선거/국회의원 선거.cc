#include <bits/stdc++.h>

using namespace std;

int candidate[51];

int main(){
    int n;
    cin>>n;

    int me;
    cin>>me;

    for(int i=1;i<=n-1;i++){
        int num;
        cin>>num;
        candidate[i] = num;
    }

    sort(candidate+1, candidate+n);
    int cnt=0;
    while(me<=candidate[n-1] && n-1>=1){
        me++;
        candidate[n-1]--;
        cnt++;
        sort(candidate+1, candidate+n);
    }

    cout<<cnt;

    
}