#include <bits/stdc++.h>

using namespace std;

int n,m;
int field[101][101];
int visited[101][101];
//일단 지금 당장 보이는 문제점은 다음과 같아
/*치즈 내부의 공간이었다가 아니게 되는 걸 어떻게 알 수 있을까.
그니까 초반에 치즈 덩이들을 BFS로 찾는다고 칠 때, 영역을 1,1부터 잡고 대신 BFS는 0,0부터 해서 덩어리별로 
visited를 1씩 늘려가며 탐색하면 1은 외부니까 알 수 있어. 
뭐 이것도 좋은 방법인지는 모르겠지만 일단 당장 내가 생각해낸 방법은 그렇다.
근데 문제는 나중에 치즈들이 사라지면서 내부의 공간이었던 게 다시 외부가 될 수 있다는거지
그럼 치즈가 사라질 때마다 다시 BFS를 조져? 이것도 좀 웃기다고 생각하는데...
일단은 뭐 어떡해, 할 수 있는 방법대로 일단은 구현해보고 안되면 고쳐야지*/

void input(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin>>field[i][j];
        }
    }
}

void init(){
    for(int i=0;i<101;i++){
        for(int j=0;j<101;j++){
            visited[i][j]=-1;
        }
    }
}

int dirX[4]={0,1,0,-1};
int dirY[4]={1,0,-1,0};

void BFS(int x, int y){
    queue<pair<int, int>> q;
    q.push({x,y});
    visited[x][y]=0;
    while(!q.empty()){
        int sx = q.front().first;
        int sy = q.front().second;
        q.pop();

        for(int i=0;i<4;i++){
            int nx = sx + dirX[i];
            int ny = sy + dirY[i];

            if(nx>=0 && nx<=n && ny>=0 && ny<=m){
                //필드 자체는 1~이지만, 쉽게 외부를 확인하기 위한
                //내 전략을 위해서 0이어도 가능인 것이다...
                if(field[nx][ny]==0){
                    //빈공간이어야 하고 ㅇㅇ
                    if(visited[nx][ny]==-1){
                        //아직 방문하지 않아야

                        //이제야 우리는 이 곳이 외부와 연결되는 곳이구나를 확인합니다
                        visited[nx][ny]=0;
                        q.push({nx,ny});
                    }
                }
            }
        }
    }
}

bool isCheeseExist(){
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(field[i][j]==1){
                return true;
            }
        }
    }
    return false;
}

void deleteCheese(){
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(field[i][j]==1){
                //i,j를 주위로 하는 4방향을 검색했을 때, visited좌표값이 0이면 외부입니다.
                int outCnt=0;
                for(int k=0;k<4;k++){
                    int nx = i+dirX[k];
                    int ny = j+dirY[k];

                    if(nx>=1 && nx<=n && ny>=1 && ny<=m){
                        //이때는 0고려 안해도 되는게, 기본적인 1~인 필드 외부이면 그냥 바깥인거라 카운트 가능
                        if(visited[nx][ny]==0) outCnt++;
                    }
                    else outCnt++;
                }

                if(outCnt>=2){
                    //이러면 해당 위치 치즈는 사라질 거임
                    //사라지고, 해당 위치를 시작으로 하는 BFS를 진행하면 되겠당

                    //근데!! 여기서 사라져버리면, 현 단계에서는 외부와 접촉이 2미만인 애들도 나중에 지워질 수 있음 현재는 그럼 field값을 2로 변경해서 나중에 2인 놈들을 없애는 작전으로 가자 ㅇㅇ
                    field[i][j]=2;
                    //BFS(i,j);
                }
            }
        }
    }

    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(field[i][j]==2){
                //외부이고 지워지는 애들
                field[i][j]=0;
                BFS(i,j);
            }
        }
    }
}

void solution(){
    //초기화
    init();

    //BFS를 진행해서 구역을 나눈다.
    //1,1부터 필드에 찍어놨지만 BFS는 0,0부터 하여 초기 상태에 외부와 내부를 분리하자.
    //그다음에 이제 치즈가 사라질때마다 다시 0,0을 시작점으로 하는 BFS 만 진행해서 visited를 업데이트하자
    //그니까 정리하자면, 초기 visited는 -1이고, 0,0을 시작점으로 하는 BFS를 진행하여 외부는 0으로 변경하자.
    //치즈의 위치는 따로 저장할까도 생각했지만, 벡터에 넣어서 돌리나 그냥 필드에서 검색하나 똑같을 것 같다.
    //치즈 주위로 만약 visited가 0이면 외부인거고 -1이면 다른 치즈이거나 외부인거다.
    //치즈 없애기 단계가 끝나면 치즈가 사라진 부분의 visited는 무조건 0이고 거기서부터 다시 BFS를 돌리면 될 것 같다, 그 점을 시작으로 field가 0이면 빈공간인거고 거기랑 이어지면 곧 외부로 변경되는거니까 ㅇㅇ

    BFS(0,0);
    int time = 0;
    while(1){
        if(!isCheeseExist()) break;
        time++;

        deleteCheese();
    }

    cout<<time;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    input();
    solution();
}