#include <bits/stdc++.h>

using namespace std;

struct Block{
    int walls[4]={0,0,0,0};//0이면 벽이 없는거야
};

Block block[51][51];
int m,n;

//인풋 받을 때 그 값을 비트 연산할 때 한번하면 서쪽, 두번쨰엔 북쪽, 세번쨰엔 동쪽, 네번째엔 남쪽
//이거에 맞게
int dirX[4]={0,-1,0,1};
int dirY[4]={-1,0,1,0};

void input(){
    cin>>m>>n;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            int num;
            cin>>num;

            for(int k=0;k<4;k++){
                //총 4번 비트를 확인하면서 보는거야 ㅇㅇ
                
                //그니까 1011랑 0001이랑 |연산 조지면 1or 0이 뜰거 아니야, 그니까 끝에 자리
                //한번하면 서쪽, 두번쨰엔 북쪽, 세번쨰엔 동쪽, 네번째엔 남쪽
                block[i][j].walls[k]=(num&1);
                //cout<<(num&1)<<" ";
                num = num>>1;
            }
        }
        //cout<<"\n";
    }    
}

int visited[51][51];

int bfs(int x, int y, int blockNum){
    queue<pair<int, int>> q;
    q.push({x,y});
    visited[x][y] = blockNum;
    int blockCnt=1;

    while(!q.empty()){
        int sx = q.front().first; int sy = q.front().second;
        q.pop();
        for(int i=0;i<4;i++){
            //i라는 방향을 택할 건데 거기에 현재위치에서 벽이 있는지 확인하자
            if(block[sx][sy].walls[i]==0){
                //이면 이 방향으로 가는데 적어도 벽은 없다는 소리
                int nx = sx+dirX[i];
                int ny = sy+dirY[i];
                if(nx>=1 && nx<=n && ny>=1 && ny<=m){
                    //해당 방향으로 가면 적어도 범위 안에는 있음
                    if(visited[nx][ny]==0){
                        //아직 방문한 적이 없는 곳
                        visited[nx][ny]=blockNum;
                        blockCnt++;
                        q.push({nx,ny});
                    }
                }
            }           
        }
    }

    return blockCnt;
}

void printVisited(){
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cout<<visited[i][j]<<" ";
        }
        cout<<"\n";
    }
}

void solution(){
    //visited배열에 숫자로 뭉탱이를 구분할 것임
    int blockNum=1;
    int maxBlockCnt = 0;
    int maxBlockNum;
    unordered_map<int, int> um;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(visited[i][j]==0){
                //i,j를 시작점으로 하여 구역 확인을 해도 된다! 라는 뜻
                int blockCnt = bfs(i,j,blockNum);
                //blockNum인 구역의 크기는 blockCnt이다. 이거 따로 저장해야함
                um[blockNum] = blockCnt;

                if(maxBlockCnt<blockCnt){
                    maxBlockCnt = blockCnt;
                    maxBlockNum = blockNum;//이렇게 가장 큰 블록 덩이 크기와 그 덩이 인덱스를 저장한다.
                }
                blockNum++;
            }
        }
    }

    //이렇게 하면 성에 있는 방의 개수 = blockNum, 가장 큰 덩이 사이즈 = maxBlockCnt
    //남은 건 벽을 제거하여 얻을 수 있는 가장 넓은 방의 크기인데.
    //살짝 생각해보니 조심해야 해. 왜냐, 가장 넓은 방이 아닌 다른 두 방을 열었을 때 그게 더 커질 수 있기 때문이다.
    //흠.. 이걸 어떻게 해결할 것인가.

    //모든 구역에 한해서 이 구역이 어디와 접하는가. 이를 모두 구할 수 있다면, 각각을 다 한번씩 접한다고 해서 구한 값의 최대를 구하면 되긴 하거덩

    //printVisited();
    //모든 visited를 다시 싸악 돌면서 벽과 상관없이 특정 영역으로 갔을 때 다른 수이다? 그럼 다른 영역과 접한다!
    //그때마다 그 두 구역의 사이즈를 더하고 그거의 최대를 구한다면 되겠다.
    //다만 이거는 시간복잡도가 맵이 작을 때나 가능하겠네. 만약 맵이 막 1억*1억이라면 어떻게 해야할지 좀 그렇다. 처음 bfs를 돌리면서 아싸리 접하는 것도 확인을 할 수 있으려냐?

    int wallCrashMaxCnt=0;

    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            //i,j에서 영역만 벗어나지 않게 탐색해서 다른 영역인지 체크
            for(int k=0;k<4;k++){
                int nx = i+dirX[k];
                int ny = j+dirY[k];
                if(nx>=1 && nx<=n && ny>=1 && ny<=m){
                    //범위 안이니까
                    if(visited[i][j]!=visited[nx][ny]){
                        //서로 다른 두 영역이 벽 하나로 접한다!
                        auto it = um.find(visited[i][j]); //저 블럭넘버의 사이즈를 um에 저장해두었다.
                        int size =0;
                        size+=it->second;
                        it = um.find(visited[nx][ny]);
                        size+=it->second;

                        wallCrashMaxCnt = max(wallCrashMaxCnt, size);
                    }
                }
            }
        }
    }

    cout<<blockNum-1<<"\n"<<maxBlockCnt<<"\n"<<wallCrashMaxCnt;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    input();
    solution();
}