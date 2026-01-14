#include <bits/stdc++.h>

using namespace std;

int n;

int field[21][21];
int dist[21][21];
int visited[21][21];

int dirX[4]={1,-1, 0,0};
int dirY[4]={0,0,1, -1};

int sharkSize = 2; int sharkExp=0;
int sharkX; int sharkY;



//deque<pair<int, int>> fishes[7];//인덱스가 물고기 사이즈, 그 안에 물고기들의 좌표

bool possible(){
    //먹을 수 있는 물고기가 하나라도 남아있는가? 
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            //필드를 돌면서 먹을 수 있는 가장 가까운 놈
            // if(field[i][j]!=0 && field[i][j]<sharkSize){
            //     int tempDist = abs(i-sharkX)+abs(j-sharkY);
            //     if(tempDist<nearDist){
            //         nearX = i;
            //         nearY = j;
            //         nearDist = tempDist;
            //     }
            // }
            
            //나는 이때 바로 최소를 구하려고 했어
            /*왜? 먹으로 이동할 때 지나는 칸의 최소 개수라 했는데 그냥 절대 거리가 최소인거로 착각한거야. 직접 BFS하면서 먼저 도착한 "먹을 수 있는 물고기"로 생각해야하기에, 존재하는지만 체크해야 해.*/

            //즉 하나라도 먹을 수 있는 물고기가 있다면 그냥 즉시 return true;
            if(field[i][j]!=0 && field[i][j]<sharkSize) return true;
        }
        
    }
    return false;
}

int bfs(){
    //최단 거리로 물고기 잡아 먹으러 가야 해
    int startX = sharkX; int startY = sharkY;

    queue<pair<int, int>> q;
    deque<pair<int, int>> dq;
    q.push({startX, startY});
    visited[startX][startY] = 1;
    dist[startX][startY] = 0;
    int minDist = 41;
    while(!q.empty()){
        pair<int, int> x = q.front(); q.pop();

        if(field[x.first][x.second]!=0 && field[x.first][x.second]<sharkSize && field[x.first][x.second]<=6){
            //그럼 먹을 수 있는 놈에 처음 도달
            //헉!! 생각해보니 이때 바로 먹으면 안돼..
            //가능한 놈들을 후보지로 놓고 그 중에서 인덱스가 최소인 놈을 골라서 먹으러 가야함...

            //일단 지금 찾은 거리가 최단 경로인건 확실하니
            if(minDist == 41) minDist = dist[x.first][x.second];
            
            if(dist[x.first][x.second]==minDist) dq.push_back({x.first, x.second}); //mindist인 목적지를 후보지로 넣어
        }

        for(int dirInd = 0; dirInd<4;dirInd++){
            int nextX = x.first + dirX[dirInd];
            int nextY = x.second + dirY[dirInd];

            if(nextX<1 || nextX>n || nextY<1 || nextY > n) continue;
            if(visited[nextX][nextY]==1) continue;
            if(field[nextX][nextY]>sharkSize) continue;

            visited[nextX][nextY] = 1;
            dist[nextX][nextY] = dist[x.first][x.second]+1;
            q.push({nextX, nextY});
        }
    }

    if(dq.size()==0) return -1;
    else{
        sort(dq.begin(), dq.end());
    }
    //도착해서 즉시 먹음
    pair<int, int> x = dq.front();
    field[x.first][x.second]=0;
    field[sharkX][sharkY] = 0;
    sharkX = x.first;
    sharkY = x.second;
    field[sharkX][sharkY] = 9;
    sharkExp++;
    if(sharkExp == sharkSize){
        sharkExp=0;
        sharkSize++;
    }
    return minDist;
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(0);

    cin>>n;

    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            int num;
            cin>>num;
            field[i][j]=num;
            if(num == 9){
                sharkX = i;
                sharkY = j;
            }            
        }
    }

    //매 순간, 상어로부터 모든 물고기들의 거리를 체크하고
    //먹을 수 있는 가장 가까운 물고기중 하나를 택해서
    //거기로 이동

    int time = 0;
    while(possible()){
        //cout<<"먹을 수 있는 놈이 있습니다!!\n";
        //애초에 possible이 최소거리에 물고기가 있다고 한거니까, 걔로 가야 해
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                dist[i][j] = 0;
                visited[i][j] = 0;
            }
        }
        int result = bfs();

        if(result == -1){
            //먹을 놈이 있는데 못가는 거임
            break;
        }
        else{
            //cout<<"그놈을 먹으러 "<<result<<"만큼의 거리를 이동했습니다.\n";
            //result가 걸리는 시간
            time += result;
        }

        // cout<<"먹은 직후 현재 shark의 size : "<<sharkSize<<", 경험치 : "<<sharkExp<<"\n";
        // cout<<"현상태\n";
        // for(int i=1;i<=n;i++){
        //     for(int j=1;j<=n;j++){
        //         cout<<field[i][j]<<" ";
        //     }
        //     cout<<"\n";
        // }
    }

    cout<<time;
}