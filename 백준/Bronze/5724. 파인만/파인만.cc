#include <bits/stdc++.h>

using namespace std;

int n;

void solution(){
    int sum=0;
    while(n>=1){
        sum+=(n*n);
        n--;
    }

    cout<<sum<<"\n";
}

void input(){
    cin>>n;
    while(n!=0){
        solution();
        cin>>n;
    }
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    input();
}