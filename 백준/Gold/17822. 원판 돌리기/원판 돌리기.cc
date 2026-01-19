#include <bits/stdc++.h>

using namespace std;

int n,m,t;
deque<deque<int>> circles;
deque<int> numbers; //이 numbers가 circle에 들어간다 생각
//d 0:시계방향, 1:반시계방향

deque<pair<pair<int, int>,int>> commands; //x,d,k
int totalNumCnt=0;

int dirX[4]={0,1,0,-1};
int dirY[4]={1,0,-1,0};

void input();
void solution();
void rotateCircle(int i, int d, int k);
void controlNumbers();

int main(){
    // cin.tie(0);
    // ios::sync_with_stdio(0);

    input();
    solution();
}

void input(){
    cin>>n>>m>>t;

    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            int num;
            cin>>num;
            numbers.push_back(num); //원판에 적히는 수들은 무조건 자연수
            totalNumCnt++;
        }
        circles.push_back(numbers);
        numbers.clear();
    }
    //numbers[i][j] : i번 원판에 j번째 수

    for(int i=1;i<=t;i++){
        int x,d,k;
        cin>>x>>d>>k;

        commands.push_back({{x,d},k});
    }
}

void solution(){
    while(t--){
        auto command = commands.front(); commands.pop_front();
        
        for(int i=command.first.first; i<=n;i+=command.first.first){
            //i번 원판들을 돌릴거에용
            rotateCircle(i, command.first.second, command.second);
        }
        //다 돌렸으니 이제 숫자 작업 시간
        // cout<<"회전 한 뒤 상태 출력 :\n";
        // for(int i=1;i<=n;i++){
        //     for(int j=1;j<=m;j++){
        //         cout<<circles[i-1][j-1]<<" ";
        //     }
        //     cout<<"\n";
        // }

        controlNumbers();
        // cout<<"지우거나 작업한 뒤 상태 출력 :\n";
        // for(int i=1;i<=n;i++){
        //     for(int j=1;j<=m;j++){
        //         cout<<circles[i-1][j-1]<<" ";
        //     }
        //     cout<<"\n";
        // }

        //작업 완료
    }
    int sum=0;
    //다 회전하고 나서 답 구하기
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(circles[i-1][j-1]>0) sum+=circles[i-1][j-1];
        }
    }

    cout<<sum;

}

void rotateCircle(int i, int d, int k){
    //i번 원판을 d의 방향으로 k번 돌린다.
    if(d==0){
        //시계방향
        while(k--){
            int temp = circles[i-1].back(); circles[i-1].pop_back();
            circles[i-1].push_front(temp);
        }
        
    }
    else{
        //반시계방향
        while(k--){
            int temp = circles[i-1].front(); circles[i-1].pop_front();
            circles[i-1].push_back(temp);
        }
        
    }
}

void controlNumbers(){
    int visited[51][51];
    for(int i=0;i<=50;i++){
        for(int j=0;j<=50;j++){
            visited[i][j]=0;
        }
    }
    //원판에 수가 남아있는가 이거는 총 토탈 수의 개수를 따로 저장하고 이게 2보다 크거나 같기만 하면 된느거 아닌가
    if(totalNumCnt>0){
        //인접한 수가 같은 것을 찾는다, 이건 후보에 넣어둔다
        //이 원판 배열들을 그냥 이차원 지도라고 생각하고 bfs 돌려 걍
        //대신 끝과 처음을 잘 검색할 수 있게잉 ㅇㅇ

        queue<pair<int, int>> q;

        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                //시작점을 circles[i-1][j-1]이라고 생각하는거임
                if(visited[i][j]==0 && circles[i-1][j-1]>0){//그니까 visited인덱스와 다르게 sx sy nx ny들은 실제 deque에서의 인덱스
                    //일단 확인 안한 곳 임과 동시에 숫자가 있는 칸인거임
                    visited[i][j]=1;

                    //얘가 곧 시작점이 되어서 큐에 넣어
                    q.push({i,j});//큐에는 visited 인덱스로 들어감
                    while(!q.empty()){
                        auto start = q.front(); q.pop();
                        int sx = start.first-1; int sy = start.second-1;

                        for(int d=0;d<=3;d++){
                            int nx = sx+dirX[d];
                            int ny = sy+dirY[d];

                            if(nx>=0 && nx<n){
                                //ny는 범위를 벗어나도 사실 노 상관임 ㅇㅇ
                                if(ny<0) ny+=m;
                                else if(ny>=m) ny-=m;

                                //이렇게 nx, ny 다 범위 안으로 만들고
                                if(visited[nx+1][ny+1]==0){
                                    if(circles[sx][sy]==circles[nx][ny]){
                                        visited[nx+1][ny+1]=1;//일단 방문
                                        visited[sx+1][sy+1]=2;
                                        visited[nx+1][ny+1]=2;//지울 대상이면 2로 하자

                                        q.push({nx+1, ny+1});
                                    }
                                }
                            }
                        }
                    }
                    
                    
                }
            }
        }
        //지울 대상을 전부 잘 찾았어

        //cout<<"지울 대상을 출력하자\n";
        bool isDelete=false;
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                //cout<<visited[i][j]<<" ";
                if(visited[i][j]==2){
                    circles[i-1][j-1]=-2100000000;//지우는 행위와 동일
                    totalNumCnt--;
                    isDelete=true;
                }
            }
            //cout<<"\n";
        }

        if(!isDelete){
            //인접하면서 같은 수가 없었다는 거임
            double sum=0;
            for(auto i : circles){
                for(auto j : i){
                    if(j>0){
                        sum+=j;
                    }
                }
            }
            sum/=totalNumCnt;

            for(int i=1;i<=n;i++){
                for(int j=1;j<=m;j++){
                    if(circles[i-1][j-1]>sum) circles[i-1][j-1]-=1;
                    else if(circles[i-1][j-1]<sum) circles[i-1][j-1]+=1;
                }
            }

        }
        
    }
}