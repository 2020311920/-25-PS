#include <bits/stdc++.h>

using namespace std;

int n,question;
int p,q,r;
int k,v;
int MININT = 2000000000;

//int field[5001][5001];//이정도의 공간 차지는 불가피해, 왜냐 결국에는 한 점에서 모든 곳으로 가는 정보가 필요하니까
vector<pair<int, int>> field[5001];//{목적지, 경로 값}
int USADO[5001][5001];

void USADOprint(){
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cout<<USADO[i][j]<<" ";
        }
        cout<<"\n";
    }
}

void printAnswer(){
    int cnt=0;
    for(int i=1;i<=n;i++){
        if(USADO[v][i]>=k) cnt++;
    }

    cout<<cnt<<"\n";
}

void usadoSetting(){
    //start에서 모든 end를 체크하면서 둘이 같으면 패스, 0보다 커도 패스 ㅇㅇ
    //0, 즉, 아직 유사도 설정이 안됐으면, 그 end까지 타고타고 가면서 최솟값을 찾아
    for(int i=1;i<=n;i++){
        int visited[5001];
        for(int a=1;a<=n;a++) visited[a]=0;

        queue<pair<int, int>> q; //지금까지의 최소 값, 위치
        q.push({MININT,i});//i에서 시작해서 그냥 모든 동선 다 가면서 USADO 업데이트
        visited[i]=1;

        while(!q.empty()){
            int value = q.front().first;
            int s = q.front().second;
            q.pop();

            for(auto j : field[s]){
                //j.first로 가면 j.second만큼의 유사도임
                if(visited[j.first]==0){
                    visited[j.first]=1;
                    int tValue = min(value, j.second);
                    q.push({tValue, j.first});
                    if(USADO[i][j.first]==0){
                        //애초에 처음 입력되는거니까
                        USADO[i][j.first] = tValue;
                        USADO[j.first][i] = tValue;
                    }
                    else{
                        USADO[i][j.first] = min(USADO[i][j.first], tValue);
                        USADO[j.first][i] = min(USADO[i][j.first], tValue);
                    }
                }
            }
        }
        
    }

    //USADOprint();
}

void solution(){
    
    
    printAnswer();
}

void input(){

    cin>>n>>question;
   
    for(int i=1;i<=n-1;i++){
        cin>>p>>q>>r;
        //field[p][q]=r;
        field[p].push_back({q,r});
        //field[q][p]=r;
        field[q].push_back({p,r});
        USADO[p][q]=r;
        USADO[q][p]=r;
    }
    //USADOprint();

    usadoSetting();

    for(int i=1;i<=question;i++){
        cin>>k>>v;
        
        solution();
    }
}


int main(){
    //유사도 하나하나는 최대 10억이기에 자료형 조심
    //결국에는 유사도 경로의 합이 아니라, 경로들 중 최솟값이 곳 직접 경로가 된다.
    //즉, 그래프 탐색해서 그냥 a-x-x-x-b를 탐색하면 a-b가 나와버린다.

    ios::sync_with_stdio(0);
    cin.tie(0);

    input();
}