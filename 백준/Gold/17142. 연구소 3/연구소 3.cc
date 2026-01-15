#include <bits/stdc++.h>

using namespace std;

int n,m;
int field[51][51];

int zeroCnt=0;
int ans = 1000000000;

int dirX[4] = {-1,0,1,0};
int dirY[4] = {0,-1,0,1};

deque<pair<int, int>> viruses;
int visitedVirus[11];

void input(){
    cin>>n>>m;

    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cin>>field[i][j];
            if(field[i][j] ==2) viruses.push_back({i,j});
            if(field[i][j]==0) zeroCnt++;
        }
    }
}

int spread(){
    int visited[51][51];
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            visited[i][j]=-1;
        }
    }
    queue<pair<int, int>> q;
    for(int i=1;i<=viruses.size();i++){
        if(visitedVirus[i]==1){
            q.push({viruses[i-1].first, viruses[i-1].second});
            visited[viruses[i-1].first][viruses[i-1].second] = 0;
        }
    }

    //이렇게 출발점들을 모두 q에 넣음

    
    int tempZeroCnt=0;
    int totalTime=0;
    while(!q.empty() && tempZeroCnt<zeroCnt){
        pair<int, int> start = q.front(); q.pop();

        int sx = start.first; int sy = start.second;
        int nextX; int nextY;
        for(int i=0;i<=3;i++){
            nextX = sx+ dirX[i];
            nextY = sy+ dirY[i];

            if(nextX>=1 && nextX<=n && nextY>=1 && nextY<=n){
                //범위 안이어야 하고
                if(field[nextX][nextY]!=1){
                    //이동하는게 벽이 아니어야 하고
                    if(visited[nextX][nextY]==-1){
                        //이미 들른적이 있는 곳이 아니어야 하고

                        //그럼 원래라면 맘편히 이동하면 되겠다.
                        //근데 모두 커버가 되는 조건은 0을 지울때임
                        if(field[nextX][nextY]==0) tempZeroCnt++;

                        visited[nextX][nextY] = visited[sx][sy]+1;
                        //cout<<visited[nextX][nextY]<<"\n";
                        if(tempZeroCnt==zeroCnt){
                            //cout<<"all clear\n";
                            totalTime = visited[nextX][nextY];
                            break;
                        }

                        q.push({nextX,nextY});
                    }
                }
            }
        }
    }

    if(tempZeroCnt == zeroCnt) return totalTime;
    else return -1;
}

void choose(int k, int l){
    //m개의 활성화를 고르는 과정
    if(k==m){
        //선택된 m개의 위치들이 전부 시작점이 되어야 한다.
        int result = spread();
        if(result != -1 && result<ans) ans = result; 
        return ;
    }
    int length = viruses.size();
    for(int i=l;i<=length;i++){
        if(visitedVirus[i]==0){
            //해당 바이러스는 선택하지 않음.
            visitedVirus[i]=1;
            choose(k+1, i);
            visitedVirus[i]=0;
        }

    }
}

void solution(){
    //순간 드는 생각이, 활성화를 고르는 DFS, 거기서 시작되는 BFS

    choose(0,1);
}

int main(){
    // cin.tie(0);
    // ios::sync_with_stdio(0);

    input();
    solution();

    if(ans==1000000000) cout<<-1;
    else cout << ans;
}