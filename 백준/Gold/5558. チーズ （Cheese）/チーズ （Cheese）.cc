#include <bits/stdc++.h>

using namespace std;

int h,w,n;
int field[1001][1001];
struct factory{
    int x;
    int y;
};

factory factorys[10];//인덱스가 곧 만들어내는 경도라고 생각하면 되겠다 그죠.

int startX; int startY;

int ans=0;

void input(){
    cin>>h>>w>>n;

    for(int i=1;i<=h;i++){
        for(int j=1;j<=w;j++){
            char num;
            cin>>num;
            if(num=='S'){
                startX = i; startY = j;
            }
            else if(num=='X'){
                field[i][j]=1;
            }
            else if((num-'0')>=1 && (num-'0')<=9){
                factorys[num-'0'] = factory{i,j};
            }
        }
    }
}

int dirX[4]={0,1,0,-1};
int dirY[4]={1,0,-1,0};

int bfs(int sx, int sy, int gx, int gy){
    int visited[1001][1001];
    for(int i=1;i<=h;i++){
        for(int j=1;j<=w;j++){
            visited[i][j]=-1;
        }
    }
    queue<pair<int, int>> q;
    q.push({sx,sy});
    visited[sx][sy]=0;

    while(!q.empty()){
        int nowX = q.front().first; int nowY = q.front().second;
        q.pop();

        if(nowX==gx && nowY == gy){
            return visited[nowX][nowY];
        }

        for(int i=0;i<4;i++){
            int nextX = nowX+dirX[i];
            int nextY = nowY+dirY[i];

            if(nextX>=1 && nextX<=h && nextY>=1 && nextY<=w){
                if(field[nextX][nextY]!=1){
                    if(visited[nextX][nextY]==-1){
                        visited[nextX][nextY] = visited[nowX][nowY]+1;
                        q.push({nextX,nextY});
                    }
                }
            }
        }
    }

    return -1;
}

void solution(){
    for(int i=1;i<=n;i++){
        int goalX = factorys[i].x; int goalY = factorys[i].y;

        //start ~ goal 계산
        ans+=bfs(startX, startY, goalX, goalY);
        startX = goalX; startY = goalY;
    }

    cout<<ans;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    input();
    solution();
}