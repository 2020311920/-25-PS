#include <bits/stdc++.h>

using namespace std;

void input();
void solution();

int n,m,nowFuel;
int field[21][21];
pair<int, int> taxi;
vector<pair<pair<int, int>, pair<int, int>>> customers;
int clearCus = 0;

int dirX[4]={0,1,0,-1};
int dirY[4]={1,0,-1,0};

int main(){
    // cin.tie(0);
    // ios::sync_with_stdio(0);

    input();
    solution();
}

void input(){
    cin>>n>>m>>nowFuel;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cin>>field[i][j];
        }
    }

    cin>>taxi.first>>taxi.second;

    for(int i=1;i<=m;i++){
        pair<int, int> customer;
        pair<int, int> goal;
        cin>>customer.first>>customer.second;
        cin>>goal.first>>goal.second;

        customers.push_back({{customer.first, customer.second}, {goal.first, goal.second}});
    }
    sort(customers.begin(), customers.end());//정렬해서 손님들을 좌측 상단부터 정렬
}

void solution(){
    //모든 손님들을 다 처리할 때까지 진행인데... 도중에 실패 또는 갈 수 없거나 등등에 즉시 종료
    int clearCus=0;
    bool clear = true;
    while(clearCus!=m && clear){
        //이제 시작.
        //n*n의 지도, m명의 손님
        int visited[21][21];
        for(int i=0;i<21;i++){
            for(int j=0;j<21;j++){
                visited[i][j]=-1;
            }
        }

        queue<pair<int, int>> q;
        int sx = taxi.first; int sy = taxi.second;
        q.push({sx, sy});
        visited[sx][sy] = 0;
        

        while(!q.empty()){
            int tempX = q.front().first; int tempY = q.front().second; q.pop();

            for(int i=0;i<=3;i++){
                int nx = tempX + dirX[i];
                int ny = tempY + dirY[i];

                if(nx>=1 && nx<=n && ny>=1 && ny<=n){
                    //범위 안에 있고
                    if(visited[nx][ny]==-1){
                        //아직 탐색하지 않았고
                        if(field[nx][ny]==0){
                            //심지어 벽이 아니라면
                            visited[nx][ny] = visited[tempX][tempY]+1;
                            q.push({nx, ny});
                        }
                    }
                }
            }
        }
        //현재 택시를 기준으로 bfs 진행 - 최소거리 손님 찾기

        //현재 기준 가장 가까운 손님 찾기
        int minDist = 2000000000;
        int cusNum=-1;
        for(int i=0;i<m;i++){
            auto customer = customers[i];
            int temp = visited[customer.first.first][customer.first.second];
            if(temp>-1 && temp<minDist){
                //도착 가능한 손님이고 최소거리 갱신 가능
                minDist = temp;
                cusNum = i;
            }
        }

        //손님을 못찾았다면
        if(cusNum==-1){
            clear = false;
            break;
        }
        //여기까지 왔다면 최소거리 손님 찾은거임
        //일단 거기까지 가

        //연료가 부족하다면
        nowFuel -= minDist;
        if(nowFuel<0){
            clear = false;
            break;
        }

        //여기까지 왔다면 연료가 0 이상이고 최소거리 손님 태움
        //cout<<"최소거리 손님은 "<<cusNum<<"번째 손님입니다! 거리는 "<<visited[customers[cusNum].first.first][customers[cusNum].first.second]<<" 손님 위치로 이동했습니다! ("<<customers[cusNum].first.first <<", "<<customers[cusNum].first.second<<")\n";
        //최소거리 손님이 시작, 그 손님 목적지가 도착

        for(int i=0;i<21;i++){
            for(int j=0;j<21;j++){
                visited[i][j]=-1;
            }
        }
        sx = customers[cusNum].first.first; sy = customers[cusNum].first.second;
        //이미 큐는 비어있다
        q.push({sx,sy});
        visited[sx][sy] = 0;
        minDist = 2000000000;
        while(!q.empty()){
            int tempX = q.front().first; int tempY = q.front().second; q.pop();
            if(tempX == customers[cusNum].second.first && tempY == customers[cusNum].second.second){
                //도착지를 알아!
                minDist = visited[tempX][tempY];
                break;
            }

            for(int i=0;i<=3;i++){
                int nx = tempX + dirX[i];
                int ny = tempY + dirY[i];

                if(nx>=1 && nx<=n && ny>=1 && ny<=n){
                    //범위 안에 있고
                    if(visited[nx][ny]==-1){
                        //아직 탐색하지 않았고
                        if(field[nx][ny]==0){
                            //심지어 벽이 아니라면
                            visited[nx][ny] = visited[tempX][tempY]+1;
                            q.push({nx, ny});
                        }
                    }
                }
            }
        }

        //도착지까지 못간다면
        if(minDist==2000000000){
            clear = false;
            break;
        }

        //일단 도착지는 갈 수 있대
        nowFuel -= minDist;

        //근데 연료가 떨어졌다면?
        if(nowFuel<0){
            clear = false;
            break;
        }

        //연료도 괜찮아? 그럼 뭐 해당 손님 미션 클리어, 연료 보충
        nowFuel += (minDist*2);
        //택시좌표도 이동
        taxi.first = customers[cusNum].second.first; taxi.second = customers[cusNum].second.second;
        //손님 클리어 처리...
        //이걸 어떻게 하지? -> 얘 위치를 0,0으로 보내면 손님검색 때 무조건 -1이라서 넘어가겠네
        customers[cusNum] = {{0,0},{0,0}};
        clearCus++;

        //cout<<"해당손님 목적지("<<taxi.first<<", "<<taxi.second<<") 로 이동 완료! 거리는 "<<minDist<<"입니다 남은 연료 : "<<nowFuel<<"\n";
    }

    if(clear==false){
        //만약 실패한 경우가 있는거라면
        cout<<-1;
    }
    else{
        cout<<nowFuel;
    }
       
}