#include <bits/stdc++.h>

using namespace std;

int dirX[5]={0,0,0,-1,1}; //1right, 2left, 3up, 4down
int dirY[5]={0,1,-1,0,0};

int n,k;
pair<pair<int, int>,int> players[11];
int field[13][13];
deque<int> onField[13][13];
int turn = 0;

void input(){
    cin>>n>>k;

    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cin>>field[i][j];
        }
    }

    for(int i=1;i<=k;i++){
        int x, y, d;
        cin>>x>>y>>d;
        players[i] = {{x,y},d};
        onField[x][y].push_back(i);
    }
}

void whiteMove(int playerNum){
    auto player = players[playerNum];
    int sx = player.first.first;
    int sy = player.first.second;
    int dir = player.second;

    int nx = sx+dirX[dir];
    int ny = sy + dirY[dir];

    int length = onField[sx][sy].size();
    int i;
    for(i=0;i<length;i++){
        if(onField[sx][sy][i]==playerNum) break;
    }
    deque<int> temp;
    for(int j = length-1; j>=i; j--){
        //뒤에서 한명씩 옮기는데, white니까, 순서가 그대로 들어가야해서 조금 어려움
        temp.push_back(onField[sx][sy].back());
        onField[sx][sy].pop_back();
    }

    //temp에서 pop_back해서 다음 칸에 push_back

    while(!temp.empty()){
        auto tempPlayer = temp.back(); temp.pop_back();
        //cout<<sx<<","<<sy<<"에 있던 플레이어"<<tempPlayer<<"가 "<<nx<<", "<<ny<<"로 이동합니다.\n";
        onField[nx][ny].push_back(tempPlayer);
        players[tempPlayer].first.first = nx;
        players[tempPlayer].first.second = ny;
    }
}

void redMove(int playerNum){
    auto player = players[playerNum];
    int sx = player.first.first;
    int sy = player.first.second;
    int dir = player.second;

    int nx = sx+dirX[dir];
    int ny = sy + dirY[dir];

    int length = onField[sx][sy].size();
    int i;
    for(i=0;i<length;i++){
        if(onField[sx][sy][i]==playerNum) break;
    }
    
    for(int j = length-1; j>=i; j--){
        //뒤에서 한명씩 옮기는데, red니까, 그 순서대로 넣어주면 돼
        
        int temp = onField[sx][sy].back(); onField[sx][sy].pop_back();
        //cout<<sx<<","<<sy<<"에 있던 플레이어"<<temp<<"가 "<<nx<<", "<<ny<<"로 이동합니다.\n";
        onField[nx][ny].push_back(temp);   
        players[temp].first.first = nx;
        players[temp].first.second = ny; 
    }
}

void move(int playerNum){
    /*특정 플레이어가 움직일 때
    우선, 본인 위치 확인하고, 본인의 움직임을 설정한 뒤에
    본인 위에 있는 애들과 다같이 움직인다.
    도착하는 칸에 push_back을 해준다.*/

    /*이 함수에서는 본인의 움직임만 설정해주자.*/
    auto player = players[playerNum];
    int sx = player.first.first;
    int sy = player.first.second;
    int dir = player.second;

    int nx = sx+dirX[dir];
    int ny = sy + dirY[dir];

    if(!(nx>=1 && nx<=n && ny>=1 && ny<=n)){
        
        //외부로 나갔어 그럼 방향 바꿔서 
        if(dir==1 || dir==3) players[playerNum].second = dir+1;
        else if(dir==2 || dir==4) players[playerNum].second = dir-1;
    
        int tempNx = sx+dirX[players[playerNum].second];
        int tempNy = sy+dirY[players[playerNum].second];

        if(field[tempNx][tempNy]==2){
            //두번 연속 나가리

        }
        else if(field[tempNx][tempNy]==0) whiteMove(playerNum);
        else if(field[tempNx][tempNy]==1) redMove(playerNum);
    }
    else if(field[nx][ny]==0) whiteMove(playerNum);
    else if(field[nx][ny]==1) redMove(playerNum);
    else if(field[nx][ny]==2){
        //파랑이야 그럼 방향 바꿔서
        if(dir==1 || dir==3) players[playerNum].second = dir+1;
        else if(dir==2 || dir==4) players[playerNum].second = dir-1;
        //아예 얘의 방향성질을 바꿔야 함.
        int tempNx = sx+dirX[players[playerNum].second];
        int tempNy = sy+dirY[players[playerNum].second];

        //하필 외부임
        if(!(tempNx>=1 && tempNx<=n && tempNy>=1 && tempNy<=n)){
            //두번 연속 나가리
        }
        else if(field[tempNx][tempNy]==0) whiteMove(playerNum);
        else if(field[tempNx][tempNy]==1) redMove(playerNum);
    }

}

void solution(){
    while(turn<1000){
        turn++;

        for(int i=1;i<=k;i++){
            //auto player = players[i];
            move(i);
            for(int j=1;j<=n;j++){
                for(int l=1;l<=n;l++){
                    if(onField[j][l].size()>=4) return;
                }   
            }
        }
        //cout<<"현재 필드에 몇명이 위치해있는지\n";
        // for(int i=1;i<=n;i++){
        //     for(int j=1;j<=n;j++){
        //         cout<<onField[i][j].size()<<" ";
        //     }
        //     cout<<"\n";
        // }

        // for(int i=1;i<=k;i++){
        //     cout<<i<<"번 플레이어는 "<<players[i].first.first<<", "<<players[i].first.second<<"에 방향은 "<<players[i].second<<"입니다\n";
        // }
        // cout<<"\n";
    }
}

int main(){
    // cin.tie(0);
    // ios::sync_with_stdio(0);

    input();

    solution();

    if(turn>=1000) cout<<-1;
    else cout<<turn;
}