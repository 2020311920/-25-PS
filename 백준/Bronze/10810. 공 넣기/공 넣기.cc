#include <bits/stdc++.h>

using namespace std;

int box[101];


int main(){
    int n,m;
    cin>>n>>m;

    for(int i=1;i<=m;i++){
        int s,e,k;

        cin>>s>>e>>k;

        for(int j=s;j<=e;j++){
            box[j]=k;
        }
    }       

    for(int i=1;i<=n;i++) cout<<box[i]<<" ";
}