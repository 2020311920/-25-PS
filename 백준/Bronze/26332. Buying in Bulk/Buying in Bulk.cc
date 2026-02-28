#include <bits/stdc++.h>

using namespace std;

int n;
int a,b;

void solution(int a, int b){
    cout<<a<<" "<<b<<"\n";
    cout<<(a*b)-(2*(a-1))<<"\n";
}

void input(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a>>b;
        solution(a,b);
    }
}



int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    input();
    //solution();
}