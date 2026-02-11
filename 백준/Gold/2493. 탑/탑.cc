#include <bits/stdc++.h>

using namespace std;
int n;
struct tower{
    int ind;
    int height;
};
vector<tower> towers;
void input(){
    cin>>n;
    for(int i=1;i<=n;i++){
        int h;
        cin>>h;
        towers.push_back(tower{i,h});
    }
}

void solution(){
    stack<tower> s;
    for(auto i : towers){
        //지금의 나를 기준으로 s의 top을 바라보며 자기보다 큰놈을 만날때까지 pop한다
        while(!s.empty() && s.top().height<i.height){
            s.pop();
        }

        if(s.empty()){
            cout<<0<<" ";
            s.push({i.ind, i.height});
        }
        else{
            cout<<s.top().ind<<" ";
            s.push({i.ind, i.height});
        }
    }    
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    input();
    solution();
}