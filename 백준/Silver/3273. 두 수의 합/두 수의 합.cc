#include <bits/stdc++.h>

using namespace std;

int n;
vector<int> v;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>n;

    for(int i=1;i<=n;i++){
        int num;
        cin>>num;

        v.push_back(num);
    }

    sort(v.begin(), v.end());

    int sum;
    cin>>sum;
    int ans=0;
    int left = 0; int right=n-1;

    while(left<right){
        if(v[left]+v[right]>sum) right--;
        else if(v[left]+v[right]<sum) left++;
        else{
            ans++;
            left++;
        }
    }

    cout<<ans;
}