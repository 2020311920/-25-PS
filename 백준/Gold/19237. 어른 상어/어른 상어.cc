/*상어는 현재 x,y,현재 바라보는 방향, 바라보는 방향에 따른 이동 우선 순위가 존재
맨처음 자신의 냄새를 뿌린다
모든 상어 이동 후 겹치면 방출 이후 냄새를 뿌린다.
냄새는 상어가 k번 이동하면 사라진다. (상어들이 이동하고 나서 냄새가 사라진다)
1번 상어만 남기까지 몇초 걸리냐
1000초를 넘기면 -1

즉, 칸에는 "어떤 상어"가 "k내구도의 냄새"를 남겼다는 정보가 생긴다.
그리고 해당 칸에 몇번 상어가 있는지도
*/
#include <bits/stdc++.h>

using namespace std;

int n, m, k;
struct block{
    int sharkNum;
    int whoseSmell=0;
    int leftSmell=0;
};
block field[21][21]; //field[i][j].sharkNum이 0이면 그 위치에 상어는 없다.
//다만 whoseSmell과 leftSmell은 있다. 

int dirX[5]={0,-1,1,0,0};//1위, 2아래, 3왼쪽, 4오른쪽
int dirY[5]={0,0,0,-1,1};

struct shark{
    int x;
    int y;
    int nowDir;
    bool alive=true;
};

shark sharks[401]; //i번 상어는 sharks[i].x, sharks[i].y
int sharksDir[401][5][5];//i번 상어의 각 방향에 따른 우선순위 sharksDir[i][위][3]

void testPrint(){
    cout<<"상어의 위치들\n";
    for(int i=1;i<=n;i++){
        
        for(int j=1;j<=n;j++){
            cout<<field[i][j].sharkNum<<" ";
        }
        cout<<"\n";
    }

    cout<<"냄새의 주인들 위치\n";
    for(int i=1;i<=n;i++){
        
        for(int j=1;j<=n;j++){
            cout<<field[i][j].whoseSmell<<" ";
        }
        cout<<"\n";
    }
}


void input(){
    cin>>n>>m>>k;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cin>>field[i][j].sharkNum;
            if(field[i][j].sharkNum>0){
                sharks[field[i][j].sharkNum].x = i;
                sharks[field[i][j].sharkNum].y = j;
            }
        }
    }

    for(int i=1;i<=m;i++){
        cin>>sharks[i].nowDir;//각 상어의 현재방향
    }

    for(int i=1;i<=m;i++){
        for(int j=1;j<=4;j++){
            for(int l=1;l<=4;l++){
                //i번 상어의 j방향에 대한 이동방향 우선순위
                cin>>sharksDir[i][j][l];
                //i번 상어가 현재 j번 방향을 보고 있다면, [i][j][1~4]로 이후 이동방향이 결정된다.

            }
        }
    }
}

void spreadSmell(){
    for(int i=1;i<=m;i++){
        if(!sharks[i].alive) continue;
        field[sharks[i].x][sharks[i].y].whoseSmell = i;
        field[sharks[i].x][sharks[i].y].leftSmell = k;
    }
}

bool onlyAlive(){
    //1번만 남았나요?
    bool ans = true;
    for(int i=2;i<=m;i++){
        if(sharks[i].alive){
            ans = false;
            break;
        }
    }

    return ans;
}

void sharkMove(){
    for(int i=1;i<=m;i++){
        //i번 상어가 살아있나요?
        if(!sharks[i].alive) continue;
        //cout<<i<<"번 상어 살아있군요 이동시키자\n";
        //살아있군요!
        //1.인접한 칸을 우선순위 순으로 검색한다.
        bool successAdjust = false;
        for(int j=1;j<=4;j++){
            //특정한 우선순위로 탐색을 진행하다 찾으면 즉시 중단
            int tempDir = sharksDir[i][sharks[i].nowDir][j];
            int nx = sharks[i].x + dirX[tempDir];
            int ny = sharks[i].y + dirY[tempDir];

            if(nx>=1 && nx<=n && ny>=1 && ny<=n){
                //범위가 정상이고
                
                //1번 그 칸에 냄새가 없는가
                if(field[nx][ny].whoseSmell==0){
                    //cout<<i<<"번 상어를 "<<nx<<", "<<ny<<"로 옮기려해요\n";
                    //냄새가 없는 칸이 있네
                    field[sharks[i].x][sharks[i].y].sharkNum=0;
                    sharks[i].x = nx;
                    sharks[i].y = ny;
                    //field[sharks[i].x][sharks[i].y].sharkNum = i;
                    sharks[i].nowDir = tempDir;
                    successAdjust = true; //이걸 해야 냄새없는 칸으로 이동했다는 증표;
                    break; //i번 상어 냄새 없는 칸으로 이동
                }
            }
        }
        if(successAdjust) continue; //i번 상어 이동 완료;

        //헉, 냄세없는 칸이 없나봐, 그럼 다시 검색하면서 자신의 냄새 칸이라도 있는지.
        for(int j=1;j<=4;j++){
            //특정한 우선순위로 탐색을 진행하다 찾으면 즉시 중단
            int tempDir = sharksDir[i][sharks[i].nowDir][j];
            int nx = sharks[i].x + dirX[tempDir];
            int ny = sharks[i].y + dirY[tempDir];

            if(nx>=1 && nx<=n && ny>=1 && ny<=n){
                //범위가 정상이고
                
                //그 칸에 본인 냄새가 있는가.
                if(field[nx][ny].whoseSmell==i){
                    //cout<<i<<"번 상어를 "<<nx<<", "<<ny<<"로 옮기려해요\n";
                    //다행히 본인 냄새가 있는 칸이라도 있는거임
                    field[sharks[i].x][sharks[i].y].sharkNum=0;
                    sharks[i].x = nx;
                    sharks[i].y = ny;
                    //field[sharks[i].x][sharks[i].y].sharkNum = i;
                    sharks[i].nowDir = tempDir;
                    successAdjust = true;
                    break; //i번 상어 냄새 없는 칸으로 이동
                }
            }
        }

        if(successAdjust) continue;

        else{
            //진짜로 주변에 이동할만 한 곳이 없다면
            // 뭐 어쩔 수 없지 그냥 넘어가야지// 문제에 명시되어있지도 않고
            //이런 경우는 없을 것
            //cout<<i<<"번 상어가 이동에 실패했어요. 본인 자리 그대로 유지\n";
        }
    }
}

void minusSmell(){
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(field[i][j].leftSmell>0) field[i][j].leftSmell--;

            if(field[i][j].leftSmell==0) field[i][j].whoseSmell = 0;
        }
    }
}

void solution(){
    //cout<<"처음 상태 : \n";
    //testPrint();

    spreadSmell();

    int ans=0;
    while(!onlyAlive() && ans<=1000){
        //각 상어가 위치한 칸에 냄새 뿌리기
        //spreadSmell();//뭐 문제에서는 뿌리고 그때부터 이동하고 뿌린다고 했는데, 이렇게 해도 상관 없어보임

        ans++;//상어들이 ans만큼 이동
        //cout<<ans<<"번째 이동을 시작합니다.\n";
        //상어들이 동시에 이동한다.
        sharkMove();

        //모든 상어를 이동할 수 있으면 다 이동 시켰어.
        //대신 field에 이동한 뒤에 업데이트를 일부러 아직 안했어. 그래서 모든 필드에 sharkNum은 0일거야.
        //겹치는 상어는 계급에 따라 방출 진행하고 이에 따라 모든 상어들의 현재 위치를 field에도 적용
        for(int i=1;i<=m;i++){
            if(!sharks[i].alive) continue;

            if(field[sharks[i].x][sharks[i].y].sharkNum==0){
                //아직 아무도 없으니 걍 박아도 돼
                field[sharks[i].x][sharks[i].y].sharkNum = i;
                //cout<<i<<"번 상어가 아무도 없어서"<<sharks[i].x<<", "<<sharks[i].y<<"로 이동 시켰어요\n";
            }
            else{
                //이말은 누군가 이미 있음
                if(field[sharks[i].x][sharks[i].y].sharkNum>i){
                    //작을 수록 우선이니
                    //먼저 그놈을 죽여
                    sharks[field[sharks[i].x][sharks[i].y].sharkNum].alive = false;
                    field[sharks[i].x][sharks[i].y].sharkNum = i;
                }
                else{
                    //내가 죽어
                    sharks[i].alive = false;
                }
            }
        }
        

        //이제 모든 필드에 0보다 큰 leftSmell을 1씩 줄여
        minusSmell();

        //이제 현재 기준 상어들에 냄새를 뿌리는데
        spreadSmell();

        //cout<<"전부 이동 및 방출 완료 및 냄새 감소 및 추가 완료\n";
        //testPrint();
    }

    if(ans<=1000) cout<<ans;
    else cout<<-1;
}

int main(){

    // cin.tie(0);
    // ios::sync_with_stdio(0);

    input();
    solution();
}