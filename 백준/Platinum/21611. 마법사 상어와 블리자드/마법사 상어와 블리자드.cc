#include <bits/stdc++.h>

using namespace std;

int dirX[5]={0,-1,1,0,0};//1위, 2아래, 3왼, 4오른
int dirY[5]={0,0,0,-1,1};

int field[50][50];
int indexing[50][50];//상어가 0번이라고 치고 1번부터 길을 따라가는 인덱싱

struct block{
    int x;
    int y;
    int num;
};
block blocks[2500];

int n,m;
int sx;
int sy;
int ballCount=0;
int bombCnt[4];


struct magic{
    int dir;
    int dist;
};
magic magics[101];

void indexingInitialize();
void testPrint();

void input(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cin>>field[i][j]; //i,j에 field[i][j]번 구슬이 들어감
            if(field[i][j]>0) ballCount++;
        }
    }
    for(int i=1;i<=m;i++){
        cin>>magics[i].dir >> magics[i].dist;
    }

    indexingInitialize();
}

void destroy(int dir, int dist){
    //sx,sy부터 dir방향으로 총 dist만큼의 칸을 지워버려
    int nx = sx; int ny = sy;
    for(int i=1;i<=dist;i++){
        nx = nx + dirX[dir];
        ny = ny + dirY[dir];
        field[nx][ny] = 0;
    }
    // cout<<"파괴 완료\n";
    // testPrint();
}

void moveBalls(){
    //공백이 있으면 땡겨라
    //n*n의 필드에는 총 몇개의 block 있느냐
    int totalBlock = n*n -1;
    block temp[2500];//blocks는 이 지렁이 field에 중앙으로부터의 이동거리의 좌표들이 들어있는 값이라면, temp는 그 위치에 있는 구슬이 담긴 배열
    int tempInd=1; //temp에 담기는 구슬의 개수이자 인덱스가 되겠죠 ballCount만큼 늘어나야겠죠..
    for(int i=1;i<=totalBlock;i++){
        //blocks는 1부터 totalBlock개수만큼의 인덱스를 가지고 있고
        //blocks[i].num은 blocks[i].x, blocks[i].y에 위치한 인덱스 값,,,
        //그니까 field에 해당 좌표는 blocks[i].num번째 자리고, 그 값이 구슬의 값인거야.
        //그래서 blocks로 field의 위치를 순서대로 검색하면서 temp에는 구슬을 순서대로 넣는거지

        //근데 넣을 때, 이왕이면 땡기면서 넣는거야.
        
        if(field[blocks[i].x][blocks[i].y]>0){
            //구슬이 있는 칸인거면, 그대로 넣어주면 돼
            temp[tempInd].num = field[blocks[i].x][blocks[i].y];
            temp[tempInd].x = blocks[tempInd].x; temp[tempInd].y = blocks[tempInd].y;
            tempInd++;
        }
        else{
            //구슬이 없는 칸이라면?
            //안넣어주면 되잖아. 근데 포인트는 필드에 그 좌표에 있는 구슬 값은 넣어주돼, temp에 x,y좌표는 그 인덱스 위치로 넣어줘야 되네 ㄷㄷ
        }
        
    }

    //남은 거는 다 0으로 채워야 하거덩 현재 tempInd를 totalBlock까지
    for(int i=tempInd; i<=totalBlock; i++){
        temp[tempInd].num=0;
        temp[tempInd].x = blocks[tempInd].x; temp[tempInd].y = blocks[tempInd].y;
        tempInd++;
    }

    //이러면 아주 잘 땡겨지겠죠?
    // cout<<"떙기기 결과\n";
    // for(int i=1;i<=totalBlock;i++){
    //     field[temp[i].x][temp[i].y] = temp[i].num;
    // }
    // testPrint();
    //이때 아싸리 연속된 애들을 저장하든, 처리하든 하면 좋겠다.
    //temp를 일단 field에 복사하는 거 진행
    bool success=false;
    int prev = 0;
    int streakPoint=1;
    //검색하는 거가 prev랑 같다면, streakPoint를 1늘려
    //prev랑 다르다면, streakPoint를 1로 초기화하고, prev를 지금으로 변경해
    //근데, 그때 streaPoint가 4이상이었다면, 현재의 바로 이전을 기준으로 총 streakPoint만큼 뒤로 가며 0으로 만들어줘.
    //그걸 끝까지 가. 그걸 field에 붙여넣기 하고 지를 다시 호출해
    for(int i=1;i<=totalBlock;i++){
        field[temp[i].x][temp[i].y] = temp[i].num;
        if(temp[i].num!=prev){
            //새로운 구슬이 등장
            //일단 지금 이전까지에 4개이상 연속이었는지
            if(streakPoint>=4){
                //이럼 없애기 과정 = 폭발
                success=true;
                for(int j=1;j<=streakPoint;j++){
                    field[temp[i-j].x][temp[i-j].y] = 0;
                    bombCnt[prev]++;
                }
            }
            else{
                //걍 아무일도 없었다

            }
            prev = temp[i].num;
            streakPoint=1;

        }
        else{
            //이전거랑 같은 구슬 등장
            streakPoint++;
        }
    }

    if(success){
        //
        //cout<<"폭발 성공!\n";
        moveBalls();
    }
    else{
        // cout<<"연쇄적 폭발 최종 성공\n";
        // testPrint();
        
        //이제 복사를 하면 좋겠네.
        //이때도 temp를 쓸 수 있음 좋아서 여기서 해결하자
        //애초에 연쇄 폭발이 끝난거면 temp나 field나 동일한 상황이니까
        
        //여전히 blocks로 인덱스는 활용 가능한 상황이고
        //1번 자리부터 totalBlock번 자리까지 다시 채우면 돼.
        //1번부터 연속을 다시 체크해서, 연속이 끝나면 이전까지 연속된 수와 개수를 newInd를 늘려가며 진행
        //마찬가지로 일찍 끝나면 나머지 채우기, 이미 칸이 다차면 잘 검사하기

        int newInd=1;
        prev = field[temp[1].x][temp[1].y]; streakPoint=1;
        for(int i=2;i<=totalBlock && newInd <=totalBlock;i++){
            if(prev == temp[i].num) streakPoint++;
            else{
                //다르다면 신나게 넣으면 돼.
                int streakNum = streakPoint;
                streakPoint = 1;
                int ballNum = prev;
                prev = temp[i].num;
                field[temp[newInd].x][temp[newInd].y] = streakNum;
                newInd++;
                field[temp[newInd].x][temp[newInd].y] = ballNum;
                newInd++;
            }
        }  

        //만약 newInd가 끝이 않났다면
        for(int i=newInd;i<=totalBlock;i++){
            field[temp[i].x][temp[i].y] = 0;
        }

        // cout<<"구슬 복사 성공\n";
        // testPrint();
        return;
    }
    
}

void duplicate(){
    //구슬이 복제되는 과정
}

void solution(){
    for(int i=1;i<=m;i++){
        //총 m번의 마법을 시전
        auto magic = magics[i];
        int dir= magic.dir;
        int dist = magic.dist;

        destroy(dir, dist);

        moveBalls(); //이때 explosion도 재귀적으로 진행

        // duplicate();

    }

    cout<<bombCnt[1]+(bombCnt[2]*2)+(bombCnt[3]*3);
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(0);

    input();
    solution();
}

void indexingInitialize(){
    //indexing을 초기화하고 시퍼
    sx = (n+1)/2;
    sy = (n+1)/2;
    //왼, 아래, 오른쪽, 위, 
    //1번, 1번, 2번, 2번
    int num=0;
    indexing[sx][sy] = num;
    num++;
    int d=1;
    int nx=sx; int ny=sy;
    while(num<=(n*n)-1){
        //cout<<"진입"<<"\n";
        for(int i=1;i<=d && num<=(n*n)-1;i++){
            //왼쪽 d번
            nx = nx +dirX[3];
            ny = ny + dirY[3];
            indexing[nx][ny]=num;
            blocks[num].x = nx;
            blocks[num].y = ny;
            num++;
        }
        for(int i=1;i<=d && num<=(n*n)-1;i++){
            //아래 d번
            nx = nx+dirX[2];
            ny = ny+dirY[2];
            indexing[nx][ny]=num;
            blocks[num].x = nx;
            blocks[num].y = ny;
            num++;
            
        }
        d++;
        for(int i=1;i<=d && num<=(n*n)-1;i++){
            //오른 d+1번
            nx = nx+dirX[4];
            ny = ny+dirY[4];
            indexing[nx][ny]=num;
            blocks[num].x = nx;
            blocks[num].y = ny;
            num++;
        }
        for(int i=1;i<=d && num<=(n*n)-1;i++){
            //위로 d+1번
            nx = nx + dirX[1];
            ny = ny + dirY[1];
            indexing[nx][ny]=num;
            blocks[num].x = nx;
            blocks[num].y = ny;
            num++;
        }
        d++;

        //cout<<"탈출\n";
    }
}

void testPrint(){
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(field[i][j]==0) cout<<"  ";
            else cout<<field[i][j]<<" ";
        }
        cout<<"\n";
    }
}