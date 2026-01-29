#include <bits/stdc++.h>

using namespace std;

int n,m;
//출발점에 따라 도착지와 그 경로값를 저장하는 구조
vector<pair<int, int>> field[50001];
int visited[50001];

void input(){
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        int s,e,v;
        cin>>s>>e>>v;
        field[s].push_back({v,e});
        field[e].push_back({v,s});
    }
}

void init(){
    for(int i=1;i<=n;i++) visited[i]=987654321;
}

void bfs(){
    //시작점 1.
    visited[1]=0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>> > pq;//항상 값이 앞에 오게 해서 최소 경로값이 top으로 오게
    pq.push({0,1});
    while(!pq.empty()){
        pair<int, int> start = pq.top(); pq.pop();
        //start.second가 출발점, start.first가 그동안의 최소 경로값
        if(start.second == n) break;
        if(start.first != visited[start.second]) continue;
        for(auto i : field[start.second]){
            //i.first = start.second에서 i.second로 가는 경로값
            if(visited[i.second]>start.first+i.first){
                visited[i.second] = start.first + i.first;
                pq.push({visited[i.second], i.second});
            }
        }
    }

    cout<<visited[n];
}

void solution(){
    init();
    bfs();
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    input();
    solution();
}