#include <bits/stdc++.h>

using namespace std;

void input();
void solution();
void greenMove(int x, int y, int type);
void blueMove(int x, int y, int type);
void greenRemove();
void blueRemove();

int n; //블록을 놓는 횟수
int t; //놓는 블록의 유형 1 1*1/ 2 1*2 / 3 2*1
int x, y;
vector<pair<int, pair<int, int>>> dominos;
int greenField[7][5];
int blueField[5][7];

int deletedLines=0;
int tileCnt=0;

/*
6
5
4
3
2
1
   1   2   3   4 greenField 형태

1
2
3
4
   6  5  4  3  2  1  blueField 형태

   어찌됐던 쌓이는 형태가 1부터 쌓임
*/

int main(){
    cin.tie(0);
    ios::sync_with_stdio(0);

    input();
    solution();
}

void input(){
    cin>>n;

    for(int i=1;i<=n;i++){
        cin>>t>>x>>y;

        dominos.push_back({t,{x+1,y+1}});
    }
}

void solution(){
    int turn=0;
    for(auto domino : dominos){
        turn++;
        //지금 놓는 도미노
        int type = domino.first;

        int sx = domino.second.first;
        int sy = domino.second.second;

        //이게 green에게는 어떻게 가고, red에게는 어떻게 가는지
        greenMove(sx, sy, type);
        blueMove(sx, sy, type);

        // cout<<turn<<"번째 도미노 놓은 후 : \n";
        // cout<<"green의 형태입니다\n";
        // for(int i=6;i>=1;i--){
        //     for(int j=1;j<=4;j++){
        //         cout<<greenField[i][j]<<" ";
        //     }
        //     cout<<"\n";
        // }

        // cout<<"blue의 형태입니다\n";
        // for(int i=1;i<=4;i++){
        //     for(int j=6;j>=1;j--){
        //         cout<<blueField[i][j]<<" ";
        //     }
        //     cout<<"\n";
        // }
        

        greenRemove();
        blueRemove();

        // cout<<turn<<"지우기 과정을 거친 뒤...\n";
        // cout<<"green의 형태입니다\n";
        // for(int i=6;i>=1;i--){
        //     for(int j=1;j<=4;j++){
        //         cout<<greenField[i][j]<<" ";
        //     }
        //     cout<<"\n";
        // }

        // cout<<"blue의 형태입니다\n";
        // for(int i=1;i<=4;i++){
        //     for(int j=6;j>=1;j--){
        //         cout<<blueField[i][j]<<" ";
        //     }
        //     cout<<"\n";
        // }
        
    }
    for(int i=1;i<=4;i++){
        for(int j=1;j<=4;j++){
            if(greenField[i][j]>0) tileCnt++;
            if(blueField[i][j]>0) tileCnt++;
        }
    }

    cout<<deletedLines<<"\n"<<tileCnt;
}

void greenMove(int x, int y, int type){
    int sx;
    if(type==1){
        //이거부터 처리해보자 차근차근
        //green이기에 y좌표는 그대로 내려온다
        //x좌표를 잘 처리해야 하는데

        for(int i=6;i>=1;i--){//위에서 아래로 내려오면서 처리
            //각 층부터 계산해서
            if(greenField[i][y]==0){
                sx = i;
            }
            else{
                break;
            }
        }
        greenField[sx][y]=1;
    }

    else if(type==2){
        //놓는 좌표가 x,y / x,y+1
        for(int i=6;i>=1;i--){
            if(greenField[i][y]==0 && greenField[i][y+1]==0){
                sx = i;
            }
            else{
                break;
            }
        }
        greenField[sx][y]=1; 
        greenField[sx][y+1]=1;
    }

    else if(type==3){
        //놓는 좌표가 x,y / x+1, y
        for(int i=5;i>=1;i--){
            if(greenField[i][y]==0 && greenField[i+1][y]==0){
                sx = i;
            }
            else break;
        }

        greenField[sx][y]=1;
        greenField[sx+1][y]=1;
    }
}

void greenRemove(){

    //먼저 정상 영역에서 없앨 게 있는지 체크하고 처리
    deque<int> dq;//지울 층들
    for(int i=1;i<=4;i++){//일단 1에서 4층까지 처리 가능한 층을 q에 넣어
        bool allFull=true;
        for(int j=1;j<=4;j++){
            if(greenField[i][j]==0){
                allFull=false;
                break;
            }
        }
        if(allFull){
            dq.push_back(i);
        }
    }

    //우선 q에 넣어. 하나씩 빼면서, 이후에 내려오면서 또 층이 만들어지면 그때그때 바로바로 q에 넣고 빼서 처리하고 해야 해
    while(!dq.empty()){
        int lineNum = dq.back(); dq.pop_back();
        deletedLines++;
        //lineNum+1층부터 맨 위층까지 한칸씩 내려야 함 ㅇㅇ
        for(int i=lineNum+1; i<=6;i++){
            for(int j=1;j<=4;j++){
                greenField[i-1][j] = greenField[i][j];
                greenField[i][j]=0;
                
            }
        }

        //lineNum이 큰 순서대로 지금 처리하기에 현재 기준 4층만 검사하면 돼
        bool allFull= true;
        for(int j=1;j<=4;j++){
            if(greenField[4][j]==0){
                allFull = false;
                break;
            }
        }

        if(allFull) dq.push_back(4);
    }

    //이렇게 정상 범주 안에 모든 것들을 지움
    int cnt=0;
    //삐죽 튀어나온 놈 처리
    for(int i=5;i<=6;i++){
        for(int j=1;j<=4;j++){
            if(greenField[i][j]>0){
                cnt++;
                break;
            }
        }
    }
    if(cnt==0) return;
    //cnt만큼 내려버려
    //deletedLines+=cnt;
    for(int i=cnt+1;i<=6;i++){
        for(int j=1;j<=4;j++){
            greenField[i-cnt][j] = greenField[i][j];
            greenField[i][j]=0;
        }
    }
}

void blueMove(int x, int y, int type){
    int sy;
    if(type==1){
        //blue기 때문에 x가 그대로 내려옴
        for(int i=6;i>=1;i--){
            if(blueField[x][i]==0){
                sy = i;
            }
            else break;
        }
        blueField[x][sy]=1;

    }

    else if(type==2){
        //놓는 좌표가 x,y / x,y+1
        for(int i=5;i>=1;i--){
            if(blueField[x][i]==0 && blueField[x][i+1]==0){
                sy = i;
            }
            else break;
        }
        blueField[x][sy]=1;
        blueField[x][sy+1]=1;
    }

    else if(type==3){
        //놓는 좌표가 x,y / x+1, y
        for(int i=6;i>=1;i--){
            if(blueField[x][i]==0 && blueField[x+1][i]==0){
                sy = i;
            }
            else break;
        }
        blueField[x][sy]=1;
        blueField[x+1][sy]=1;
    }
}

void blueRemove(){

    //먼저 정상 영역에서 없앨 게 있는지 체크하고 처리
    deque<int> dq;//지울 층들
    for(int j=1;j<=4;j++){//일단 1에서 4층까지 처리 가능한 층을 q에 넣어
        bool allFull=true;
        for(int i=1;i<=4;i++){
            if(blueField[i][j]==0){
                allFull=false;
                break;
            }
        }
        if(allFull) dq.push_back(j);
    }

    //우선 q에 넣어. 하나씩 빼면서, 이후에 내려오면서 또 층이 만들어지면 그때그때 바로바로 q에 넣고 빼서 처리하고 해야 해
    while(!dq.empty()){
        deletedLines++;
        int lineNum = dq.back(); dq.pop_back();
        //lineNum+1층부터 맨 위층까지 한칸씩 내려야 함 ㅇㅇ
        for(int j=lineNum+1; j<=6;j++){
            for(int i=1;i<=4;i++){
                blueField[i][j-1] = blueField[i][j];
                blueField[i][j]=0;
            }
        }

        //lineNum이 큰 순서대로 지금 처리하기에 현재 기준 4층만 검사하면 돼
        bool allFull= true;
        for(int j=1;j<=4;j++){
            if(blueField[j][4]==0){
                allFull = false;
                break;
            }
        }

        if(allFull) dq.push_back(4);
    }

    //이렇게 정상 범주 안에 모든 것들을 지움
    int cnt=0;
    //삐죽 튀어나온 놈 처리
    for(int j=5;j<=6;j++){
        for(int i=1;i<=4;i++){
            if(blueField[i][j]>0){
                cnt++;
                break;
            }
        }
    }
    if(cnt==0) return;
    //deletedLines+=cnt;
    //cnt만큼 내려버려
    for(int j=cnt+1;j<=6;j++){
        for(int i=1;i<=4;i++){
            blueField[i][j-cnt] = blueField[i][j];
            blueField[i][j]=0;
        }
    }
}