#include <bits/stdc++.h>

using namespace std;

int r,c;
pair<int, int> field[1001][1001];
int visited[1001][1001];
int jhPosX, jhPosY;
queue<pair<int, int>> fireQ;

int dirX[4]={0,1,0,-1};
int dirY[4]={1,0,-1,0};

void fieldPrint(){
    cout<<"필드를 출력합니다\n";
    for(int i=1;i<=r;i++){
        for(int j=1;j<=c;j++){
            cout<<field[i][j].second<<" ";
        }
        cout<<"\n";
    }
}

void input(){
    cin>>r>>c;
    for(int i=1;i<=r;i++){
        string str;
        cin>>str;
        for(int j=1;j<=c;j++){
            char ch = str[j-1];
            if(ch=='#') field[i][j] = {0,1};
            else if(ch=='J'){
                jhPosX = i; jhPosY = j;
            }
            else if(ch=='F'){
                fireQ.push({i,j});
                field[i][j] = {0,2};
            }
            //'.'이 입력되는 건 0으로 처리할 거라 무시해도 돼
        }
    }
}

void fireExpand(int time){
    //이미 한번 확장했다면, 이전 위치들은 다시 볼 필요가 없어. 
    //그래서 처음에는 막 확장된 위치들을 저장해서 거기만 보려고 했는데, 
    //그렇게 할 만한 자료구조를 못찾겠네, 심지어 겹쳐져서 확산되면, 중복되지 않게 신규 불의 위치를 관리하는 자료구조를 못찾겠다.
    //애초에 맵 사이즈가 작으니 매번 r*c로 검색해서, 가장 최신 불들 주위를 +1해서 표현하자
    //그러고 다 풀고 나서 초기 생각 구현방법을 찾아보던가 하자

    //가 아니라 불도 BFS처럼 하면 되네 생각해보니
    queue<pair<int, int>> nq;
    while(!fireQ.empty()){
        int nowX = fireQ.front().first; int nowY = fireQ.front().second;
        fireQ.pop();
        for(int i=0;i<4;i++){
            int nextX = nowX+dirX[i];
            int nextY = nowY+dirY[i];

            if(nextX>=1 && nextX<=r && nextY>=1 && nextY<=c){
                if(field[nextX][nextY].second==0){
                    field[nextX][nextY].second=2;
                    field[nextX][nextY].first = time;
                    nq.push({nextX,nextY});
                }
            }
        }
    }

    fireQ = nq;//이렇게 넘겨도 되나?
}

void bfs(){
    //항상 불 확장 후 필드 업데이트
    bool success=false;
    int ansTime=0;
    queue<pair<int,pair<int, int>>> q;
    q.push({0,{jhPosX, jhPosY}});//0초일때의 위치
    visited[jhPosX][jhPosY]=1;
    int time = 0;
    while(!q.empty()){
        
        int nowTime = q.front().first;
        int nowX = q.front().second.first;
        int nowY = q.front().second.second; q.pop();
        //cout<<nowTime<<"일때의 지훈이 위치 : "<<nowX<<", "<<nowY<<"\n";

        if(nowTime==time){
            time++;
            fireExpand(time);
        }

        //fieldPrint();

        if(nowX==r || nowX==1 || nowY==c || nowY==1){
            //경계에 위치했다는 소리 이러면 탈출한 거야
            success = true;
            ansTime = nowTime+1;
            break;
        }

        for(int i=0;i<4;i++){
            int nextX = nowX+dirX[i];
            int nextY = nowY+dirY[i];

            if(nextX>=1 && nextX<=r && nextY>=1 && nextY<=c){
                //일단 범위 안
                //nowTime+1일때 갈 수 있는 곳으로 이동
                if(field[nextX][nextY].second == 1){
                    //그냥 벽
                    continue;
                }

                if(field[nextX][nextY].second == 2){
                    //불이라면 해당 위치가 언제 확산된 곳인지 체크
                    if(field[nextX][nextY].first<=nowTime+1){
                        //nowTime+1을 포함한 이전에 불이었던 곳 그럼 애초에 못가
                        continue;
                    }
                }

                if(visited[nextX][nextY]==1) continue; //visited 에도 언제 방문했느냐를 담아줘야 하나 싶은데, 먼저 방문했다면 무조건 이득이고, 나중에 방문하면 무조건 손해 아닌가? 그러니 필요가 없을 것

                //위 조건들을 다 버텼다면
                visited[nextX][nextY]=1;
                q.push({nowTime+1,{nextX, nextY}});
            }
        }
    }

    if(success) cout<<ansTime;
    else cout<<"IMPOSSIBLE";
}

void solution(){
    //먼저 불을 확산 시키고
    //매초 필드를 업데이트 시켜서 BFS
    bfs();
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    input();
    solution();
}