#include <bits/stdc++.h>

using namespace std;

int field[5][5]; //물고기 번호가 들어가있음
pair<pair<int, int>, int> fishes[17]; //해당 번호 물고기의 row, col, dir
pair<pair<int, int>, int> shark; //상어의 row, col, dir

int dirX[9]={0,-1,-1,0,1,1,1,0,-1};//1:up, 2:upleft, 3:left, 4:leftdown, 5:down, 6:downright, 7:right, 8:upright
int dirY[9]={0,0,-1,-1,-1,0,1,1,1};
const char* dirImg[9] ={u8" ", u8"↑", u8"↖", u8"←", u8"↙", u8"↓", u8"↘", u8"→", u8"↗"};

int sumFishNum = 0;
int maxAns=0;

void input(){
    for(int i=1;i<=4;i++){
        for(int j=1;j<=4;j++){
            int fishNum; int dir;
            cin>>fishNum>>dir;
            field[i][j] = fishNum;
            fishes[fishNum] = {{i,j},dir};
        }
    }
    
};

void testPrint(){
    for(int a=1;a<=4;a++){
        for(int b=1;b<=4;b++){
            if(a==shark.first.first && b==shark.first.second){
                cout<<"S"<<dirImg[shark.second]<<" ";
            }
            else{
                cout<<field[a][b];
                if(field[a][b]==0) cout<<"  ";
                else cout<<dirImg[fishes[field[a][b]].second]<<" ";
            }
            
        }
        cout<<"\n";
    }
}

void moveFish(){
    //fishes배열 돌며 이동하자~~

    for(int i=1;i<=16;i++){
        auto fish = fishes[i];
        int nowX = fish.first.first; int nowY = fish.first.second;
        //이 물고기가 이미 사라진건지 체크
        if(nowX==0 && nowY==0) continue;//다음 물고기로 이동
        
        //이동하는 방식이 현재 물고기의 방향부터 시작하여 이동이 가능한 지 체크
        //이동 가능한 칸 : 빈칸 or 물고기 칸

        for(int j=1;j<=8;j++){
            //현재를 기준으로 8방향 체크
            int dir = fish.second + j-1;
            if(dir>8) dir-=8;

            int nextX = nowX + dirX[dir];
            int nextY = nowY + dirY[dir];

            if(nextX>=1 && nextX<=4 && nextY>=1 && nextY<=4){
                //경계 내부여야 하고
                if(!(nextX==shark.first.first && nextY==shark.first.second)){
                    //그 칸이 상어가 아니어야 하고
                    
                    //오키 여기부터는 이동은 가능함
                    // cout<<i<<"번 물고기의 방향으로 움직일 수 있습니다! "<<nextX<<","<<nextY<<"로 이동합니다.\n";
                    //이동하려는 칸이 빈칸이냐 물고기 칸이냐

                    if(field[nextX][nextY]>0){
                        //물고기랑 스위치
                        int tempFishNum = field[nextX][nextY];
                        auto tempFish = fishes[tempFishNum]; //이동하려는 칸에 있던 물고기 정보 저장
                        //현재 i번 물고기가 nextX, nextY로 이동 방향은 dir
                        field[nextX][nextY] = i;
                        fishes[i] = {{nextX, nextY}, dir};

                        //원래 nextX, nextY에 있던 tempFishNum번 물고기가 nowX, nowY로 tempFish의 방향성 그대로 유지
                        field[nowX][nowY] = tempFishNum;
                        fishes[tempFishNum] = {{nowX, nowY}, tempFish.second};
                    }
                    else{
                        //빈칸으로 이동
                        field[nextX][nextY] = field[nowX][nowY];//그 칸으로 물고기 번호 이동
                        field[nowX][nowY]=0;

                        //i번 물고기 이동이기에 해당 정보 변경
                        fishes[i] = {{nextX, nextY}, dir};
                    }

                    break;
                }
            }
        }

        // cout<<i<<"번 물고기 이동 후 상태 : \n";
        // testPrint();
    }

    //testPrint();
}

void moveShark(){
    int sx = shark.first.first; int sy = shark.first.second;

    
}

void dfs(){
    //매번 돌아가는 형식은 물고기 이동-> 상어 이동

    moveFish();

    //이때 상어가 움직일 수 있는 선택지를 어디 넣어줘
    vector<pair<pair<int, int>, int>> v;
    int sharkX = shark.first.first; int sharkY = shark.first.second;
    int sharkDir = shark.second;

    int nextSharkX = sharkX + dirX[sharkDir];
    int nextSharkY = sharkY + dirY[sharkDir];
    while(nextSharkX>=1 && nextSharkX<=4 && nextSharkY>=1 && nextSharkY<=4){
        //범주 안
        if(field[nextSharkX][nextSharkY]>0){
            //상어가 갈 수 있는 칸임
            v.push_back({{nextSharkX,nextSharkY}, fishes[field[nextSharkX][nextSharkY]].second});
            //cout<<"상어가 갈 수 있는 칸 삽입\n";
        }
        nextSharkX = nextSharkX + dirX[sharkDir];
        nextSharkY = nextSharkY + dirY[sharkDir];
    }

    if(v.size()==0){
        //이럼 해당 세계관이 종료된다.
        if(sumFishNum>maxAns) maxAns = sumFishNum;
        return;
    }
    else{
        //백업 정보
        int tempField[5][5]; //물고기 번호가 들어가있음
        for(int i=0;i<=4;i++){
            for(int j=0;j<=4;j++){
                tempField[i][j] = field[i][j];
            }
        }
        pair<pair<int, int>, int> tempFishes[17]; //해당 번호 물고기의 row, col, dir
        for(int i=1;i<=16;i++) tempFishes[i] = fishes[i];
        pair<pair<int, int>, int> tempShark; //상어의 row, col, dir
        tempShark = shark;
        bool tempGoHome;
        int tempSumFishNum;
        tempSumFishNum = sumFishNum;
        

        //세계관 열어
        for(auto i : v){
            int nextSharkX = i.first.first; int nextSharkY = i.first.second;
            int nextSharkDir = i.second;

            //상어가 next로 이동하여 거기 물고기를 먹는다.
            //그러고 세계관을 열어서 돌린다


            //해당 세계관이 끝나서 여기로 돌아오면, 변형된 전역변수를 뒤로 돌려야 한다.
            //field, fishes, shark, goHome, sumFishNum들을 이전거로 다시 백업

            //백업 정보 저장해둬볼까? 이건 우선 for 밖에서 전부 가능

            //이제 상어 이동
            
            //이동할 곳에 있는 fish 처리
            int t = field[nextSharkX][nextSharkY];
            field[nextSharkX][nextSharkY] = 0;
            fishes[t] = {{0,0},0};
            sumFishNum += t;
            shark.first.first = nextSharkX; shark.first.second = nextSharkY;
            shark.second = nextSharkDir;

            //샤크 이동 완료
            // cout<<"샤크 이동 완료\n";
            // testPrint();

            dfs();

            //백업
            for(int i=0;i<=4;i++){
                for(int j=0;j<=4;j++){
                    field[i][j] = tempField[i][j];
                }
            }
            for(int i=1;i<=16;i++) fishes[i] = tempFishes[i];
            shark = tempShark;
            sumFishNum = tempSumFishNum;
        }

    }
}

void solution(){
    // cout<<"현재 물고기 상태 : \n";
    // testPrint();
    

    //먼저 상어 1,1세팅

    shark = {{1,1}, fishes[field[1][1]].second};
    sumFishNum += field[1][1];//해당 물고기 번호 먹음

    fishes[field[1][1]] = {{0,0},0}; //해당 번호의 물고기 정보를 0으로 처리
    //앞으로 물고기 정보가 0이면 없는 물고기로 인식
    field[1][1] = 0; //해당 위치에 물고기가 없음을 0으로 표시
    

    //상어가 집 갈 때까지 dfs돌려야 할 거 같은데
    //상어가 이동할 때 세계관이 열리는 개념
    dfs();

    cout<<maxAns;
};

int main(){
    // cin.tie(0);
    // ios::sync_with_stdio(0);

    input();
    solution();
}