#include <bits/stdc++.h>

using namespace std;

struct PairHash {
    size_t operator()(const pair<int,int>& p) const {
        // 간단한 해시 조합 예시
        return hash<int>()(p.first) ^ (hash<int>()(p.second) << 1);
    }
};

int n, k,l;
int board[101][101];
queue<pair<int, int>> snakeMark;
unordered_set<pair<int, int>, PairHash> snakeMark2;

int startX=1, startY=1;
int dirX[4]={-1,0,1,0};//위, 오른쪽, 아래, 왼쪽
int dirY[4]={0,1,0,-1};

vector<pair<int, char>> command;

bool gameState = true;
int gameTime = 0;
int commandOrder = 0;
int dirOrder = 1; //오른쪽

pair<int, int> snakeHead;
pair<int, int> snakeTail;

bool collisionWithBody(int x, int y){
    //이 x,y가 이미 snakeMark에 있는가로 보는거임
    return snakeMark2.find({x,y}) != snakeMark2.end();
}

int main(){
    cin>>n>>k;

    for(int i=1;i<=k;i++){
        int x,y;
        cin>>x>>y;

        board[x][y] = 1;
    }

    cin>>l;

    for(int i=1;i<=l;i++){
        int x;
        char c;
        cin>>x>>c;//C입력값이 방향이 왼쪽이면, dir를 -1, 오른쪽이면 dir +1;

        command.push_back({x,c});
    }

    //게임 시작 전, 뱀 위치
    snakeMark.push({1,1});
    snakeMark2.insert({1,1});
    
    while(gameState){
        gameTime++;
        // snakeMark.front가 꼬리
        // snakeMark.back이 대가리, 이게 계속 추가되는 방식
        snakeHead = snakeMark.back();
        snakeTail = snakeMark.front();

        //머리를 늘력
        snakeHead.first+=dirX[dirOrder];
        snakeHead.second+=dirY[dirOrder];

        //게임오버 체크
        if(snakeHead.first>n || snakeHead.first<1 || snakeHead.second>n || snakeHead.second<1){//벽에 충돌
            gameState=false;
            continue;
        }
        if(collisionWithBody(snakeHead.first, snakeHead.second)){
            //지 몸에 충돌
            gameState=false;
            continue;
        }

        //일단 게임오버가 이때 안났다? 그럼 대가리 옮긴 것이 확정되는거임
        snakeMark.push({snakeHead.first, snakeHead.second});
        snakeMark2.insert({snakeHead.first, snakeHead.second});

        //사과 체크
        if(board[snakeHead.first][snakeHead.second]==1){
            //사과 먹음
            board[snakeHead.first][snakeHead.second]=0; //사과 사라짐
        }
        else{
            //사과 못먹음
            //꼬리 반환
            snakeTail=snakeMark.front();
            snakeMark.pop();
            snakeMark2.erase(snakeTail);
        }

        if(gameTime == command[commandOrder].first){
            //방향전환 해야할 타이밍이다?
            if(command[commandOrder].second=='L'){
                //현재기준 왼쪽으로 턴
                dirOrder--;
                if(dirOrder<0) dirOrder+=4;
            }
            else if(command[commandOrder].second == 'D'){
                //현재기준 오른쪽으롤 턴
                dirOrder++;
                if(dirOrder>3) dirOrder-=4;
            }
            commandOrder++;
        }

        // cout<<gameTime<<"이 끝난 기준 현 상황입니다\n";
        // for(int i=1;i<=n;i++){
        //     for(int j=1;j<=n;j++){
        //         if(snakeMark2.find({i,j})!=snakeMark2.end()) cout<<"x ";
        //         else cout<<board[i][j]<<" ";
        //     }
        //     cout<<"\n";
        // }
        
    }
    cout<<gameTime;
}