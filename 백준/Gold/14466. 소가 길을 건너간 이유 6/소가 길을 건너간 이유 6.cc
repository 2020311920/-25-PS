//x번 소가 나머지 소들을 만나러 갈 때, "길을 건너지 않고는 만날 수 없는 쌍을 구하면 돼"

#include <bits/stdc++.h>

using namespace std;

int n,k;
int dirX[4] = {0,0,-1,1};
int dirY[4] = {1,-1,0,0};//0번 오른, 1번 왼, 2번 위, 3번 아래

struct Block{
    bool walls[4]={0,0,0,0};//몇 번 방향에 "길"이 있다
};
Block blocks[101][101];

vector<pair<int ,int>> cows;

void input(){
    cin>>n>>k;
    int r;
    cin>>r;
    for(int i=1;i<=r;i++){
        int r,c,rr,cc;
        cin>>r>>c>>rr>>cc;
        //r,c - rr,cc에 길이 있다라는 뜻
        int xDir = rr-r;
        int yDir = cc-c;
        //이게 r,c 기준으로 몇번 방향에 길이 있는지를 구해서 넣어주면 된다...
        //양방향으로
        //이걸 어떻게 하면 쉽게 구할 수 있지
        //일단 억지로라도 해보자
        if(xDir==0){
            if(yDir==1){
                //오른쪽인거야.
                blocks[r][c].walls[0]=1;
                blocks[rr][cc].walls[1]=1;
            }
            else if(yDir==-1){
                //왼쪽인거야
                blocks[r][c].walls[1]=1;
                blocks[rr][cc].walls[0]=1;
            }
        }
        else if(xDir==1){
            if(yDir == 0){
                //아래
                blocks[r][c].walls[3]=1;
                blocks[rr][cc].walls[2]=1;
            }
        }
        else if(xDir==-1){
            if(yDir==0){
                //위
                blocks[r][c].walls[2]=1;
                blocks[rr][cc].walls[3]=1;
            }
        }
    }

    for(int i=1;i<=k;i++){
        int x, y;
        cin>>x>>y; //여기에 소가 있다
        cows.push_back({x,y});
    }
}

int ans=0;

void BFS(int i){
    vector<vector<int>> visited;
    for(int a=1;a<=n+1;a++){
        vector<int> v;
        v.assign(n+1,0);
        visited.push_back(v);
    }
    //전부 0으로 채워진 visited를 만든다. 1,1~n,n까지 존재
    int sx = cows[i].first; int sy = cows[i].second;

    queue<pair<int, int>> q;
    q.push({sx,sy});
    visited[sx][sy]=1;
    while(!q.empty()){
        int x = q.front().first; int y = q.front().second;
        q.pop();

        for(int d=0;d<4;d++){
            int nx = x+dirX[d]; int ny = y+dirY[d];
            if(nx>=1 && nx<=n && ny>=1 && ny<=n){
                if(visited[nx][ny]==0){
                    if(blocks[x][y].walls[d]==0){
                        //그니까 범위 안이면서, 방문한 적 없고, 그 방향으로 가는데 "길"이 있지 않다면
                        visited[nx][ny]=1;
                        q.push({nx, ny});
                    }
                }
            }
        }
    }

    //모든 소들을 보면서 visited에 해당 소 위치에 1이 찍혀있지 않으면 해당 쌍은 연결이 안되는거임
    //근데 복수로 카운팅이 될 것이기에 나중에 2로 나누어주자
    for(auto cow : cows){
        int cx = cow.first; int cy = cow.second;
        if(visited[cx][cy]!=1) ans++;
    }
}

void solution(){
    //소들의 쌍을 지어가며, 서로가 길이 아닌 경로로만 가서 만날 수 있는지 체크
    //라고 하면 너무 많은 BFS를 진행하기에 그냥 각각의 소를 시작점으로 하여 BFS를 진행하고
    //연결되지 않은 소들을 체크하는 식으로 가자
    for(int i=0;i<k;i++){
        BFS(i);
    }

    cout<<ans/2;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    input();
    solution();
}