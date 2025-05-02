#include <bits/stdc++.h>

using namespace std;

vector<int> v;

int main(){
    int n;
    cin>>n;

    for(int i=1;i<=n;i++){
        int num;
        cin>>num;
        v.push_back(num);
    }

    sort(v.begin(), v.end());

    for(auto i:v) cout<<i<<" ";
}