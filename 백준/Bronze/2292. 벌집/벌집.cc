#include <bits/stdc++.h>

using namespace std;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin>>n;

    int sum=1;
    int ans = 1;
    while(sum<n){
        ans++;
        sum += ((ans-1)*6);
    }

    cout<<ans;

}