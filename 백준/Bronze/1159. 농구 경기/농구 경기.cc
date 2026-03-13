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

int character[26];

void solution(){
    for(auto name : v){
        character[name[0]-'a']++;
    }

    int cnt=0;
    for(int i=0;i<26;i++){
        if(character[i]>=5){
            cnt++;
            cout<<char(i+'a');
        }
    }
    if(cnt==0) cout<<"PREDAJA";
    
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    input();
    solution();
}