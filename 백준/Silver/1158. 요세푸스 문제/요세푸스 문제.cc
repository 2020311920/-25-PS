#include <bits/stdc++.h>

using namespace std;

int n, k;

queue<int> q;
vector<int> ans;

int main(){
    cin>>n>>k;

    for(int i=1;i<=n;i++) q.push(i);

    while(!q.empty()){
        int cnt = 0;
        while(cnt!=k-1){
            cnt++;
            int num = q.front();
            q.pop();
            q.push(num);
        }
        int num = q.front();
        ans.push_back(num);
        q.pop();
    }
    cout<<"<";
    for(int i=0;i<ans.size()-1;i++) cout<<ans[i]<<", ";
    cout<<ans[ans.size()-1]<<">";
}