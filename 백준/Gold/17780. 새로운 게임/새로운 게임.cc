#include <bits/stdc++.h>
using namespace std;

int n,k;
int dirX[4]={0,0,-1,1};
int dirY[4]={1,-1,0,0};

struct block{
    int color; //0white, 1red, 2blue
    deque<int> players;//{playerNumber}
};

block field[13][13];

struct player{
    int x;
    int y;
    int dir;
};

player players[11];

void input(){
    cin>>n>>k;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            int num;
            cin>>num;
            field[i][j].color = num;
        }
    }

    for(int i=1;i<=k;i++){
        int x,y,dir;
        cin>>x>>y>>dir;
        players[i]=player{x,y,dir-1};
        field[x][y].players.push_back(i);
    }
}

// bool isFull(){
//     bool full = false;
//     for(auto i : players){
//         int x = i.x;
//         int y = i.y;
//         if(field[x][y].players.size()>=4){
//             full = true;
//             break;
//         }
//     }

//     return full;
// }

int moveToRed(int x, int y){
    player me = players[field[x][y].players.front()];
    int dir = me.dir;

    int nx = x + dirX[dir]; int ny = y + dirY[dir];
    //이미 이동이 가능한 걸로 판단이 된거야.
    while(!field[x][y].players.empty()){
        int playerInd = field[x][y].players.back();
        field[x][y].players.pop_back();
        
        field[nx][ny].players.push_back(playerInd);
        //playerInd번째의 player의 x,y도 변경
        players[playerInd].x = nx;
        players[playerInd].y = ny;
    }

    return field[nx][ny].players.size();
}

int moveToWhite(int x, int y){
    player me = players[field[x][y].players.front()];
    int dir = me.dir;

    int nx = x + dirX[dir]; int ny = y + dirY[dir];
    //이미 이동이 가능한 걸로 판단이 된거야.
    while(!field[x][y].players.empty()){
        int playerInd = field[x][y].players.front();
        field[x][y].players.pop_front();
        
        field[nx][ny].players.push_back(playerInd);

        players[playerInd].x = nx;
        players[playerInd].y = ny;
    }

    return field[nx][ny].players.size();
}

int moveToBlue(int x, int y){
    int cnt;
    player me = players[field[x][y].players.front()];
    int dir = me.dir;
    //아까 이동한 방향이 blue 또는 바깥 영역이기에 이 함수로 들어온 것이기에
    if(dir == 0) dir = 1;
    else if(dir == 1) dir = 0;
    else if(dir == 2) dir = 3;
    else if(dir == 3) dir =2; // 0이었으면 1, 1였으면 0, 2이었으면 3, 3이었으면 2
    //이 새로운 방향으로 간 곳이 또 blue이거나, 바깥 영역이면 안움직이고 방향만 바꾼 거 그대로
    int nx = x+dirX[dir]; int ny = y+dirY[dir];
    if(nx>=1 && nx<=n && ny>=1 && ny<=n){
        int color = field[nx][ny].color;
        if(color == 0){
            //이때는 방향을 바꿔서 이동이 가능해진거니까 방향을 변경시켜서 이동
            players[field[x][y].players.front()].dir = dir;
            cnt = moveToWhite(x, y);
        }

        else if(color==1){
            players[field[x][y].players.front()].dir = dir;
            cnt = moveToRed(x,y);
        }
        else if(color == 2){
            //바깥으로 간거랑 동일 == 파랑으로 움직임
            players[field[x][y].players.front()].dir = dir;
            cnt = field[x][y].players.size();
        }
    }
    else{
        //바깥이니까 바뀐 방향만 유지
        players[field[x][y].players.front()].dir = dir;
        cnt = field[x][y].players.size();
    }

    return cnt;
}

int movePlayers(int x, int y){
    //x,y에 있는 뭉탱이를 바닥에 있는 놈 방향으로 움직인다.
    //이러고 움직인 뒤의 그 곳의 쌓인 개수를 리턴
    player me = players[field[x][y].players.front()];
    int dir = me.dir;
    int cnt;

    //그 방향에 있는 칸 색이 무엇인가
    int nx = x+dirX[dir]; int ny = y+dirY[dir];
    if(!(nx>=1 && nx<=n && ny>=1 && ny<=n)) cnt = moveToBlue(x, y);
    else{
        int color = field[nx][ny].color;
        if(color == 0) cnt = moveToWhite(x, y);
        else if(color == 1) cnt = moveToRed(x, y);
        else if(color == 2) cnt = moveToBlue(x, y);
    }

    return cnt;
}

void printField(){
    string dirMark[4]={"→","←", "↑", "↓"};
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cout<<"[";
            cout<<"c:"<<field[i][j].color<<" players:";
            for(auto p : field[i][j].players){
                cout<<p<<dirMark[players[p].dir]<<" ";
            }
            cout<<"]";
        }
        cout<<"\n";
    }
}

void solution(){
    int cnt=0;
    bool trigger = true;
    while(trigger){
        cnt++;
        if(cnt>1000) break;
        //종료 조건 (옮기고 나서 즉시 그곳을 확인하는 것으로 변경)
        //if(isFull()) break;

        //말 하나씩 보면서 지가 움직일 수 있으면 이동하기
        for(int i=1;i<=k;i++){
            player me = players[i];
            int x= me.x;
            int y = me.y;
            int dir = me.dir;
            //cout<<x<<", "<<y<<"에 위치한 놈의 바닥 : "<<field[x][y].players.front()<<"\n";
            if(field[x][y].players.front()==i){
                int playerNum = movePlayers(x,y);

                //cout<<i<<"번 말이 움직일 수 있어서 이동 후 : \n";
                //printField();
                if(playerNum>=4){
                    trigger = false;
                    break;
                }
            }
        }
    }

    if(cnt>1000) cout<<-1;
    else cout<<cnt;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    input();
    solution();
}