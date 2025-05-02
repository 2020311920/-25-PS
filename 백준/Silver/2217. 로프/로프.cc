#include <bits/stdc++.h>

using namespace std;

int n;
int rope[100001];

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n;
    for(int i=1;i<=n;i++){
        int weight;
        cin>>weight;
        rope[i] = weight;
    }

    sort(rope+1, rope+n+1);
    int max = rope[1]*n;
    for(int i=2;i<=n;i++){
        if(rope[i]*(n-i+1) > max) max = rope[i]*(n-i+1);
    }

    cout<<max;
}