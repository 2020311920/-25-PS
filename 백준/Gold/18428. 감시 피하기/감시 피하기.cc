#include <bits/stdc++.h>

using namespace std;

//사실 문제를 보자마자 이거 매번 한칸씩 검색하면 비용이 너무 비싸니까, 아예 특정열에 누가 있다 이런 식으로 접근하려 했어
/*근데 생각보다 필드의 사이즈가 좀 적긴 하네
그렇다보니 진짜 좀 많이 무식하게 장애물 놓는 걸 DFS로 돌리고 해도 될 정도이긴 하다...
근데 그렇게 풀기는 싫어*/

/*변형해서 생각을 해봤는데, 장애물을 놓아야만 하는 "범위"라는게 있을 것
이 범위들의 개수가 있을 건데, 그 범위가 다른 범위에 겹치는게 있다면 두 범위를 합칠 수도 있어보여
근데 생각보다 이 방식도 어려워 보이네..

일단 무식하게 풀어는 봅시다.*/

int n;
int field[7][7];
vector<pair<int, int>> students;

void input(){
    cin>>n;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            char ch;
            cin>>ch;
            if(ch=='X') field[i][j]=0;
            else if(ch=='S'){
                field[i][j]=1;
                students.push_back({i,j});
            }
            else if(ch=='T') field[i][j]=2;
        }
    }
}

bool isPossible = false;
int dirX[4]={0,1,0,-1};
int dirY[4]={1,0,-1,0};

bool allCovered(){
    for(auto student : students){
        int x= student.first; int y = student.second;
        //x,y로 4방향을 총총 넘어갈 때 선생님을 만나면 안되는겨
        for(int i=0;i<4;i++){
            //i번 방향 체택, 그 방향으로 끝까지 가
            int nx = x; int ny = y;
            while(nx>=1 && nx<=n && ny>=1 && ny<=n){
                if(field[nx][ny] == 2){
                    return false;
                }
                if(field[nx][ny] == 3){
                    //안전한 방향인게 확정
                    //더 이상 탐색 그만
                    break;
                }
                nx+=dirX[i];
                ny+=dirY[i];
            }
            //만약에 선생도 안만나고 장애물도 안만나고 그냥 쭈욱 갔으면 안전 방향인거
        }
    }
    return true;
}

void fieldPrint(){
    char symbol[4]={' ', 'S', 'T', 'O'};
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cout<<"["<<symbol[field[i][j]]<<"] ";
        }
        cout<<"\n";
    }
}

void dfs(int x, int y, int cnt){
    if(cnt==3){
        //fieldPrint();
        if(allCovered()) isPossible = true;
        return;
    }

    cnt++;
    //x,y부터 차례로 다음 장애물 놓을 곳을 확인하자
    while(x>=1 && x<=n && isPossible==false){
        if(field[x][y]==0){
            //장애물을 일단 놓을 수는 있는 위치여야 놓아보든 하죠 ㅇㅇ
            field[x][y]=3;
            dfs(x,y,cnt);
            field[x][y]=0;
        }
        y+=1;
        if(y>n){
            x+=1;
            y=1;
        }
    }

    return;
}//제대로 짠 DFS 맞겠지? 

void solution(){
    dfs(1,1,0);

    if(isPossible) cout<<"YES";
    else cout<<"NO";
}

int main(){
    // ios_base::sync_with_stdio(0);
    // cin.tie(0); cout.tie(0);

    input();
    solution();
}