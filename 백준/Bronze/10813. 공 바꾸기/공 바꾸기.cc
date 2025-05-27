#include <bits/stdc++.h>

using namespace std;

int box[101];

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    int a,b;

    cin>>a>>b;

    for(int i=1;i<=a;i++) box[i] = i;

    for(int i=1;i<=b;i++){
        int c,d;
        cin>>c>>d;

        swap(box[c], box[d]);

    }

    for(int i=1;i<=a;i++) cout<<box[i]<<" ";
}