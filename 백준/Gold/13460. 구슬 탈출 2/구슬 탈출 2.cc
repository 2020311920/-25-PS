#include <bits/stdc++.h>

using namespace std;

void input();
void solution();
void dfs(int k);
void tilt(int dir);

int n,m;
//# = 35, . = 46
int field[11][11];
pair<int, int> redBall;
pair<int, int> blueBall;
pair<int, int> goal;
int minAns=11;

int dirX[4]={0,1,0,-1};
int dirY[4]={1,0,-1,0};


int main(){
    cin.tie(0);
    ios::sync_with_stdio(0);

    input();
    solution();
}

void input(){
    cin>>n>>m;

    for(int i=1;i<=n;i++){
        string str;
        cin>>str;
        int j=0;
        for(auto c : str){
            j++;
            if(c=='#') field[i][j]=-1;
            else if(c=='.') field[i][j]=0;
            else if(c=='R'){
                field[i][j]='R';
                redBall={i,j};
            }
            else if(c=='B'){
                field[i][j]='B';
                blueBall={i,j};
            }
            else if(c=='O'){
                field[i][j]=0;
                goal={i,j};
            }
        }
    }
}

void solution(){
    //10번을 상하좌우 맘대로 기울일 수 있고, 최소의 해결법을 찾아라...
    //dfs만한게 없어 보여요

    dfs(0);

    if(minAns==11) cout<<-1;
    else cout<<minAns;
}

void dfs(int k){
    //k번째 흔듭니다
    //cout<<"현재 "<<k<<"번 흔들었고, 다음을 정하기 전에 체크합니다.";
    // if(redBall.first == goal.first && redBall.second == goal.second){
    //     cout<<"빨강 탈출 성공 ";
    // }
    // if(blueBall.first == goal.first && blueBall.second == goal.second){
    //     cout<<"파랑 탈출 성공 \n";
    // }
    if(k>10 || (blueBall.first == goal.first && blueBall.second == goal.second) || k>=minAns){
        return;
    }
    if(redBall.first == goal.first && redBall.second == goal.second && !(blueBall.first == goal.first && blueBall.second == goal.second)){
        //빨강은 도착했지만, 파랑은 도착하지 못했을 때
        //즉, 이러한 조건이기에 빨강이 움직이고 만약 목적지라면 field에서 없애줘야 한다.
        // cout<<"빨강이 먼저 빠졌습니다! "<<k<<"번만에 성공!\n";
        if(k<minAns) minAns = k;
        return;
    }

    //실패 조건은 10회를 넘어간다 & 파랑이 빠진다 (먼저 빠지고 아니고는 상관없음 왜냐
    //어짜피 매 기울임마다 테스트하는데, 파랑이 빠졌다? 그럼 동시에 빠졌거나, 먼저 빠진거임)
    //성공 조건은 빨강은 빠지고, 파랑은 안빠짐

    k++;
    pair<int, int> prevRed = redBall;
    pair<int, int> prevBlue = blueBall;
    int temp[11][11];
    for(int j=1;j<=n;j++){
        for(int l=1;l<=m;l++) temp[j][l]=field[j][l];
    }
    //미리 정보 저장 dfs 이후 복구 용

    for(int i=0;i<=3;i++){
        
        
        tilt(i); //i방향으로 기울인다.
        dfs(k);
        //복구
        redBall = prevRed;
        blueBall = prevBlue;
        for(int j=1;j<=n;j++){
            for(int l=1;l<=m;l++) field[j][l]=temp[j][l];
        }
    }

}

void tilt(int dir){
    //cout<<dir<<"방향으로 기울입니다.\n";
    int redsx = redBall.first; int redsy = redBall.second;
    int bluesx = blueBall.first; int bluesy = blueBall.second;
    int rednx=redsx, redny=redsy, bluenx=bluesx, blueny=bluesy;
    do{
        redsx = rednx; redsy = redny; bluesx = bluenx; bluesy = blueny;
        //빨갱이 이동
        if(!(rednx==goal.first && redny==goal.second)){
            //아직 빨강이가 도착하지 않아야 빨강의 움직임을 체크하지 ㅇㅇ
            int tempRednx = rednx + dirX[dir];
            int tempRedny = redny + dirY[dir];  
            //일단 이게 접근 가능 영역인지 부터 ㅇㅇ
            if(tempRednx>=1 && tempRednx<=n && tempRedny >=1 && tempRedny<=m){
                //움직일 준비하고
                //미리 비워놔
                field[rednx][redny]=0;

                if(field[tempRednx][tempRedny]==0){
                    //이동이 가능하다
                    rednx = tempRednx; redny = tempRedny;

                }
                field[rednx][redny] = 'R';
                //만약 업데이트 좌표가 goal이면 field에서는 없애야 함
                if(rednx==goal.first && redny==goal.second){
                    field[rednx][redny] = 0;
                }
            }
            
        }
        //파랭이 이동
        if(!(bluenx==goal.first && blueny==goal.second)){
            //아직 파랭이가 도착하지 않아야 파랭의 움직임을 체크하지 ㅇㅇ
            int tempBluenx = bluenx + dirX[dir];
            int tempBlueny = blueny + dirY[dir];

            if(tempBluenx>=1 && tempBluenx<=n && tempBlueny >=1 && tempBlueny<=m){
                //움직일 준비하고
                //미리 비워놔
                field[bluenx][blueny]=0;

                if(field[tempBluenx][tempBlueny]==0){
                    //이동이 가능하다
                    bluenx = tempBluenx; blueny = tempBlueny;

                }
                field[bluenx][blueny] = 'B';
                //만약 업데이트 좌표가 goal이면 field에서는 없애야 함
                if(bluenx==goal.first && blueny==goal.second){
                    field[bluenx][blueny] = 0;
                }
            }
            
        }        
    }while(!(rednx==redsx && redny==redsy && bluenx==bluesx && blueny==bluesy));

    redBall = {rednx, redny}; blueBall={bluenx, blueny};

    // cout<<"기울인 결과 : \n";
    // for(int i=1;i<=n;i++){
    //     for(int j=1;j<=m;j++){
    //         cout<<field[i][j]<<" ";
    //     }
    //     cout<<"\n";
    // }
}