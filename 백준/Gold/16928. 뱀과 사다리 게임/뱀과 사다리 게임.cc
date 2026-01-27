#include <bits/stdc++.h>

using namespace std;

void input();
void solution();

int main(){
    // ios::sync_with_stdio(0);
    // cin.tie(0);

    input();
    solution();
}

int field[101];
int n,m;
void input(){
    cin>>n>>m;

    for(int i=1;i<=n;i++){
        int x,y;
        cin>>x>>y;
        field[x] = y;
    }

    for(int j=1;j<=m;j++){
        int u,v;
        cin>>u>>v;
        field[u]=v;
    }
}

int visited[101];

void bfs(int n){
    deque<int> dq;
    dq.push_back(n);
    visited[n]=0;

    while(!dq.empty()){
        int s = dq.front(); dq.pop_front();
        if(s == 100) break;
        int a = s;
        //주사위 안굴려도 되는 거 먼저 삽입
        while(field[a]!=0){
            //a에 사다리든, 뱀이 있어서, field[a]로 이동
            //무조건 이동이 된다.
            if(visited[field[a]]==-1 || visited[field[a]]>visited[a]){
                visited[field[a]] = visited[a];
                // cout<<a<<"에서 "<<field[a]<<"로 점프가 가능해서! ";
                // cout<<field[a]<<"칸의 주사위 횟수가 "<<visited[a]<<"로 갱신!\n";
                dq.push_front(field[a]);
            }
            a = field[a];
        }

        //어찌되었던, 저 while문을 한번이라도 돌았다면, 주사위는 굴릴 수 없어
        if(field[s]!=0) continue;

        for(int i=6;i>=1;i--){
            int ns = s+i;
            if(ns>=1 && ns<=100){
                if(visited[ns]==-1 || visited[ns]>visited[s]+1){
                    visited[ns] = visited[s]+1;
                    // cout<<s<<"에서 주사위를 굴려 "<<ns<<"로 도착가능해서! ";
                    // cout<<ns<<"칸의 주사위 횟수가 "<<visited[s]+1<<"로 갱신!\n";
                    dq.push_back(ns);
                }
            }
        }
    }
    cout<<visited[100];
}

void initialize(){
    for(int i=1;i<=100;i++){
        visited[i] = -1;
    }
}

void solution(){
    initialize();
    bfs(1);
}