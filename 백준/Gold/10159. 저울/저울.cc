#include <bits/stdc++.h>

using namespace std;

int n,m;
struct thing{
    vector<int> lighter;
    vector<int> heavier;
};

thing things[101];

void input(){
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int a,b;
        cin>>a>>b;
        things[a].lighter.push_back(b);
        things[b].heavier.push_back(a);
    }
}

void solution(){
    //1번부터 n번까지
    //각각 lighter로 연결되는 visit들 체크
    for(int i=1;i<=n;i++){
        int visited[101];
        for(int j=1;j<=n;j++){
            visited[j]=0;
        }

        int cnt=1;
        //lighter 타고 들어가
        queue<int> lq;
        for(auto j : things[i].lighter){
            if(visited[j]==0){
                cnt++;
                visited[j]=1;
                lq.push(j);
            }
        }

        while(!lq.empty()){
            int now = lq.front(); lq.pop();
            for(auto j : things[now].lighter){
                if(visited[j]==0){
                    cnt++;
                    visited[j]=1;
                    lq.push(j);
                }
            }
        }

        //이제 heavier를 타고 들어가
        for(auto j : things[i].heavier){
            if(visited[j]==0){
                cnt++;
                visited[j]=1;
                lq.push(j);
            }
        }

        while(!lq.empty()){
            int now = lq.front(); lq.pop();
            for(auto j : things[now].heavier){
                if(visited[j]==0){
                    cnt++;
                    visited[j]=1;
                    lq.push(j);
                }
            }
        }

        cout<<n-cnt<<"\n";
    }
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    input();
    solution();
}