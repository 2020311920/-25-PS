// #include <bits/stdc++.h>

// using namespace std;

// int n; int s;
// int cost[11][11];
// int MAXINT = 2100000000;
// int dist[11];

// void input(){
//     cin>>n>>s;
//     s+=1;

//     for(int i=1;i<=n;i++){
//         for(int j=1;j<=n;j++){
//             cin>>cost[i][j];
//         }
//     }
// }

// int minTime=MAXINT;
// //시작점이 s일 때의 bit
// int bit = 1;
// int allVisitedBit = 1;

// void dfs(int visited[], int nowTime, int now){
//     bool allVisited=true;
//     int tempVisited[11];
//     for(int i=1;i<=n;i++) tempVisited[i]=visited[i];
//     for(int i=1;i<=n;i++){
//         if(visited[i]==0){
//             allVisited=false;
//             break;
//         }
//     }

//     if(allVisited==true){
//         //전부 방문한 상태이니
//         minTime = min(minTime, nowTime);
//         return;
//     }

//     for(int i=1;i<=n;i++){
//         if(i==now) continue;
//         if(nowTime+cost[now][i]>=minTime) continue;
//         tempVisited[i]=1;
//         dfs(tempVisited, nowTime+cost[now][i], i);
//         tempVisited[i]=0;
//     }
// }
// //흠.. 근데 이러면 dfs 좀 별로인거 같애. 차라리 bfs로 돌리는데 pq를 써서, 같은 곳 방문을 할 수는 있되, 
// //빠르게 다른 지점을 방문하는 경우나, 작은 경로를 위주로 먼저 파악하고, 먼저 pop됐는데, 다 방문했다면
// //무조건 그게 답일 거니까 ㅇㅇ

// void bfs(){
//     priority_queue<pair<pair<int, int>, int>, vector<pair<pair<int, int>, int>>, greater<pair<pair<int, int>, int>>> pq; //{time, where},bit //bit = 1101101 0이면 방문 안한 곳

//     pq.push({{0,s},bit});
//     dist[s]=0;

//     while(!pq.empty()){
//         //int trash;
//         //cin>>trash;
//         int time = pq.top().first.first;
//         int where = pq.top().first.second;
//         int bit = pq.top().second;
//         cout<<"누적방문 bit : "<< bitset<11>(bit)<<"\n";
//         cout<<"현재 위치 : "<<where<<" 누적 시간은 : "<<time<<"\n";
//         pq.pop();

//         if(bit == allVisitedBit){
//             minTime = time;
//             return;
//         }

//         //if(time!=dist[where]) continue;

//         for(int i=1;i<=n;i++){
//             if(i==where) continue;
//             //if(time+cost[where][i]>dist[i]) continue;
//             //i가 현위치가 아닌데 심지어 가도 이전 거리보다 짧거나 같은거라면, 일단 가보는거야 ㅇㅇ
//             int iBit = 1;
//             for(int b=i;b<n;b++) iBit = iBit<<1;
//             int newBit = bit | iBit;
//             //dist[i] = time+cost[where][i];
//             pq.push({{time+cost[where][i], i},newBit});
//             //cout<<where<<"에서 "<<i<<"로 갈거얌 bit : "<<bitset<11>(newBit)<<"\n";
//         }
//     }
// }

// void solution(){
//     //start에서 모든 곳을 다 탐색할 때까지의 최소값을 구하는거
//     // int visited[11];
//     // for(int i=1;i<=n;i++) visited[i]=0;
//     // dfs(visited, 0, s);

//     for(int i=1;i<=n;i++) dist[i]=MAXINT;

//     for(int i=1;i<n;i++){
//         allVisitedBit=allVisitedBit<<1;
//         allVisitedBit+=1;
//     }

//     for(int i=s;i<n;i++){
//         bit = bit<<1;
//     }
    
//     bfs();

//     cout<<minTime;
// }

// int main(){
//     // ios::sync_with_stdio(0);
//     // cin.tie(0);
//     input();
//     solution();
// }

//플로이드 워셜을 사용해야 하는구나
#include <bits/stdc++.h>

using namespace std;

int n, s;
int cost[11][11];
int MAXINT = 2100000000;

void input(){
    cin>>n>>s;
    s+=1;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cin>>cost[i][j];
        }
    }
}

int visited[11];
int minTime = MAXINT;

void dfs(int start, int time){
    bool allVisited = true;
    for(int i=1;i<=n;i++){
        if(visited[i]==0){
            allVisited=false;
            break;
        }
    }

    if(allVisited==true){
        minTime = min(minTime, time);
        return;
    }

    for(int i=1;i<=n;i++){
        if(visited[i]==1) continue;

        visited[i]=1;
        dfs(i, time+cost[start][i]);
        visited[i]=0;
    }
}

void solution(){
    //우회 경로가 더 이득일 수 있는 경우이기에, 애초에 i에서 j까지의 최단 경로를 한번 쫘아아악 업데이트를 해야한다
    //플로이드 워셜

    for(int k=1;k<=n;k++){
        //k는 경유점이 된다.
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                //i에서 k를 거쳐 j에 도달한다.
                if(i==j) continue;
                if(cost[i][j]>cost[i][k]+cost[k][j]) cost[i][j] = cost[i][k]+cost[k][j]; //업데이트
            }
        }
    }
    visited[s]=1;
    dfs(s,0);

    cout<<minTime;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    input();
    solution();
}