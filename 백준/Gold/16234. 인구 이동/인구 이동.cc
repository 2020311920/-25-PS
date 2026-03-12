#include <bits/stdc++.h>

using namespace std;

int n; int l,r;
int field[51][51];

void input(){
    cin>>n>>l>>r;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cin>>field[i][j];
        }
    }
}

int visited[51][51];

int dirX[4]={0,1,0,-1};
int dirY[4]={1,0,-1,0};

bool bfs(){
    bool returnV=false;
    //시작점을 탐색하고, 그 시작점부터 bfs돌려
    int sectorN = 0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(visited[i][j]==0){
                //i,j가 시작점이 돼
                int sectorSize = 1;
                int sectorSum = field[i][j];
                sectorN++;
                //sectorN번째 구역 탐색 시작
                visited[i][j]=sectorN;
                vector<pair<int, int>> v;
                v.push_back({i,j});
                queue<pair<int, int>> q;
                q.push({i,j});

                while(!q.empty()){
                    int sx = q.front().first; int sy = q.front().second;
                    q.pop();
                    
                    for(int k=0;k<4;k++){
                        int nx = sx+dirX[k];
                        int ny = sy+dirY[k];

                        if(nx>=1 && nx<=n && ny>=1 && ny<=n){
                            if(visited[nx][ny]==0){
                                if(abs(field[sx][sy]-field[nx][ny])>=l && abs(field[sx][sy]-field[nx][ny])<=r){
                                    //이럼 국경선이 열린다, bfs로 접근이 가능하다
                                    visited[nx][ny]=sectorN;
                                    v.push_back({nx,ny});
                                    q.push({nx, ny});
                                    sectorSize++;
                                    sectorSum+=field[nx][ny];
                                }
                            }
                        }
                    }
                }

                if(sectorSize>1){
                    returnV = true;
                    //국경 열린게 있다는거라서
                    int average = sectorSum/sectorSize;
                    for(auto x : v){
                        field[x.first][x.second] = average;
                    }
                }

            }
        }
    }

    return returnV;
}

void solution(){
    int days=0;
    while(1){
        memset(visited, 0, sizeof(visited));
        bool returnV = bfs(); //구역들 열심히 나누면서 알아서 바로바로 업데이트하도록 하자
        if(!returnV) break;
        days++;
    }
    cout<<days;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    input();
    solution();
}