/*
흠.. 문제를 딱 보니 시뮬레이션 문제 같다.
일단 "동일한"시간에 배양액 둘이 서로 도착해야 꽃을 피운다.
맵의 최대 사이즈는 50*50이고, 배양액의 개수 최대도 그렇게 크지 않은 상황
DFS와 BFS를 적절히 사용한다면 좋을까?
일단 두 배양액을 매번 같은 순간 놓는다고 좋은 건 또 아닐것 같다. 이게 문제에서 어려워지는 포인트 인 듯
그니까 1초에 꼭 초록과 빨간 배양액을 동시에 놓을 필요는 또 없다 이거지 

라고 생각했는데, 이 문제에서는 그건 아닌거 같긴 하네,, 만약 다른 타이밍에 놓을 수 있게 된다면
좀 많이 어려워지겠다 대박.. 이렇게 된다면 또 어떻게 풀어야 할지 고민이네..
아마 똑같이 DFS+BFS로 하되, 놓을 수 있는 칸이 없는데 배양액이 남지 않도록 처리하면 되려나

일단 0초에 모두 뿌려놓는다는 전제 하에 풀어본다면..
어디에 놓을 지는 DFS로 풀어야 할 듯 싶고 이건 배양액을 "뿌릴 수 있는" 칸들을 미리 저장하거나, 맵 사이즈가 
막 엄청 큰건 아니니까 그냥 탐색하면서 DFS를 조져도 될 것 같아 보인다.

일단 배양액을 처음 놓는 DFS의 시간복잡도는 최악의 경우 2500C5+2500C5일 거인데, 대충 100억 아래가 나오는걸 보면
음.. 심각하다

어?! 문제에 "배양액을 뿌릴 수 있는 땅의 개수는 최대 10개"라고 되어있네
그러면 DFS 최악이 10C5*10C5니까 대충 충분하고
거기서 매번 BFS를 돌리니까 매 DFS마다 50^2이면... 매우매우 아슬아슬하게 1.5초정도 나올것같은 느낌..
자세한건 제대로 시간 계산을 해보자

일단 이렇게 푸는 것이 "최적"이냐라고 한다면 뭔가 아닌것 같다.
음.. 제대로 시간 계산을 해본다 하면, 최대 10Cg + (10-n)Cr이 되기에 g,r이 애매하게 막 3,3이런다해도 10000을 넘지는 않아 보인다. 거기에 매번 DFS를 한다쳐도 2500*10000이기에 1초안으로 끊을 수는 있어보이네
일단 이렇게 풀어봐야겠다 ㅇㅇ
*/

#include <bits/stdc++.h>

using namespace std;

int n,m;
int G,R;

struct Block{
    int what=0; //호수냐, 빈 공간이냐
    int Gtime=0;
    int Rtime=0;
};

Block field[51][51];
vector<pair<int, int>> possible;

void input(){
    cin>>n>>m>>G>>R;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            int num;
            cin>>num;
            //field[i][j]=num; //굳이 필드에 해당 수를 저장할 필요가 없어. 처음에 입력하는 것은
            //호수처럼 갈 수 없는 곳, 배양액을 놓을 수 있냐 없냐인데, 배양액 관련은 나중에는 탐색에 필요가 없기에
            //나중에 BFS를 조지기 위해서는 호수를 1, 나머지는 그냥 0으로 유지하자
            if(num==0){
                //호수면 오히려 필드에 1을 놓는 거지
                field[i][j].what=1;
            }
            if(num==2){
                //뿌릴 수 있는 땅을 미리 따로 저장
                possible.push_back({i,j});
            }
        }
    }
}

int dirX[4]={0,1,0,-1};
int dirY[4]={1,0,-1,0};

int DFSvisited[51][51];
//int BFSvisited[10];//뿌릴 수 있는 땅은 최대 10이므로
vector<int> BFSvisited;

int maxFlowerCnt=0;

void testPrint(){
    cout<<"\n";
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(field[i][j].what==1) cout<<1<<" ";
            else if(field[i][j].Gtime==1) cout<<"G ";
            else if(field[i][j].Rtime==1) cout<<"R ";
            else cout<<"0 ";
        }
        cout<<"\n";
    }
    
}

void spread(){
    //testPrint();
    int time = 0;
    Block newField[51][51];
    queue<pair<int, int>> q;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            newField[i][j] = field[i][j];
            if(field[i][j].Gtime>0 || field[i][j].Rtime>0) q.push({i,j});
        }
    }
    int flowerCnt=0;
    while(1){
        time++;
        int spreadCnt=0;
        queue<pair<int, int>> nq;
        while(!q.empty()){
            int i = q.front().first;
            int j = q.front().second;
            q.pop();
        // for(int i=1;i<=n;i++){
        //     for(int j=1;j<=m;j++){
                //cout<<i<<", "<<j<<"에서 탐색할게요\n";
            if(newField[i][j].Gtime!=0 && newField[i][j].Gtime == newField[i][j].Rtime){
                //이건 꽃 피운 칸이니까 그냥 넘어가면 돼
                continue;
            }
            //그게 아니라면 확산
            if(newField[i][j].Gtime==time || newField[i][j].Rtime == time){
                //다음칸을 먼저 만들어놓자
                for(int k=0;k<4;k++){
                    int nx = i+dirX[k];
                    int ny = j+dirY[k];

                    if(nx>=1 && nx<=n && ny>=1 && ny<=m){
                        //다음 칸이 범위 안이야
                        if(newField[nx][ny].what==0){
                            //다음칸이 심지어 이동 가능한 칸이다
                            //이제 현재칸이 뭐였냐에 따라 진행
                            //그전에, 이동하려는 칸이 이미 꽃일 수도 있어
                            if(newField[nx][ny].Gtime!=0 && newField[nx][ny].Gtime==newField[nx][ny].Rtime) continue;
                            if(newField[i][j].Gtime==time){
                                //초록칸이었다면
                                //아예 깨끗한 칸으로 이동하거나
                                //이동하려는 칸의 빨강이 time+1과 같거나

                                if(newField[nx][ny].Rtime==0&&newField[nx][ny].Gtime==0){
                                    //spreadCnt++;
                                    newField[nx][ny].Gtime = time+1;
                                    nq.push({nx,ny});
                                }
                                else if(newField[nx][ny].Rtime==time+1){
                                    //마침 같은거면 확산과 동시에 꽃 카운팅
                                    //spreadCnt++;
                                    //cout<<nx<<", "<<ny<<"에서 꽃 탄생!\n";
                                    flowerCnt++;
                                    newField[nx][ny].Gtime = time+1;
                                }
                            }
                            else if(newField[i][j].Rtime == time){
                                //빨간칸이었다면
                                //역시나 아예 깨끗한 칸으로 or
                                //이동하려는 칸의 초록이 time+1과 같거나
                                if(newField[nx][ny].Rtime==0&&newField[nx][ny].Gtime==0){
                                    //spreadCnt++;
                                    newField[nx][ny].Rtime = time+1;
                                    nq.push({nx,ny});
                                }
                                else if(newField[nx][ny].Gtime==time+1){
                                    //마침 같은거면 확산과 동시에 꽃 카운팅
                                    //spreadCnt++;
                                    //cout<<nx<<", "<<ny<<"에서 꽃 탄생!\n";
                                    flowerCnt++;
                                    newField[nx][ny].Rtime = time+1;
                                }
                            }
                        }
                    }
                }
            }

            
        }

        //모든 칸 검색했는데, 새롭게 확산되는 칸이 없었다면 그대로 종료해도 돼
        if(nq.empty()){
            break;
        }
        q = nq;
    }
    // cout<<"이 경우의 꽃의 수는 "<<flowerCnt<<"\n";
    // for(int i=1;i<=n;i++){
    //     for(int j=1;j<=m;j++){
    //         if(newField[i][j].what==1) cout<<"1 ";
    //         else if(newField[i][j].Gtime!=0 && newField[i][j].Gtime==newField[i][j].Rtime) cout<<"F ";
    //         else if(newField[i][j].Gtime>0) cout<<"G ";
    //         else if(newField[i][j].Rtime>0) cout<<"R ";
    //         else cout<<"0 ";
    //     }
    //     cout<<"\n";
    // }
    maxFlowerCnt = max(maxFlowerCnt, flowerCnt);
}

void redDFS(int cnt, int x){
    int size = possible.size();
    if(cnt==R){
        //빨강도 다 고른거야. 그럼 이제 이를 바탕으로 이제 시간에 따라 확산 진행
        spread();
        return;
    }

    //다 못골랐는데 앞으로 고를 양이 더 많이 남았다 그럼 세계관 일찍 닫아
    if(R-cnt>size-x+1) return;

    for(int i=x;i<size;i++){
        if(BFSvisited[i]==0){
            //아직 선택하지 않은 땅이라면
            BFSvisited[i]=1;
            field[possible[i].first][possible[i].second].Rtime=1;
            redDFS(cnt+1, i+1);
            field[possible[i].first][possible[i].second].Rtime=0;
            BFSvisited[i]=0;
        }
    }
}

void greenDFS(int cnt, int x){
    int size = possible.size();
    if(cnt==G){
        //다 고른거야
        //이제야 빨강DFS를 조져야 해
        redDFS(0,0);
        return;
    }

    //다 고르지 않았는데 앞으로 다 골라도 이미 cnt가 G개를 못고른다면 해당 세계관 일찍 닫아야지
    if(G-cnt>size-x+1){
        return;
    }

    
    for(int i=x;i<size;i++){
        if(BFSvisited[i]==0){
            //아직 선택하지 않은 땅이라면
            BFSvisited[i]=1;
            field[possible[i].first][possible[i].second].Gtime=1;
            greenDFS(cnt+1, i+1);
            field[possible[i].first][possible[i].second].Gtime=0;
            BFSvisited[i]=0;
        }
    }
    
}

void init(){
    BFSvisited.assign(possible.size(), 0); //BFSvisited배열을 벡터로 필요한 만큼만 만드는 거지
}

void simulation(){
    init();
    //우선 배양액을 잘 놓아보자꾸나

    //우선 초록 배양액부터
    greenDFS(0,0);//0개 선택, 0번 인덱스부터 탐색
    cout<<maxFlowerCnt;
}

void solution(){
    //원래 계획대로
    //DFS+BFS
    simulation();
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    input();
    solution();
}