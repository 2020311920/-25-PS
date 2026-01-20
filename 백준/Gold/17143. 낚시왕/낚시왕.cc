#include <bits/stdc++.h>

using namespace std;

int n,m,sharkNum;
int field[101][101];

struct shark{
    int x;
    int y;
    int size;
    int dir;
    int speed;
    bool alive = true;
};
shark sharks[10001];
int personCol = 0;

int dirX[5]={0,-1,1,0,0};//1위, 2아래, 3오른, 4왼
int dirY[5]={0,0,0,1,-1};

void input(){
    cin>>n>>m>>sharkNum;
    for(int i=1;i<=sharkNum;i++){
        cin>>sharks[i].x>>sharks[i].y>>sharks[i].speed>>sharks[i].dir>>sharks[i].size;
        field[sharks[i].x][sharks[i].y] = i;
    }
}

void testPrint(){
    cout<<"현상태를 출력합니다.\n";
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cout<<field[i][j]<<" ";
        }
        cout<<"\n";
    }
}

void sharkMove(){
    for(int i=1;i<=sharkNum;i++){
        //우선 살아있는 상어인지
        if(sharks[i].alive==false) continue;

        //살아있고
        int sx = sharks[i].x; int sy = sharks[i].y;
        int dir = sharks[i].dir;  int speed = sharks[i].speed;

        //speed만큼 이동
        int line;
        if(dir==1 || dir==2) line = 2*(n-1);
        else line = 2*(m-1);
        speed %= line;
        while(speed--){
            int nx = sx + dirX[dir];
            int ny = sy + dirY[dir];
            if(!(nx>=1 && nx<=n && ny>=1 && ny<=m)){
                //만약 범위를 벗어나는 거라면
                if(dir==1) dir = 2;
                else if(dir==2) dir = 1;
                else if(dir==3) dir = 4;
                else if(dir==4) dir = 3;
                //방향 반대로 해서 nx, ny 변경해줘
                nx = sx + dirX[dir];
                ny = sy + dirY[dir];
            }

            //nx, ny는 안전
            sx = nx; sy = ny;
        }

        //최종 nx, ny로 i번 상어가 이동했다는 소리
        field[sharks[i].x][sharks[i].y]=0; //원래 있던 위치는 없다고 표시
        //이동 후 는 나중에 잡아먹고 나서 표시
        sharks[i].x = sx; sharks[i].y = sy; sharks[i].dir = dir; //i번 상어의 위치와 방향 업데이트
    }

    //상어 전부 이동 완료
    //중복의 경우 잡아먹기
    //field에 상어 기입하면서 업데이트
    for(int i=1;i<=sharkNum;i++){
        //우선 살아있는 상어인지
        if(sharks[i].alive==false) continue;

        if(field[sharks[i].x][sharks[i].y]==0) field[sharks[i].x][sharks[i].y] = i;//비어있으니까
        else{
            //사이즈 비교
            if(sharks[field[sharks[i].x][sharks[i].y]].size < sharks[i].size){
                //내가 잡아먹는다
                sharks[field[sharks[i].x][sharks[i].y]].alive=false;//죽여
                field[sharks[i].x][sharks[i].y] = i;//나를 저기에 번호로 넣어
            }
            else{
                //내가 잡아먹힌다
                sharks[i].alive =false;
            }
        }

    }

    //testPrint();

    
}

void solution(){
    int sumSharkSize = 0;
    //testPrint();
    while(personCol<m){
        //m열에 도착할 때까지 돌려
        personCol++;
        for(int i=1;i<=n;i++){
            //n개의 행을 보면서
            if(field[i][personCol]>0){
                //즉시 잡아
                sumSharkSize += sharks[field[i][personCol]].size;
                //cout<<personCol<<"일때 "<<field[i][personCol]<<"번 상어를 잡아!\n";

                //잡았으니
                sharks[field[i][personCol]].alive =false;
                field[i][personCol] = 0;//필드에서 상어의 존재를 지워
                break;
            }
        }

        //사람의 낚시 종료
        sharkMove();

        //상어 이동 완료
        
        
    }

    cout<<sumSharkSize;
}

int main(){

    ios::sync_with_stdio(0);
    cin.tie(0);

    input();
    solution();

}