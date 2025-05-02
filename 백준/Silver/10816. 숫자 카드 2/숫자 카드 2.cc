#include <bits/stdc++.h>

using namespace std;

int n;
int arr[20000001];

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n;
    for(int i=1;i<=n;i++){
        int num;
        cin>>num;
        num+=10000000;
        arr[num]++;
    }

    cin>>n;

    for(int i=1;i<=n;i++){
        int num;
        cin>>num;
        num+=10000000;
        cout<<arr[num]<<" ";
    }
}