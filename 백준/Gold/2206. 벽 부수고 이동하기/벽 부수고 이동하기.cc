//이거랑 비슷한 문제 몇몇 풀었죠. 최단경로라고 해서 BFS돌리면 될 것 같지만
//특수한 조건으로 인해서 단순히 pq를 통해 먼저 도착한게 뽑혔다고
//확신할 수 없어서
//큐를 모든 점에 대해서 늘리는 것이 아닌, 상태별로 DFS를 통해 진행.
//맞지?

//흠.. 이상하구만, 특수조건때문에 단순히 PQ와 BFS를 통해서 먼저 도착지에 도달했다고 해도 
//해당 경로가 최소인지 확신할 수 없기에 끝까지 돌려야 하므로 DFS와 다르지 않은 시간복잡도가 걸릴 것이라 생각했어. 그리고 기억은 안나지만 전에 비슷한 문제를 풀면서 DFS가 더 메모리적으로 이득이라고도 그랬구..
//근데 시간초과? 이건 뭐 어떻게 이득을 볼 수 있을까?

//내가 헷갈린 거는 좀 다른 느낌이었네
/*1987번 문제랑 헷갈림. 1987번은 동일한 알파벳을 밟지 않고, 가장 많은 지역을 밟으려 하는 거였어. 그래서 어디를 밟았는지에 따라 앞으로의 미래가 다 달라지므로, DFS로 모든 경우를 다 볼 필요가 있었던 거야.

반대로 이 문제는 출발점에서 목적지까지의 최단 거리를 구하는데, 일부 조건이 추가된 형태이지. 그래서 단순 좌표뿐만 아니라 그 조건에 따른 상태를 유지하면서 BFS 최단 거리를 진행하면 된다.*/

#include <bits/stdc++.h>
using namespace std;

int n,m;
int field[1001][1001];
int visited[1001][1001][2];

int dirX[4]={0,0,-1,1};
int dirY[4]={1,-1,0,0};

int ans = 2100000000;

struct state{
    int x;
    int y;
    int broke;
};

void solution(){
    //시작점은 1,1, 이동거리 1 벽 부순 경우 0;
    //헷갈리면 안될 것 같은게, 벽을 부숴봤는지에 대한 상태는 
    queue<state> q;
    q.push({1,1,0});
    visited[1][1][0]=1;

    while(!q.empty()){
        int sx = q.front().x; int sy = q.front().y; int broke = q.front().broke;
        q.pop();

        if(sx==n && sy==m){
            ans=visited[sx][sy][broke];
            break;
        }

        for(int i=0;i<4;i++){
            int nx = sx+dirX[i];
            int ny = sy+dirY[i];
            int nBroke = broke;

            if(nx>=1 && nx<=n && ny>=1 && ny<=m){
                if(field[nx][ny]==1){
                    //가려는 곳이 벽이다
                    if(nBroke==0){
                        //벽을 부수고 갈 수 있음
                        if(visited[nx][ny][1]==0){
                            //벽을 부숴본 상태로 진입해본적이 없는 칸이기에 가능
                            nBroke = 1;
                            visited[nx][ny][nBroke]=visited[sx][sy][broke]+1;
                            q.push({nx, ny, nBroke});
                        }
                    }
                }
                else{
                    //가려는 곳이 벽이 아니다 - nBroke 유지하면서 이동
                    //그럼 방문 이력이 있는지만 체크
                    if(visited[nx][ny][nBroke]==0){
                        visited[nx][ny][nBroke]=visited[sx][sy][broke]+1;
                        q.push({nx, ny, nBroke});
                    }
                }
            }
        }
    }

    if(ans == 2100000000) cout<<-1;
    else cout<<ans;
}

void input(){
    cin>>n>>m;

    for(int i=1;i<=n;i++){
        string str;
        cin>>str;
        for(int j=1;j<=m;j++){
            field[i][j] = str[j-1]-'0';
        }
    }
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    input();
    solution();
}