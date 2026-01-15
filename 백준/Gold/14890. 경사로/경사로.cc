#include <bits/stdc++.h>

using namespace std;

int n,l;

int field[101][101];
int cnt=0;

void input(){
    cin>>n>>l;

    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cin>>field[i][j];
        }
    }
}

void solution(){

    for(int i=1;i<=n;i++){
        //i행을 돌아볼거에요~
        int behind = 0;
        int j;
        for(j=1;j<=n;j++){
            behind++;

            //1. 평평하다

            //2. 벽이 있다
            //2-1. 그 벽이 1만 높다 vs 아니다
            if(j<n && field[i][j]<field[i][j+1]){
                if(abs(field[i][j]-field[i][j+1])==1){
                    if(behind>=l) behind=0;
                    else break;
                }
                else break;
            }

            //3. 땅이 꺼진ek
            //3-1. 그 땅이 1만 꺼진다 vs 아니다.
            if(j<n && field[i][j]>field[i][j+1]){
                if(abs(field[i][j]-field[i][j+1])==1){
                    //이때는 좀 특이함, 그 뒤를 더 봐야 해.
                    //마침 i, j+1을 포함해서 같은 높의 땅이 뒤에 l만큼 있어야 함
                    int floorCnt=0;
                    for(int k=j+1;k<=n;k++){
                        floorCnt++;
                        if(floorCnt == l) break;

                        if(k<n &&field[i][k]==field[i][k+1]){}
                        else{
                            break;
                        }
                    }   
                    if(floorCnt==l){
                        behind=-1;
                        j+=(l-1);
                    }
                    else break;
                    
                }
                else break;
            }
        }

        if(j>n){
            //cout<<"tlqkf"<<i<<"행 횡단 성공\n";
            cnt++;
        }


        //i열을 돌아볼거에요~
        behind = 0;
        for(j=1;j<=n;j++){
            behind++;

            //1. 평평하다

            //2. 벽이 있다
            //2-1. 그 벽이 1만 높다 vs 아니다
            if(j<n && field[j][i]<field[j+1][i]){
                if(abs(field[j][i]-field[j+1][i])==1){
                    if(behind>=l) behind=0;
                    else break;
                }
                else break;
            }

            //3. 땅이 꺼진ek
            //3-1. 그 땅이 1만 꺼진다 vs 아니다.
            if(j<n && field[j][i]>field[j+1][i]){
                if(abs(field[j][i]-field[j+1][i])==1){
                    //이때는 좀 특이함, 그 뒤를 더 봐야 해.
                    //마침 i, j+1을 포함해서 같은 높의 땅이 뒤에 l만큼 있어야 함
                    int floorCnt=0;
                    for(int k=j+1;k<=n;k++){
                        floorCnt++;
                        if(floorCnt == l) break;

                        if(k<n &&field[k][i]==field[k+1][i]){}
                        else{
                            break;
                        }
                    }   
                    if(floorCnt==l){
                        behind=-1;
                        j+=(l-1);
                    }
                    else break;
                    
                }
                else break;
            }
        }

        if(j>n){
            //cout<<i<<"열 성공\n";
            cnt++;
        }
    }
    cout<<cnt;

}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(0);

    input();

    solution();
}