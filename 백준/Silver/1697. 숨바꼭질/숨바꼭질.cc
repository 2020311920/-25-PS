#include <bits/stdc++.h>

using namespace std;

int n,k;
int visited[100001];

void input(){
    cin>>n>>k;
}

void bfs(){
    priority_queue<pair<int, int>, vector<pair<int,int>>, greater<pair<int, int>>> q; //시간, 위치
    q.push({0,n});
    visited[n]=0;
    while(!q.empty()){
        int nowTime = q.top().first;
        int now = q.top().second; q.pop();
        //만약 먼저 나왔다면 무조건 그게 답일까..
        //더 이득인 경우가 없을까
        //cout<<nowTime<<"에 "<<now<<"위치\n";

        if(visited[now]<nowTime) continue; //만료된 후보니까 패스

        if(now==k) break;
        
        int next;
        next = now+1;
        if(next>=0 && next<=100000){
            if(visited[next]>nowTime+1){
                visited[next] = nowTime+1;
                //cout<<nowTime+1<<"에 "<<next<<"로 가는거 push\n";
                q.push({nowTime+1, next});
            }
        }

        next = now-1;
        if(next>=0 && next<=100000){
            if(visited[next]>nowTime+1){
                visited[next] = nowTime+1;
                //cout<<nowTime+1<<"에 "<<next<<"로 가는거 push\n";
                q.push({nowTime+1, next});
            }
        }

        next = now*2;
        if(next>=0 && next<=100000){
            if(visited[next]>nowTime+1){
                visited[next] = nowTime+1;
                //cout<<nowTime+1<<"에 "<<next<<"로 가는거 push\n";
                q.push({nowTime+1, next});
            }
        }
    }

    cout<<visited[k];
}

void solution(){
    for(int i=0;i<=100000;i++) visited[i]=100001;
    bfs();
}

int main(){
    // ios::sync_with_stdio(0);
    // cin.tie(0);

    input();
    solution();
}