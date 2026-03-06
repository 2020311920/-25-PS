#include <bits/stdc++.h>

using namespace std;

int n;
vector<string> v;

void input(){
    cin>>n;
    for(int i=1;i<=n;i++){
        string str;
        cin>>str;

        v.push_back(str);
    }
}

void solution(){
    string ans = v[0];
    int length = ans.size();
    for(int i=1;i<n;i++){
        string temp = v[i];
        for(int j=0;j<length;j++){
            if(ans[j]==temp[j]){}
            else{
                ans[j]='?';
            }
        }
    }

    cout<<ans;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    input();
    solution();
}