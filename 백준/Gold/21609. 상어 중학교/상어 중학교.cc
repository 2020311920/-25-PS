#include <bits/stdc++.h>

using namespace std;

//검정 -1, 무지개 0, 나머지는 1~M
//빈 공간을 -2라고 하겠습니다.
int n,m;
int ans=0;

int field[21][21];
int dirX[4]={0,1,0,-1};
int dirY[4]={1,0,-1,0};

void input(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cin>>field[i][j];
        }
    }


}

void testPrint(){
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cout<<"[";
            if(field[i][j]==-2) cout<<" ";
            else cout<<field[i][j];
            cout<<"]";
        }
        cout<<"\n";
    }
}

bool findBlock(){
    int selected[21][21];
    for(int i=0;i<=20;i++){
        for(int j=0;j<=20;j++){
            selected[i][j]=0;
        }
    }

    int result[21][21];
    //컬러의 색으로 영역전개 해보자
    //근데 이건 일반 색들을 위주로 잡는 목적으로 쓰자, 왜냐 0번 무지개 블럭은 모두가 쓸 수 있는거라, 한명이 썼다고
    //1표시하면 꼬임    
    int maxCnt=0;
    int maxRainBow = 0;
    int resultX=0; int resultY=0;//결과물의 기준점
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(selected[i][j]==0){
                //i,j를 시작점으로 선택은 일단 가능
                selected[i][j]=1;
                //i,j를 기준점으로 하고 싶으니까 **여기를 기준점으로 한다해도, 탐색중에 위로 올라갈 수 있어 이거 어떡할래
                if(field[i][j]>0){
                    //일반 색이다! 그럼 얘를 기준으로 탐험 시작
                    //bfs를 걍 박을거다.
                    int cnt=0;
                    int rainBow=0;
                    int standardX=21; int standardY=21;
                    queue<pair<int, int>> q;
                    int visited[21][21];
                    for(int a=1;a<=n;a++){
                        for(int b=1;b<=n;b++){
                            visited[a][b]=0;
                        }
                    }
                    int color = field[i][j];
                    visited[i][j] = color;
                    q.push({i,j});
                    cnt++; //해당 블록은 넣었으니까
                    standardX=i; standardY=j;
                    //cout<<"블럭 탐색 시작\n";
                    while(!q.empty()){
                        auto now = q.front(); q.pop();
                        int sx = now.first;
                        int sy = now.second;
                        //cout<<sx<<","<<sy<<" 찾음\n";

                        for(int d=0;d<4;d++){
                            int nx = sx + dirX[d];
                            int ny = sy + dirY[d];

                            if(nx>=1 && nx<=n && ny>=1 && ny<=n){
                                if(visited[nx][ny]==0){
                                    if(field[nx][ny]==color || field[nx][ny]==0){
                                        q.push({nx,ny});
                                        cnt++;
                                        if(field[nx][ny]==0) rainBow++;
                                        else{
                                            //일반 블럭이라면 기준점이 변경되는지를 봐야 해.
                                            if(nx<standardX){
                                                standardX = nx; standardY = ny;
                                            }
                                            else if(nx==standardX && ny<standardY){
                                                standardY = ny;
                                            }
                                        }
                                        visited[nx][ny]=visited[sx][sy]; //해당컬러로 물들여
                                        selected[nx][ny] = 1; //여기는 불필요한 반복을 줄이기 위함
                                    }
                                    
                                }
                            }
                        }
                    }
                    //블럭 잘 찾는지 테스트 출력
                    // cout<<"블럭출력\n";
                    // for(int a=1;a<=n;a++){
                    //     for(int b=1;b<=n;b++){
                    //         cout<<visited[a][b]<<" ";
                    //     }
                    //     cout<<"\n";
                    // }
                    //i,j로부터 시작한 블럭 탐색이 끝났어.
                    if(cnt>maxCnt){
                        //최대사이즈 블록이 갱신되는거니까
                        maxCnt = cnt;
                        maxRainBow = rainBow;
                        resultX = standardX; resultY = standardY;
                        for(int i=0;i<=20;i++){
                            for(int j=0;j<=20;j++){
                                result[i][j]=visited[i][j];
                            }
                        }
                        //result에 저장해두자

                    }
                    //근데 크기가 같다면
                    else if(cnt==maxCnt){
                        //rainbow비교
                        if(rainBow>maxRainBow){
                            //그럼 크기 말고 무지개랑 기준점 갱신
                            maxRainBow = rainBow;
                            resultX = standardX; resultY = standardY;
                            for(int i=0;i<=20;i++){
                                for(int j=0;j<=20;j++){
                                    result[i][j]=visited[i][j];
                                }
                            }
                        }
                        else if(rainBow==maxRainBow){
                            //하필 근데 rainbow도 같다면 기준점이 큰거
                            if(standardX>resultX){
                                resultX = standardX; resultY = standardY;
                                for(int i=0;i<=20;i++){
                                    for(int j=0;j<=20;j++){
                                        result[i][j]=visited[i][j];
                                    }
                                }
                            }
                            else if(standardX==resultX && standardY>resultY){
                                resultY = standardY;
                                for(int i=0;i<=20;i++){
                                    for(int j=0;j<=20;j++){
                                        result[i][j]=visited[i][j];
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    if(maxCnt>1){
        //maxCnt는 블럭이기에 최소 2여야 함
        //그럼 그 블럭들을 전부 제거
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                if(result[i][j]>0){
                    field[i][j] = -2;
                }
            }
        }
        ans+=(maxCnt*maxCnt);
        return true;
    }
    else return false;
}

void gravity(){
    for(int j=1;j<=n;j++){
        for(int i=n;i>=1;i--){
            //field[i][j]의 i를 내릴 수 있을 때까지 내려
            //dir=1은 아래로 이동
            if(field[i][j]<0) continue;
            int sx = i; int sy = j;
            int nx = sx; int ny = sy;
            
            while(1){
                int tempX = nx+dirX[1];
                int tempY = ny+dirY[1];
                if(tempX>=1 && tempX<=n && tempY>=1 && tempY<=n){
                    if(field[tempX][tempY]==-2){
                        //마침 빈칸
                        //그럼 가야지
                        nx = tempX; ny = tempY;
                    }
                    else{
                        //빈칸이 아니면 스탑
                        break;
                    }
                    
                }
                else break;
            }

            //i,j에 있던 블록이 nx, ny로 이동했다고 생각해도 돼
            int temp = field[i][j];
            field[i][j]=-2;
            field[nx][ny] = temp;
        }
    }
}
void rotateField(){
    int tempField[21][21];
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            tempField[i][j] = field[j][n-i+1];
        }
    }

    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            field[i][j] = tempField[i][j];
        }
    }
}

void solution(){
    while(1){
        bool success = findBlock();
        //cout<<"블럭찾기\n";
        //testPrint();
        if(!success) break;

        //중력을 적용한다.
        gravity();
        //cout<<"중력적용\n";
        //testPrint();

        //90도 반시계 방향 회전
        rotateField();
        //cout<<"회전완료\n";
        //testPrint();

        gravity();
        //cout<<"중력적용\n";
        //testPrint();

        //cout<<ans<<"\n";
    }
    
    cout<<ans;

}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(0);


    input();
    solution();
}