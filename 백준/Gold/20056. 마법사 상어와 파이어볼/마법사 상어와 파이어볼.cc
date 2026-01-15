#include <bits/stdc++.h>

using namespace std;

int n, M, k;
int r,c,m,s,d;
deque<pair<pair<int, int>,int>> fireBallCoord[51][51];//해당 칸에 있는 파이어볼들의 정보
deque<pair<pair<int, int>,int>> temp[51][51];

int dirX[8]={-1, -1, 0, 1, 1, 1, 0, -1};
//0 up, 1 upright, 2 right, 3 downright, 4 down, 5 downleft, 6 left, 7 upleft
int dirY[8]={0, 1, 1, 1, 0, -1, -1, -1};


void input(){
    cin>>n>>M>>k;

    for(int i=1;i<=M;i++){
        cin>>r>>c>>m>>s>>d;
        fireBallCoord[r][c].push_back({{m,s},d});
    }
}

int checkRange(int x){
    
    if(x<1){
        return n-((x*-1)%n);
    }
    else if(x>n){
        return (x%n==0 ? n : x%n);
    }

    return x;
}

void moveFireBall(pair<pair<int, int>,int> fireBall, int x, int y){
    int mass = fireBall.first.first;
    int speed = fireBall.first.second;
    int dir = fireBall.second;
    int nowX = x;
    int nowY = y;

    //이 파이어볼은 x,y에서 dir로 speed칸 움직인다.
    // while(speed--){
    //     int nextX = nowX+dirX[dir];
    //     int nextY = nowY+dirY[dir];
    //     nowX = checkRange(nextX);
    //     nowY = checkRange(nextY); //외부로 나간거 연결
    // }
    int nextX = nowX + (dirX[dir]*speed);
    int nextY = nowY + (dirY[dir]*speed);
    nowX = checkRange(nextX);
    nowY = checkRange(nextY);

    //fireBallCoord[nowX][nowY].push_back({{mass, speed}, dir});
    temp[nowX][nowY].push_back({{mass,speed},dir});
}

void splitFireBall(int x, int y){
    auto fireBalls = temp[x][y];

    //해당 칸에 있는 모든 불들을 조합해서 쪼개야 해.
    int sumMass=0, sumSpeed=0;
    int num = fireBalls.size();
    bool allEven=true;
    bool allOdd=true;
    for(auto fireBall : fireBalls){
        sumMass+=fireBall.first.first;
        sumSpeed+=fireBall.first.second;
        if(fireBall.second%2==0 && allEven) allEven = true;
        else allEven = false;

        if(fireBall.second%2==1 && allOdd) allOdd = true;
        else allOdd = false;
    }

    int eachMass = sumMass/5; if(eachMass==0) return;
    int eachSpeed = sumSpeed/num;
    int dirList[2][4]={
        {0,2,4,6}, {1,3,5,7}
    };
    for(int i=0;i<=3;i++){
        if(allEven || allOdd) fireBallCoord[x][y].push_back({{eachMass, eachSpeed},dirList[0][i]});
        else fireBallCoord[x][y].push_back({{eachMass, eachSpeed},dirList[1][i]});
        
    }
}

void printMass(){
    long sum = 0;
    for(int i=1;i<=n;i++){
        for(int j=1; j<=n;j++){
            for(auto fireBall : fireBallCoord[i][j]) sum += fireBall.first.first;
        }
    }

    cout<<sum;
}

void solution(){
    while(k--){
        //cout<<"새롭게 시작!!\n";
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                if(fireBallCoord[i][j].size()>0){
                    //i,j에 파이어 볼들이 있어, 이런 곳만 조지면 돼.
                    int length = fireBallCoord[i][j].size();
                    for(int a=0;a<length;a++){
                        auto fireBall = fireBallCoord[i][j][a];
                        moveFireBall(fireBall, i, j);
                    }
                }
                fireBallCoord[i][j].clear();
            }
        } //1001*n^4
        //cout<<"이동 후\n";
        //이동 완료, 이동 후의 형태는 temp에 담겨있다.
        // for(int i=1;i<=n;i++){
        //     for(int j=1;j<=n;j++){
        //         if(temp[i][j].size()>0){
        //             cout<<i<<","<<j<<"에는 "<<temp[i][j].size()<<"개의 파이어볼이 있다.\n";
        //             for(auto fireBall : temp[i][j]) cout<<fireBall.first.first<<" "<<fireBall.first.second<<" "<<fireBall.second<<"\n";
        //         }

        //     }
        //     cout<<"\n";
        // }

        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                if(temp[i][j].size()>=2){
                    splitFireBall(i,j);
                }
                else if(temp[i][j].size()==1){
                    //그럼 그 하나를 옮겨줘야지 fireBallCoord에
                    fireBallCoord[i][j].push_back(temp[i][j][0]);
                }

                temp[i][j].clear();
            }
        }//n^4

        //쪼개진거 완료, 이후 형태는 fireBallCoord에 담겨있다.
        // cout<<"쪼개진 후\n";
        // for(int i=1;i<=n;i++){
        //     for(int j=1;j<=n;j++){
        //         if(fireBallCoord[i][j].size()>0){
        //             cout<<i<<","<<j<<"에는 "<<fireBallCoord[i][j].size()<<"개의 파이어볼이 있다.\n";
        //             for(auto fireBall : fireBallCoord[i][j]) cout<<fireBall.first.first<<" "<<fireBall.first.second<<" "<<fireBall.second<<"\n";
        //         }                
        //     }
        //     cout<<"\n";
        // }
    }

    printMass();
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(0);

    input();

    solution();
}