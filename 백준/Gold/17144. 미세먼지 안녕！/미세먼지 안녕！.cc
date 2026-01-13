#include <bits/stdc++.h>

using namespace std;

int R,C,T;

int field[51][51];
int tempField[51][51]; //동시에 확산되기에, 확산 시 각 칸마다 변화되는 정도를 저장
//이후에 원래 field에 그 변화값만을 더해주면 된다.
pair<int, int> cleaner;
queue<pair<int, int>> dusts;

int dirX[4]={-1, 0, 1, 0};//1위, 2오른, 3아래, 4왼
int dirY[4]={0, 1, 0, -1};
int ans=0;

void dustMove(){
    while(!dusts.empty()){
        pair<int, int> i = dusts.front();
        dusts.pop();
        //각각의 먼지들이 전부 동시에 확산을 진행합니다.
        int amount = field[i.first][i.second]/5;

        //4방향 확산 가능성 체크
        int dirCnt=0;
        for(int j=0;j<=3;j++){
            int newX = i.first + dirX[j];
            int newY = i.second + dirY[j];
            if(newX>=1 && newX<=R && field[newX][newY]!=-1 &&newY>=1 && newY<=C){
                //확산한 방향의 위치가 정상적인 범위이면서, 공기청정기가 아니다.
                tempField[newX][newY] += amount;
                dirCnt++;
            }
        }
        //확산 가능한 방향 개수와, 변화 업데이트 완료
        tempField[i.first][i.second] -= (amount * dirCnt);
    }

    //이렇게  tempField에 변화량을 다 입력했으니
    for(int i=1;i<=R;i++){
        for(int j=1;j<=C;j++){
            field[i][j] += tempField[i][j];
            tempField[i][j] = 0; //tempField 초기화

            
        }
    }

    //이렇게 먼지 확산은 완료, 먼지 큐가 비었는데요? 어짜피 청정기 바람으로 좌표 싹 다 바뀜, 그 이후에 다시 집어넣어도 됨
}

void windMove(){
    //공기청정기 위치
    //위로 반시계 방향 시작점 : cleaner.first, 1
    //아래로 시계 방향 시작점 : cleaner.second, 1

    //밀어내는 개념이라 구현할 때는 역방향으로 끌어온다고 구현해야겠네요
    //먼저 위에서 아래로 청정기로 들어오는 방향
    
    //일단 청정기 바로 위 칸은 그냥 0이 됨
    field[cleaner.first-1][1]=0;

    for(int i=cleaner.first-2;i>=1;i--){
        //{i,1}에 먼지가 있다면... 아래로 이동
        if(field[i][1]>0){
            field[i+1][1] = field[i][1];
            field[i][1] = 0;
        }
    }

    for(int i=2;i<=C;i++){
        //{1,i}에 먼지가 있다면, 왼쪽으로 땡김
        if(field[1][i]>0){
            field[1][i-1] = field[1][i];
            field[1][i] = 0;
        }
    }

    for(int i=2;i<=cleaner.first;i++){
        //{i,C}에 먼지가 있다면 위로 땡김
        if(field[i][C]>0){
            field[i-1][C] = field[i][C];
            field[i][C] = 0;
        }
    }

    for(int i=C-1;i>=2;i--){
        //{cleaner.first, i}에 먼지가 있다면, 오른쪽으로 땡김
        if(field[cleaner.first][i]>0){
            field[cleaner.first][i+1] = field[cleaner.first][i];
            field[cleaner.first][i] = 0;
        }
    }

    //이렇게 청정기 위에서 반시계로 도는거를 역으로 땡기면서 구현 완
    //아래도 똑같이

    //우선 청정기 바로 아래는 0이 됨
    field[cleaner.second+1][1]=0;

    for(int i = cleaner.second+2;i<=R;i++){
        //{i,1}에 먼지가 있다면, 위로 땡김
        if(field[i][1]>0){
            field[i-1][1] = field[i][1];
            field[i][1] = 0;
        }
    }

    for(int i=2;i<=C;i++){
        //{R, i}에 먼지가 있다면, 왼쪽으로 땡김
        if(field[R][i]>0){
            field[R][i-1] = field[R][i];
            field[R][i] = 0;
        }
    }

    for(int i = R-1; i>=cleaner.second;i--){
        //{i, C}에 먼지가 있으면 아래로 땡겨
        if(field[i][C]>0){
            field[i+1][C] = field[i][C];
            field[i][C] = 0;
        }
    }

    for(int i=C-1;i>=2;i--){
        //{cleaner.second, i}에 먼지가 있다면, 오른쪽으로 땡겨
        if(field[cleaner.second][i]>0){
            field[cleaner.second][i+1] = field[cleaner.second][i];
            field[cleaner.second][i] = 0;
        }
    }

    //이렇게 전부 청정기 바람 이동 완료

    //이때 먼지 큐를 채워놓으면 된다~

    for(int i=1;i<=R;i++){
        for(int j=1;j<=C;j++){
            if(field[i][j]>0) dusts.push({i,j});
        }
    }
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(0);

    cin>>R>>C>>T;

    for(int i=1;i<=R;i++){
        for(int j=1;j<=C;j++){
            cin>>field[i][j];

            if(field[i][j]==-1 ){
                //공기청정기 위치로서 뭔가 체크가 필요하다.
                //먼저 입력된 공기청정기는 위로 돌고, 뒤에 입력된게 아래로 돌죠

                //j는 항상 1이거든요
                //i행에서 j가 2부터 n-1까지 돌면서 field에 >0 인 값들을 j+1로 옮기고
                //j=n이면 i-1,j로 , {i-1,j-1 ... 2}까지 값들을 {i-1,j-1}로 옮기고 
                //아무튼... 공기청정기의 i값들을 저장하겠습니다.
                cleaner = {i-1, i}; //이렇게 하면, 총 입력 받고 두번째거로 업데이트되니까 ㅇㅇ 문제없음
            }

            if(field[i][j]>0){
                dusts.push({i,j}); // 먼지들의 좌표를 저장
            }
        }
    }

    //입력을 다 받았구요.

    //1차적으로 먼지가 확산됩니다.
    //dustMove();

    // cout<<"먼지 확산 완료\n";
    // for(int i=1;i<=R;i++){
    //     for(int j=1;j<=C;j++){
    //         cout<<field[i][j]<<" ";
    //     }
    //     cout<<"\n";
    // }

    //이제 공기 청정기 바람 이동
    //windMove();

    // cout<<"청정기 바람 완료\n";
    // for(int i=1;i<=R;i++){
    //     for(int j=1;j<=C;j++){
    //         cout<<field[i][j]<<" ";
    //     }
    //     cout<<"\n";
    // }

    //테스트 완료, 이제 T초 후를 위해 while 돌리자

    while(T){
        T--; //1초 흐름
        dustMove();
        windMove();
    }  

    for(int i=1;i<=R;i++){
        for(int j=1;j<=C;j++){
            if(field[i][j]>0) ans += field[i][j];
        }
    }

    cout<<ans;
}