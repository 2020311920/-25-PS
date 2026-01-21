#include <bits/stdc++.h>

using namespace std;

struct fish{
    int x;
    int y;
    int dir;
    bool moved=false;
};

struct Shark{
    int x;
    int y;
};

struct block{
    deque<fish> fishes;
    int leftSmell=0;
};
block field[5][5];
Shark shark;
int fishNum;
int n;

int dirX[9]={0,0,-1,-1,-1,0,1,1,1};//1왼, 2왼위, 3위, 4위오, 5오, 6오아래, 7아래, 8왼아래
int dirY[9]={0,-1,-1,0,1,1,1,0,-1};
int sharkDirX[5]={0,-1,0,1,0};
int sharkDirY[5]={0,0,-1,0,1};//1상, 2좌, 3하, 4우
const char* dirImg[9]={u8" ",u8"←",u8"↖",u8"↑",u8"↗",u8"→",u8"↘",u8"↓",u8"↙",};

void testPrint(){
    for(int i=1;i<=4;i++){
        for(int j=1;j<=4;j++){
            cout<<"[";
            cout<<field[i][j].leftSmell;
            if(field[i][j].fishes.size()>0){
                int length = field[i][j].fishes.size();
                for(int f=0;f<length;f++) cout<<dirImg[field[i][j].fishes[f].dir];
            }
            else{
                //물고기가 없다
                cout<<" ";
            }

            if(i==shark.x && j==shark.y) cout<<"S";
            
            cout<<"]";
        }
        cout<<"\n";
    }
}

void input(){
    cin>>fishNum>>n;
    for(int i=1;i<=fishNum;i++){
        int x,y,d;
        cin>>x>>y>>d;
        field[x][y].fishes.push_back({x,y,d});
    }
    cin>>shark.x>>shark.y;
}

void moveFish(){
    //새롭게 움직이는거라 모든 물고기들은 moved 초기화
    for(int i=1;i<=4;i++){
        for(int j=1;j<=4;j++){
            int length = field[i][j].fishes.size();
            for(int f=0;f<length;f++) field[i][j].fishes[f].moved = false;
        }
    }
    for(int i=1;i<=4;i++){
        for(int j=1;j<=4;j++){
            if(field[i][j].fishes.size()>0){
                //그럼 그 칸에 물고기가 있다.
                int num = field[i][j].fishes.size();
                //cout<<i<<", "<<j<<"에 있는 물고기 "<<num<<"마리를 이동한다\n";
                while(num--){
                    //총 num만큼 pop_front()이동하거나, 이동못하면 push_back();
                    auto fish = field[i][j].fishes.front(); field[i][j].fishes.pop_front();
                    int dir= fish.dir;
                    int sx = fish.x;
                    int sy = fish.y;
                    
                    if(fish.moved==true){
                        //이미 도착했던 놈이니까 뒤로 넣어줘
                        field[i][j].fishes.push_back({i,j,dir,true});
                        continue;
                    }
                    //cout<<dirImg[dir]<<"인 물고기를 이동하려고 한다\n";
                    bool isMoved= false;
                    for(int d=0;d<8;d++){
                        if(dir<1) dir+=8;

                        int nx = sx+dirX[dir];
                        int ny = sy+dirY[dir];

                        if(nx>=1 && nx<=4 && ny>=1 && ny<=4){
                            if(!(nx == shark.x && ny==shark.y)){
                                if(field[nx][ny].leftSmell==0){
                                    //이럼 이 방향으로 이동해야 해.
                                    //이미 전 칸에서는 빼버림
                                    //그럼 이동하는 칸에 넣어버리자
                                    //cout<<nx<<","<<ny<<"로 "<<dirImg[dir]<<"인 방향으로 이동해서 도착\n";
                                    field[nx][ny].fishes.push_back({nx, ny, dir,true});
                                    isMoved=true;
                                    break;
                                }
                            }
                        }
                        dir--;
                    }
                    if(!isMoved){
                        field[i][j].fishes.push_back({i,j,dir,true});
                        continue;
                    }
                    
                }
            }
        }
    }
}

void sharkMove(){
    //3회 이동하는데, 그 중 최대로 물고기를 잡는 이동
    //방향은 sharkDir 1,2,3,4 순서대로 돌리면서 갱신된 최소가 사전순으로 앞서도록 세팅
    int maxEat = -1;
    int finalX, finalY;
    int firstX, firstY, secondX, secondY;
    for(int a=1;a<=4;a++){
        //a로 1차이동
        int anx = shark.x + sharkDirX[a];
        int any = shark.y + sharkDirY[a];

        if(anx>=1 && anx<=4 && any>=1 && any<=4){
            //범주 안이면 이동 가능
            for(int b=1;b<=4;b++){
                int bnx = anx + sharkDirX[b];
                int bny = any + sharkDirY[b];
                if(bnx>=1 && bnx<=4 && bny>=1 && bny<=4){
                    for(int c=1;c<=4;c++){
                        //a, b, c를 선택한거임
                        int tempMaxEat=0;
                        int cnx = bnx + sharkDirX[c];
                        int cny = bny + sharkDirY[c];
                        if(cnx>=1 && cnx<=4 && cny>=1 && cny<=4){
                            //이거까지 성공한거면 갈 수 있는 경로
                            //a,b,c로 움직인 경로에 먹을것을 tempMaxEat에 더해주고 정리해보자
                            //tempMaxEat += (field[anx][any].fishes.size() + field[bnx][bny].fishes.size() + field[cnx][cny].fishes.size());
                            auto tempFishA = field[anx][any].fishes;
                            auto tempFishB = field[bnx][bny].fishes;
                            auto tempFishC = field[cnx][cny].fishes;

                            tempMaxEat += field[anx][any].fishes.size();
                            field[anx][any].fishes.clear();
                            
                            tempMaxEat += field[bnx][bny].fishes.size();
                            field[bnx][bny].fishes.clear();
                            
                            tempMaxEat += field[cnx][cny].fishes.size();
                            field[cnx][cny].fishes.clear();

                            if(tempMaxEat>maxEat){
                                //cout<<anx<<","<<any<<"로 1차 이동 "<<bnx<<","<<bny<<"로 2차 이동 "<<cnx<<","<<cny<<"로 3차 이동했더니 "<<maxEat<<"보다 많이 먹는 "<<tempMaxEat<<"이 나옴\n";
                                maxEat = tempMaxEat;
                                finalX = cnx; finalY = cny;
                                firstX = anx; firstY = any;
                                secondX = bnx; secondY = bny;
                            }
                            //복구
                            field[anx][any].fishes = tempFishA;
                            field[bnx][bny].fishes = tempFishB;
                            field[cnx][cny].fishes = tempFishC;
                        }
                        else{
                            //나가리
                        }
                    }
                }
                else{
                    //나가리
                }
                
            }
        }
        else{
            //a이동부터 나가리면 걍 나가리인거임
        }
        
    }

    //결정된 위치로 샤크 이동 및 그 사이에 물고기들 없애고 동시에 냄새 를 없애줘
    for(int i=1;i<=4;i++){
        for(int j=1;j<=4;j++){
            if(field[i][j].leftSmell>0) field[i][j].leftSmell--;
        }
    }
    
    // cout<<"상어 이동 전 오류 체크\n";
    // testPrint();
    
    if(field[firstX][firstY].fishes.size()>0){
        field[firstX][firstY].leftSmell = 2;
        field[firstX][firstY].fishes.clear();
    }
    
    if(field[secondX][secondY].fishes.size()>0){
        field[secondX][secondY].leftSmell = 2;
        field[secondX][secondY].fishes.clear();
    }
    
    if(field[finalX][finalY].fishes.size()>0){
        field[finalX][finalY].leftSmell = 2;
        field[finalX][finalY].fishes.clear();
    }

    shark.x = finalX; shark.y = finalY;

}

void solution(){
    //cout<<"초기상태\n";
    //testPrint();
    while(n--){
        block temp[5][5];
        for(int i=0;i<5;i++){
            for(int j=0;j<5;j++){
                temp[i][j] = field[i][j];
            }
        }
        //물고기 움직이기 전에 현재 상태를 저장해둬야 함
        moveFish();
        //testPrint();

        sharkMove();
        for(int i=1;i<=4;i++){
            for(int j=1;j<=4;j++){
                //원래있던 물고기들 붙여넣기
                int length = temp[i][j].fishes.size();
                for(int f=0;f<length;f++){
                    field[i][j].fishes.push_back(temp[i][j].fishes[f]);
                }


            }
        }
        //testPrint();
    }

    int ans=0;
    for(int i=1;i<=4;i++){
        for(int j=1;j<=4;j++){
            ans+=field[i][j].fishes.size();
        }
    }

    cout<<ans;
}

int main(){
    // cin.tie(0);
    // ios::sync_with_stdio(0);

    input();
    solution();
}