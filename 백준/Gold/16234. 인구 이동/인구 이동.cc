#include <bits/stdc++.h>

using namespace std;

int n, l, r;
int field[51][51];
int dirX[4]={0,1,0,-1};
int dirY[4]={1,0,-1,0};
bool trigger;
void input(){
    cin>>n>>l>>r;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cin>>field[i][j];
        }
    }
}

void bfs(){
    trigger = false;//초기화
    int visited[51][51];
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            visited[i][j]=0;
        }
    }

    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(visited[i][j]==0){
                queue<pair<int, int>> q;
                vector<pair<int, int>> v;
                q.push({i,j});
                visited[i][j]=1;
                v.push_back({i,j});
                int tempSum=field[i][j];
                while(!q.empty()){
                    auto start = q.front(); q.pop();

                    int sx = start.first; int sy = start.second;
                    for(int k=0;k<=3;k++){
                        int nx = sx+dirX[k];
                        int ny = sy+dirY[k];
                        if(nx>=1 && nx<=n && ny>=1 && ny<=n){
                            if(visited[nx][ny]==0){
                                if(abs(field[nx][ny]-field[sx][sy])>=l && abs(field[nx][ny]-field[sx][sy])<=r){
                                    //범위 안이고, 방문 안했고, 연합조건도 맞으니
                                    visited[nx][ny]=1;
                                    tempSum+=field[nx][ny];
                                    q.push({nx,ny});
                                    v.push_back({nx,ny});
                                }   
                            }
                        }
                    }
                }
                //구역확장 완료
                int sectorSize = v.size();
                //구역의 크기가 2이상이면 인구이동이 일어남
                //한번이라도 일어나면 하루는 지난다.
                if(sectorSize>=2) trigger = true;
                tempSum /= sectorSize;

                for(auto coord:v){
                    field[coord.first][coord.second] = tempSum;
                }
            }
        }
    }
}

void solution(){
    int days=0;
    while(1){
        bfs();
        if(trigger){
            days++;
        }
        else break;
    }

    cout<<days;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    input();
    solution();
}