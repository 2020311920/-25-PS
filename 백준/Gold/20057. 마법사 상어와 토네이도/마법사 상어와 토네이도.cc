#include <bits/stdc++.h>

using namespace std;

int n;
int field[501][501];
int visited[501][501];

int dirX[8]={0,1,0,-1,1,1,-1,-1};//0 right, 1 down, 2 left, 3 up, 4 (01) rightdown, 5(12) downleft, 6 (23) leftup, 7 (30) upright
int dirY[8]={1,0,-1,0,1,-1,-1,1};

int outSide=0;

void input(){
    cin>>n;
    for(int i=1;i<=n;i++){
        for (int j=1;j<=n;j++){
            cin>>field[i][j];
        }
    }
}

void sandMove(int x, int y, int dirInd){
    int nowSand = field[x][y];
    for(int i=0;i<=3;i++){
        if(i!= (dirInd+2)%4){
            //dirInd = 0이면 2를 제외
            
            if(i==dirInd) continue;

            //방향성이 i인거임
            int nextX = x+dirX[i];
            int nextY = y +dirY[i];
            int nextSand = (nowSand*7)/100; //7%

            if(nextX>=1 && nextX<=n && nextY>=1 && nextY<=n){
                //범위 안
                field[nextX][nextY] += nextSand;
                field[x][y] -= nextSand;
            }
            else{
                //범위 밖
                outSide += nextSand;
                field[x][y] -= nextSand;
            }

            // 그 방향으로 한번 더 갈 수 있음
            nextX+=dirX[i];
            nextY+=dirY[i];
            nextSand = (nowSand*2)/100; //2%

            if(nextX>=1 && nextX<=n && nextY>=1 && nextY<=n){
                //범위 안
                field[nextX][nextY] += nextSand;
                field[x][y] -= nextSand;
            }
            else{
                //범위 밖
                outSide += nextSand;
                field[x][y] -= nextSand;
            }
        }
    }
    
    int candidate1 = dirInd + 4; //애초에 dirInd는 0,1,2,3이기에 범위는 괜찮
    int candidate2 = candidate1-1 < 4 ? candidate1-1+4 : candidate1-1;
    //대각선 움직임
    for(int i=4;i<=7;i++){
        if(i == candidate1 || i== candidate2){//10퍼센트
            //방향성이 i인거임
            int nextX = x+dirX[i];
            int nextY = y +dirY[i];
            int nextSand = (nowSand*10)/100; //10%

            if(nextX>=1 && nextX<=n && nextY>=1 && nextY<=n){
                //범위 안
                field[nextX][nextY] += nextSand;
                field[x][y] -= nextSand;
            }
            else{
                //범위 밖
                outSide += nextSand;
                field[x][y] -= nextSand;
            }
        }
        else{
            //1퍼센트
            //방향성이 i인거임
            int nextX = x+dirX[i];
            int nextY = y +dirY[i];
            int nextSand = (nowSand*1)/100; //1%

            if(nextX>=1 && nextX<=n && nextY>=1 && nextY<=n){
                //범위 안
                field[nextX][nextY] += nextSand;
                field[x][y] -= nextSand;
            }
            else{
                //범위 밖
                outSide += nextSand;
                field[x][y] -= nextSand;
            }
        }
    }

    //dirInd로 두번 간 거 따로 처리해주자
    int nextX = x + (dirX[dirInd]*2);
    int nextY = y + (dirY[dirInd]*2);
    int nextSand = (nowSand*5)/100; //5%

    if(nextX>=1 && nextX<=n && nextY>=1 && nextY<=n){
        //범위 안
        field[nextX][nextY] += nextSand;
        field[x][y] -= nextSand;
    }
    else{
        //범위 밖
        outSide += nextSand;
        field[x][y] -= nextSand;
    }

    //마지막으로 알파 처리
    nextX = x + dirX[dirInd];
    nextY = y + dirY[dirInd];
    nextSand = field[x][y]; //다 보내고 남은 거

    if(nextX>=1 && nextX<=n && nextY>=1 && nextY<=n){
        //범위 안
        field[nextX][nextY] += nextSand;
        field[x][y] -= nextSand;
    }
    else{
        //범위 밖
        outSide += nextSand;
        field[x][y] -= nextSand;
    }
}

void solution(){
    int sx = n/2 +1;
    int sy = n/2 + 1;
    int dirInd = 2;
    visited[sx][sy]=1;
    
    //토네이도 움직임을 구현하려면, 0right, 1down, 2left, 3up 일 따, 현재의 움직임 -1한 방향을 계속 가고 싶어야 함. ㅇㅇ
    //일단 현재 방향으로는 움직여야 함.
    while(!(sx==1 && sy==1)){
        int nextX = sx + dirX[dirInd];
        int nextY = sy + dirY[dirInd];

        //토네이도 움직임에서 nextX, nextY는 절대 범위를 벗어나지 않음
        //그래도 안전하게
        if((!nextX>=1 && nextX<=n && nextY>=1 && nextY<=n)){
            cout<<"토네이도 정지\n";
            break;
        }

        sx = nextX;
        sy = nextY;
        visited[sx][sy]=1;

        sandMove(sx, sy, dirInd); //더러운 sandMove함수지만 일단 했으니까 넘겨

        //다음 움직임을 체크
        int nextDirInd = dirInd-1;
        if(nextDirInd<0) nextDirInd = 3;

        if(visited[sx + dirX[nextDirInd]][sy+dirY[nextDirInd]]==0){
            //꺾을 수 있다
            dirInd = nextDirInd;
        }
    }
}

int main(){

    input();

    solution();

    cout<<outSide;

}