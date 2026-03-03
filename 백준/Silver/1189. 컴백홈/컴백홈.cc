#include <bits/stdc++.h>

using namespace std;

int r,c,k;
int field[6][6];

void input(){
    cin>>r>>c>>k;
    for(int i=1;i<=r;i++){
        for(int j=1;j<=c;j++){
            char ch;
            cin>>ch;

            if(ch=='.') field[i][j]=0;
            if(ch=='T') field[i][j]=1;
        }
    }
}

int ansCnt=0;
int dirX[4]={0,1,0,-1};
int dirY[4]={1,0,-1,0};
int visited[6][6];

void dfs(int x, int y, int dist){
    if(dist == k){
        if(x==1 && y==c) ansCnt++;
        return;
    }

    for(int i=0;i<4;i++){
        int nx = x+dirX[i];
        int ny = y+dirY[i];

        if(nx>=1&&nx<=r && ny>=1 && ny<=c){
            if(field[nx][ny]==0){
                if(visited[nx][ny]==0){
                    visited[nx][ny]=1;
                    dfs(nx, ny, dist+1);
                    visited[nx][ny]=0;
                }
            }
            
        }
    }
}

void solution(){
    visited[r][1]=1;
    dfs(r,1,1);

    cout<<ansCnt;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    input();
    solution();
}