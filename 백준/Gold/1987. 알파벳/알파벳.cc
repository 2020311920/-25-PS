#include <bits/stdc++.h>

using namespace std;

int r,c;
int field[21][21];
int dist[21][21];
int dirX[4]={0,0,1,-1};
int dirY[4]={1,-1,0,0};

void input(){
    cin>>r>>c;

    for(int i=1;i<=r;i++){
        string str;
        cin>>str;
        for(int j=1;j<=c;j++){
            field[i][j] = str[j-1];
        }
    }
}

void printDist(){
    for(int i=1;i<=r;i++){
        for(int j=1;j<=c;j++){
            cout<<dist[i][j]<<" ";
        }
        cout<<"\n";
    }
}

//아래에 사용될 pq에 들어가는 pair안에 단순 int만 있는게 아니라서 필요할 것 같다는 생각에 만든다
struct cmp{
    bool operator()(const pair<int, pair<array<int, 26>, pair<int, int>>>& s1, const pair<int, pair<array<int, 26>, pair<int, int>>>& s2){
        return s1.first<s2.first;
    }
};

void dfs(){
    int maxAns=1;
    int sx=1; int sy=1;
    int cnt=1;
    
    priority_queue<pair<int, pair<array<int, 26>,pair<int, int>>>, vector<pair<int, pair<array<int, 26>, pair<int, int>>>>, cmp> pq;
    
    //dist[sx][sy]=1;
    //unordered_map<int, int> prev;
    array<int, 26> prev;
    for(int i=0;i<26;i++) prev[i]=0;
    //prev[field[sx][sy]-'A'] = 1;
    pq.push({cnt,{prev,{sx,sy}}});
    

    while(!pq.empty()){
        int sx = pq.top().second.second.first;
        int sy = pq.top().second.second.second;
        int val = pq.top().first;
        auto prev = pq.top().second.first;
        pq.pop();

        //cout<<"현재pq에서 뽑은 위치 : "<<sx<<","<<sy<<"로"<<char(field[sx][sy])<<"을 들렀다고 표시된상태입니다\n";

        //pq에 넣으면서 위치를 기록하면 안되고 뽑으면서 해당 경로를 확정지어야 겠다
        prev[field[sx][sy]-'A']=1;

        if(val>maxAns) maxAns = val;

        // if(val != dist[sx][sy]){
        //     //뽑는 값이 이미 갱신된 값과 다르다는 것은 이미 노후화한 놈
        //     continue;
        // }
        //이렇게 그냥 패스할 수는 없지. 왜냐하면, 이전보다 해당 칸에 적은 누적칸으로 왔어도, 여기서 끝까지 가면 최대가 달라질 수 있으니까... 

        

        for(int i=0;i<4;i++){
            int nx = sx+dirX[i];
            int ny = sy+dirY[i];

            if(nx>=1 && nx<=r && ny>=1 && ny<=c){
                if(prev[field[nx][ny]-'A']==1){
                    //이미 지나온 거니까 패스
                }
                else{
                    //이러면 갈 수 있다는 곳
                    // //이미 이전에 들렀을 수도 있어서, 
                    // if(dist[nx][ny]<val+1){
                    //     //이미 더 많이 지나갔던 칸이 아니므로 업데이트 필요
                    //     dist[nx][ny] = val+1;
                    //     prev[field[sx][sy]] = 1;
                    //     pq.push({val+1, {prev, {nx, ny}}});
                        
                    // }

                    //pop할 때 미리 패스하지 못하는 것과 마찬가지로, 가능한 경우라면 일단 가능세계로 넣어줘야 해
                    pq.push({val+1,{prev, {nx,ny}}});
                    //cout<<nx<<","<<ny<<"는"<<char(field[nx][ny])<<"로 들른 적이 없기에 이동하는 경우를 pq에 넣습니다\n";
                }
            }
        }
    }
    //printDist();
    cout<<maxAns;
}

void solution(){
    dfs();
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    input();
    solution();
}