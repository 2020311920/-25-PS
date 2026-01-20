#include <bits/stdc++.h>

using namespace std;

int cnt=0;
int n;
struct block{
    int num=0;
    bool added = false;
};
block field[21][21];
int maxV = 0;

int dirX[4]={0,1,0,-1};//0오른, 1아래, 2왼, 3위
int dirY[4]={1,0,-1,0};

void input(){
    cin>>n;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cin>>field[i][j].num;
        }
    }
}

void testPrint(){
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cout<<field[i][j].num<<" ";
        }
        cout<<"\n";
    }
}

void roll(int dir){
    //어느 방향이던 간, 낮은 쪽을 먼저 이동시켜야 한다...

    //dir방향으로 field를 기울인다.
    if(dir==3){
        //위로 기울이는 것
        //1,2,3,4열을 따로 봐야해
        for(int j=1;j<=n;j++){
            for(int i=1;i<=n;i++){
                if(field[i][j].num>0){
                    //i,j에 블록이 있다.
                    //얘를 갈 수 있을 때까지 간다.
                    int sx = i;
                    int sy = j;
                    int nx = sx+dirX[dir];
                    int ny = sy+dirY[dir];
                    while(nx>=1 && nx<=n && ny>=1 && ny<=n){
                        if(field[nx][ny].num==0){
                            //가는 곳이 빈 공간이다
                            int temp = field[sx][sy].num;
                            field[sx][sy].num = 0;
                            field[nx][ny].num = temp;
                            //스위치하고

                            //이때는 뭐 합쳐지고 이런게 아니라서 ㅇㅇ
                            sx = nx;
                            sy = ny;
                            nx += dirX[dir];
                            ny += dirY[dir];
                        }
                        else if(field[nx][ny].num>0){
                            //가는 곳에 블럭이 있다
                            //다르면 그냥 nx로 가지 못하고 ㅈㅈ
                            if(field[sx][sy].num != field[nx][ny].num){
                                break;
                            }
                            else{
                                //헉! 같아!
                                //그럼 최후의 조건으로 이미 합쳐진 이력이 있는지 체크
                                if(field[nx][ny].added==false && field[sx][sy].added == false){
                                    //그제서야 이동이 가능
                                    field[sx][sy].num = 0;//해당 필드에 있는 애가 사라지는거니까
                                    field[nx][ny].added = true;
                                    field[nx][ny].num *=2;

                                    break;//왜냐 합쳐진다는 것부터가 그 뒤로는 더 이동이 안되는거임
                                }
                                else break;
                            }
                        }
                    }

                    //이렇게 이동 완료
                }
            }
        }
    }
    else if(dir==1){
        //아래로 기울이는 것
        //1,2,3,4열을 따로 봐야해
        for(int j=1;j<=n;j++){
            for(int i=n;i>=1;i--){
                if(field[i][j].num>0){
                    //i,j에 블록이 있다.
                    //얘를 갈 수 있을 때까지 간다.
                    int sx = i;
                    int sy = j;
                    int nx = sx+dirX[dir];
                    int ny = sy+dirY[dir];
                    while(nx>=1 && nx<=n && ny>=1 && ny<=n){
                        if(field[nx][ny].num==0){
                            //가는 곳이 빈 공간이다
                            int temp = field[sx][sy].num;
                            field[sx][sy].num = 0;
                            field[nx][ny].num = temp;
                            //스위치하고

                            //이때는 뭐 합쳐지고 이런게 아니라서 ㅇㅇ
                            sx = nx;
                            sy = ny;
                            nx += dirX[dir];
                            ny += dirY[dir];
                        }
                        else if(field[nx][ny].num>0){
                            //가는 곳에 블럭이 있다
                            //다르면 그냥 nx로 가지 못하고 ㅈㅈ
                            if(field[sx][sy].num != field[nx][ny].num){
                                break;
                            }
                            else{
                                //헉! 같아!
                                //그럼 최후의 조건으로 이미 합쳐진 이력이 있는지 체크
                                if(field[nx][ny].added==false && field[sx][sy].added == false){
                                    //그제서야 이동이 가능
                                    field[sx][sy].num = 0;//해당 필드에 있는 애가 사라지는거니까
                                    field[nx][ny].added = true;
                                    field[nx][ny].num *=2;

                                    break;//왜냐 합쳐진다는 것부터가 그 뒤로는 더 이동이 안되는거임
                                }
                                else break;
                            }
                        }
                        
                    }

                    //이렇게 이동 완료
                }
            }
        }
    } 
    else if(dir==0){
        //오른쪽으로 기울이는 것
        //1,2,3,4행을 따로 봐야해
        for(int i=1;i<=n;i++){
            for(int j=n;j>=1;j--){
                if(field[i][j].num>0){
                    //i,j에 블록이 있다.
                    //얘를 갈 수 있을 때까지 간다.
                    int sx = i;
                    int sy = j;
                    int nx = sx+dirX[dir];
                    int ny = sy+dirY[dir];
                    while(nx>=1 && nx<=n && ny>=1 && ny<=n){
                        if(field[nx][ny].num==0){
                            //가는 곳이 빈 공간이다
                            int temp = field[sx][sy].num;
                            field[sx][sy].num = 0;
                            field[nx][ny].num = temp;
                            //스위치하고

                            //이때는 뭐 합쳐지고 이런게 아니라서 ㅇㅇ
                            sx = nx;
                            sy = ny;
                            nx += dirX[dir];
                            ny += dirY[dir];
                        }
                        else if(field[nx][ny].num>0){
                            //가는 곳에 블럭이 있다
                            //다르면 그냥 nx로 가지 못하고 ㅈㅈ
                            if(field[sx][sy].num != field[nx][ny].num){
                                break;
                            }
                            else{
                                //헉! 같아!
                                //그럼 최후의 조건으로 이미 합쳐진 이력이 있는지 체크
                                if(field[nx][ny].added==false && field[sx][sy].added == false){
                                    //그제서야 이동이 가능
                                    field[sx][sy].num = 0;//해당 필드에 있는 애가 사라지는거니까
                                    field[nx][ny].added = true;
                                    field[nx][ny].num *=2;

                                    break;//왜냐 합쳐진다는 것부터가 그 뒤로는 더 이동이 안되는거임
                                }
                                else break;
                            }
                        }
                    }

                    //이렇게 이동 완료
                }
            }
        }
    } 
    else if(dir==2){
        //왼쪽으로 기울이는 것
        //1,2,3,4행을 따로 봐야해
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                if(field[i][j].num>0){
                    //i,j에 블록이 있다.
                    //얘를 갈 수 있을 때까지 간다.
                    int sx = i;
                    int sy = j;
                    int nx = sx+dirX[dir];
                    int ny = sy+dirY[dir];
                    while(nx>=1 && nx<=n && ny>=1 && ny<=n){
                        //cout<<"여기서 걸림?";
                        if(field[nx][ny].num==0){
                            //가는 곳이 빈 공간이다
                            int temp = field[sx][sy].num;
                            field[sx][sy].num = 0;
                            field[nx][ny].num = temp;
                            //스위치하고

                            //이때는 뭐 합쳐지고 이런게 아니라서 ㅇㅇ
                            sx = nx;
                            sy = ny;
                            nx += dirX[dir];
                            ny += dirY[dir];
                        }
                        else if(field[nx][ny].num>0){
                            //가는 곳에 블럭이 있다
                            //다르면 그냥 nx로 가지 못하고 ㅈㅈ
                            if(field[sx][sy].num != field[nx][ny].num){
                                break;
                            }
                            else{
                                //헉! 같아!
                                //그럼 최후의 조건으로 이미 합쳐진 이력이 있는지 체크
                                if(field[nx][ny].added==false && field[sx][sy].added == false){
                                    //그제서야 이동이 가능
                                    field[sx][sy].num = 0;//해당 필드에 있는 애가 사라지는거니까
                                    field[nx][ny].added = true;
                                    field[nx][ny].num *=2;

                                    break;//왜냐 합쳐진다는 것부터가 그 뒤로는 더 이동이 안되는거임
                                }
                                else break;
                            }
                        }
                    }

                    //이렇게 이동 완료
                }
            }
        }
    } 
}

void dfs(int k){
    if(k==5){
        //현상황에서 최대인 값이 최대인지
        //cout<<k<<"번 움직여서 최댓값을 뽑습니다\n";
        int tempMax=0;
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                if(field[i][j].num>tempMax) tempMax = field[i][j].num;
            }
        }
        //cout<<"이 세계관에서의 최대는 "<<tempMax<<"\n";
        if(maxV<tempMax) maxV = tempMax;
        return;
    }

    k++;
    //cout<<k<<"번쨰 이동입니다.\n";
    //k번째 이동시킨다
    //매 이동마다, 모든 field에 added변수는 false로 초기화 해줘야 한다.
    //한번의 이동에서 그 부분이 작동하기에
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            field[i][j].added = false;
        }
    }
    block temp[21][21];
    for(int i=0;i<=20;i++){
        for(int j=0;j<=20;j++){
            temp[i][j] = field[i][j];
        }
    }

    for(int i=0;i<=3;i++){
        //이동 방향 선택
        //cout<<"여기서 시작\n"; testPrint();
        roll(i);
        //cout<<i<<"로 회전 "; //testPrint();
        //이동 시켰으니
        dfs(k);

        for(int j=0;j<=20;j++){
            for(int l=0;l<=20;l++){
                field[j][l] = temp[j][l];
            }
        }
    }


}

void solution(){
    dfs(0);

    //cout<<"\n"<<cnt;
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(0);

    input();
    solution();

    cout<<maxV;
}