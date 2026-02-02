#include <bits/stdc++.h>

using namespace std;

int r, c, k,w;
int field[21][21];
int temp[21][21];
int blowTemp[21][21]; //기계로 인해 매 단계 늘어나는 온도 변화
int visited[21][21];

int dirX[5]={0,0,0,-1,1};
int dirY[5]={0,1,-1,0,0};//1오른, 2왼, 3위, 4아래

int tempDir[5][3]={
    {0,0,0},
    {0,3,4},//1 오른에서 파생
    {0,3,4},//2 왼에서 파생
    {0,1,2},//3 위에서 파생
    {0,1,2}//4아래에서 파생
};

struct machine{
    int x;
    int y;
    int dir;
};
vector<machine> machines;

struct check{
    int x;
    int y;
};

vector<check> checks;

// struct wall{
//     int x;
//     int y;
//     int t;
// };
// vector<wall> walls;
unordered_map<int, bool> walls;

void input(){
    cin>>r>>c>>k;
    for(int i=1;i<=r;i++){
        for(int j=1;j<=c;j++){
            int num;
            cin>>num;
            if(num==5){
                checks.push_back(check{i,j});
            }
            else if(num>0){
                machines.push_back(machine{i,j,num});
            }
        }
    }

    cin>>w;

    for(int i=1;i<=w;i++){
        int x, y, t;
        cin>>x>>y>>t;
        if(t==0){
            walls[x*10000 + y*100 + 3] = true;
            if(x-1>=1 && x-1<=r) walls[(x-1)*10000+y*100 + 4] = true;
        }
        else if(t==1){
            walls[x*10000+y*100+1] = true;
            if(y+1>=1 && y+1<=c) walls[x*10000+(y+1)*100+2] = true;
        }
    }
}

void controlTemp(){
    //이건 모든 칸을 바탕으로 주변에 자신에게 영향 주는 변화량을 저장 후 최종적으로 field에 반영
    for(int i=1;i<=r;i++){
        for(int j=1;j<=c;j++){
            //기준이 되는 놈은 field[i][j]
            //4방향으로 본인과 대조해서 변화량 체크
            for(int ind=1;ind<=4;ind++){
                int nx = i+dirX[ind];
                int ny = j+dirY[ind];
                if(nx>=1 && nx<=r && ny>=1 && ny<=c){//범위 체크
                    //벽체크
                    auto it = walls.find(i*10000+j*100+ind); 
                    if(it==walls.end()){
                        //벽이 없다는 뜻이니까, 온도 받거나 줄 수 있다.
                        if(field[i][j]>field[nx][ny]){
                            int sub = field[i][j]-field[nx][ny];
                            sub/=4;
                            temp[i][j] -= sub;
                        }
                        else if(field[i][j]<field[nx][ny]){
                            int sub = field[nx][ny]-field[i][j];
                            sub/=4;
                            temp[i][j] +=sub;
                        }
                    }
                }
            }
        }
    }

    //이렇게 temp에 변화량을 다 저장했으니
    for(int i=1;i<=r;i++){
        for(int j=1;j<=c;j++){
            field[i][j] += temp[i][j];
            temp[i][j]=0;//temp 초기화
        }
    }
}//4(n^2)

void decrease(){
    for(int i=1;i<=r;i++){
        if(field[i][1]>0) field[i][1]--;
        if(field[i][c]>0) field[i][c]--;
    }

    for(int i=2;i<=c-1;i++){
        if(field[1][i]>0) field[1][i]--;
        if(field[r][i]>0) field[r][i]--;
    }
}//4n

bool checkAllk(){
    bool trigger = true;
    for(auto i : checks){
        if(field[i.x][i.y]<k){
            trigger = false;
            break;
        }
    }
    return trigger;
}//n^2

void windBlow(){
    for(auto i : machines){
        //각 기계들을 보며 온도 전달을 진행

        //중복 전달을 막기 위해 
        
        for(int a=1;a<=r;a++){
            for(int b=1;b<=c;b++){
                visited[a][b]=0;
            }
        }
        //현재 '나'라는 기계 위치는
        int sx = i.x;
        int sy = i.y;
        int sdir = i.dir;
        
        queue<pair<pair<int, int>, int>> q;
        //일단 한번 이동할 때 변화
        int nx = sx+dirX[sdir];
        int ny = sy+dirY[sdir];
        int value = 5;
        q.push({{nx,ny},value});
        blowTemp[nx][ny] += value;
        visited[nx][ny]=1;
        while(!q.empty()){
            auto start = q.front(); q.pop();
            if(start.second<=1) continue;
            //여기서 총 3개의 방향을 탐색
            //sdir==1 || sdir==2 -> sdir+3, sdir+4, sdir 방향으로 검색
            //sdir==3 || sdir==4 -> sdir+1, sdir+2, sdir 방향으로 검색
            //sdir+? 는 ?로 한번, sidr로 한번 이동해서 벽이 없어야 한다는 뜻
            for(int a=0;a<3;a++){
                int nextX = start.first.first+dirX[tempDir[sdir][a]];
                int nextY = start.first.second+dirY[tempDir[sdir][a]];
                //cout<<"1차 체크 "<<nextX<<","<<nextY<<"로 가는 길이 벽인지 체크\n";
                //1차 무빙 : 그대로 있거나, 대각선이 아닌 1차 벽 확인
                if(nextX>=1 && nextX<=r && nextY>=1 && nextY<=c){
                    auto it = walls.find(start.first.first*10000 + start.first.second*100+tempDir[sdir][a]);
                    if(it==walls.end()){
                        //이제 2차무빙 진행
                        //cout<<"2차 체크 "<<nextX<<","<<nextY<<"에서 이제 추가 이동\n";
                        int nnextX = nextX+dirX[sdir];
                        int nnextY = nextY+dirY[sdir];
                        if(nnextX>=1 && nnextX<=r && nnextY>=1 && nnextY<=c){
                            auto it2 = walls.find(nextX*10000+nextY*100+sdir);
                            if(it2==walls.end()){
                                //자 이래야 열 확산에 성공하는 것이야.
                                if(visited[nnextX][nnextY]==0){
                                    //아직 안한 곳이니까 여기까지 오면 이제 큐에도 넣고 visited에도 넣고, blowTemp에도 넣고!
                                    if(start.second>1){
                                        //cout<<"확산 진행! ";
                                        q.push({{nnextX,nnextY},start.second-1});
                                        blowTemp[nnextX][nnextY] += (start.second-1);
                                        visited[nnextX][nnextY]=1;
                                    }
                                    
                                }
                            }
                        }
                    }
                }
            }
        }

        // for(int i=1;i<=r;i++){
        //     for(int j=1;j<=c;j++){
        //         cout<<blowTemp[i][j]<<" ";
        //     }
        //     cout<<"\n";
        // }
    }
}

void solution(){
    int ans=0;
    windBlow();//모든 온풍기에서 바람이 한 번 나옴// 이렇게 해서 한번만 실행해서 저장
    // for(int i=1;i<=r;i++){
    //     for(int j=1;j<=c;j++){
    //         cout<<blowTemp[i][j]<<" ";
    //     }
    //     cout<<"\n";
    // }
    while(1){
        for(int i=1;i<=r;i++){
            for(int j=1;j<=c;j++){
                field[i][j] += blowTemp[i][j]; //windBlow로 인해 계산된 변화
            }
        }
        controlTemp();//온도가 조절됨
        decrease();//테두리 온도 1 감소
        ans++;
        if(ans>100) break;
        bool trigger = checkAllk();//조사할 칸들이 전부 k이상인지
        if(trigger==true) break;
        else continue;
    }

    // for(int i=1;i<=r;i++){
    //     for(int j=1;j<=c;j++){
    //         cout<<field[i][j]<<" ";
    //     }
    //     cout<<"\n";
    // }
    cout<<ans;
}

int main(){
    // ios::sync_with_stdio(0);
    // cin.tie(0);

    input();
    solution();
}