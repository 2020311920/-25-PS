#include <bits/stdc++.h>

using namespace std;

int n;
//vector<pair<int, int>> iceCream;
int field[1001][1001];

int visited[1001][1001];

void input(){
    cin>>n;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            char ch;
            cin>>ch;
            if(ch=='#'){
                field[i][j]=1;
                //iceCream.push_back({i,j});
            }
            if(ch=='.') field[i][j]=2;
        }
    }
}

int dirX[4]={0,1,0,-1};
int dirY[4]={1,0,-1,0};

pair<int,int> bfs(int startX, int startY, int blockInd){
    int borderLine = 0;
    queue<pair<int,int>> q;
    q.push({startX, startY});
    int cnt=1;

    while(!q.empty()){
        int sx = q.front().first; int sy = q.front().second;
        q.pop();
        //이 점을 바탕으로 확인하는거야 둘레 계산을.
        //4방향의 주위가 각각 .이거나 바깥이면 둘레로 처리, 아니면 접한거라 무시
        for(int i=0;i<4;i++){
            int nx = sx+dirX[i];
            int ny = sy+dirY[i];

            if(nx>=1 && nx<=n && ny>=1 && ny<=n){
                if(field[nx][ny]==1){
                    if(visited[nx][ny]==0){
                        visited[nx][ny]=blockInd; cnt++;
                        q.push({nx,ny});
                    }
                }
                else{
                    borderLine++;
                }
            }
            else{
                borderLine++;
            }
        }
    }

    return {borderLine, cnt};
}

//priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> ansBlock; //{둘레, 인덱스}

void solution(){
    //iceCream의 모든 좌표들을 시작점으로 해서 덩어리를 구하는거지 ㅇㅇ
    //int iceCreamNum = iceCream.size();
    int blockInd=1;
    int maxBlockSize = 0;
    int minBorderLine = 2100000000;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(visited[i][j]==0 && field[i][j]==1){
                //아직 안 들른 곳이어야 덩어리의 첫 좌표로서 시작 가능인거임
                visited[i][j]=blockInd;
                auto blockInfo = bfs(i,j, blockInd);
                if(maxBlockSize<blockInfo.second){
                    //최신화
                    //while(!ansBlock.empty()) ansBlock.pop();
                    maxBlockSize = blockInfo.second;
                    minBorderLine = blockInfo.first;
                }
                else if(maxBlockSize == blockInfo.second){
                    minBorderLine = min(minBorderLine, blockInfo.first);
                }
                blockInd++;
            }
        }
    }
    //visited에 blockInd가 여러개로 막 표시가 됐을 것이야

    //sort(ansBlock.begin(), ansBlock.end());
    cout<<maxBlockSize<<" "<<minBorderLine;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    input();
    solution();
}