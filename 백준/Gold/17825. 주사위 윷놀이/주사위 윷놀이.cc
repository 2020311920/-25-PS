#include <bits/stdc++.h>

using namespace std;

pair<int, int> dices[11];
pair<int, int> wherePlayers[5];
vector<vector<int>> field={
    {0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40},
    {0,10,13,16,19,25,30,35,40},
    {0,20,22,24,25,30,35,40},
    {0,30,28,27,26,25,30,35,40}
};
int maxSum=0;

void input();
void solution();
void dfs(int k);

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    input();
    solution();

    cout<<maxSum;
}

void input(){
    for(int i=1;i<=10;i++){
        int num;
        cin>>num;

        dices[i] ={0,num};
    }
}

void solution(){
    //dfs로 돌릴거니까
    for(int i=1;i<=4;i++) wherePlayers[i] = {0,0};
    dfs(0);
}

void dfs(int k){
    //players들을 초기화해줄 필요가 있다.
    for(int i=1;i<=4;i++) wherePlayers[i]={0,0};
    if(k==10){
        // cout<<"하나의 케이스\n";
        // for(int i=1;i<=10;i++) cout<<dices[i].first<<" ";
        // cout<<"\n";
        int tempSum=0;
        for(int i=1;i<=10;i++){
            int who = dices[i].first;
            int what = dices[i].second;

            int sx = wherePlayers[who].first;
            int sy = wherePlayers[who].second;
            if(sy==-1) return; //이미 도착한 놈을 고른 케이스라서 ㅇㅇ

            int nx = sx; int ny = sy + what;

            if(nx==0){
                //지름길 가능성
                if(ny==5 || ny==10 || ny==15){
                    //5의 배수
                    nx = ny/5;
                    ny = 1;
                }

                else if(ny>20){
                    //도착을 가버림
                    wherePlayers[who].second = -1; //도착 처리
                    continue;
                }
                else if(ny==20){
                    nx= 2; //맨 마지막 칸은 다 다르게 인식하는 것을 막ㄱ기 위해
                    ny=7;
                }
            }
            else{
                //이미 지름길을 탄 상태
                if((nx==1 || nx==3) && ny>8){
                    wherePlayers[who].second = -1;
                    continue;
                }
                else if((nx==1 || nx==3) && ny>=5){//중앙에서 겹칠 때
                    nx = 2;
                    ny -=1;
                }
                
                else if(nx==2 && ny>7){
                    wherePlayers[who].second = -1;
                    continue;
                }
                
            }
            // cout<<who<<"가 "<<what<<"만큼 이동을 합니다. 얘는 원래 "<<sx<<","<<sy<<"에 있었고 "<<nx<<","<<ny<<"에 도착합니다\n";
            //일단 움직였다고 가정
            for(int j=1;j<=4;j++){
                if(j!=who){
                    if(wherePlayers[j].first == nx && wherePlayers[j].second == ny) return;
                }                
            }

            //고른 놈이 제대로 움직일 수 있다는 것
            tempSum += field[nx][ny];
            wherePlayers[who].first = nx; wherePlayers[who].second = ny;
        }

        //성공
        // cout<<"성공한 케이스 : \n";
        // for(int i=1;i<=10;i++) cout<<dices[i].first<<" ";
        // cout<<"\n이때의 답은"<<tempSum<<"\n";
        if(tempSum>maxSum){
            maxSum = tempSum;
            // for(int i=1;i<=10;i++) cout<<dices[i].first<<" ";
            // cout<<"\n이때의 답은"<<tempSum<<"\n";
        }
        return;
    }

    //k+1번째 다이스 결과를 누가 할 지

    for(int i=1;i<=4;i++){
        dices[k+1].first = i;
        dfs(k+1);
        dices[k+1].first = 0;
    }
}