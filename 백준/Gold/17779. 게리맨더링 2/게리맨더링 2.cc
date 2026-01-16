#include <bits/stdc++.h>

using namespace std;

int field[21][21];

int n;

void input(){
    cin>>n;

    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cin>>field[i][j];
        }
    }
}

void firstStep(){
    int ans = 2100000000;
    

    for(int x=1;x<=n;x++){
        for(int y=1;y<=n;y++){
            //x,y가 기준점이라고 치자.
            int d1=1, d2=1;
            for(d1=1;d1<=n;d1++){
                for(d2=1;d2<=n;d2++){
                    if(1<=x && x<x+d1+d2 &&x+d1+d2<=n && 1<=y-d1 &&y-d1<y &&y<y+d2 && y+d2<=n){
                        //여기를 들어와야 d1, d2가 정해진 거임

                        int temp[21][21];
                        for(int i=1;i<=20;i++){
                            for(int j=1;j<=20;j++){
                                temp[i][j] = 0;
                            }
                        }
                        
                        //아래를 통해 경계선을 그린거임
                        for(int a=0;a<=d1;a++){
                            temp[x+a][y-a] = 5; //1번 경계선
                            temp[x+d2+a][y+d2-a] = 5;//4번 경계선
                        }
                        for(int a=0;a<=d2;a++){
                            temp[x+a][y+a] = 5;
                            temp[x+d1+a][y-d1+a]=5;
                        }



                        int tempSum[6];
                        for(int i=1;i<=5;i++) tempSum[i]=0;

                        //경계선을 다 그렸으니, 다시 전체를 순회하면서 각 번호 선거구에 맞게 매칭
                        for(int i=1;i<=n;i++){
                            for(int j=1;j<=n;j++){
                                if(temp[i][j]==0){
                                    if(1<=i && i<x+d1 && 1<=j &&j<=y && i+j < x+y) temp[i][j]=1;

                                    else if(1<=i && i<=x+d2 && y<j && j<=n && (i-j) < (x-y)) temp[i][j]=2;

                                    else if(x+d1<=i && i<=n && 1<=j && j<y-d1+d2 && (i-j) > (x-y+(2*d1))) temp[i][j]=3;

                                    else if(x+d2<i && i<=n && y-d1+d2<=j && j<=n && i+j> x+y+(2*d2)) temp[i][j]=4;

                                    else temp[i][j] = 5;
                                }

                                tempSum[temp[i][j]]+= field[i][j];
                            }
                        }

                        //이렇게 하면 싸그리 다 선거구 번호 작성 완료띠
                        sort(tempSum+1, tempSum+6);
                        int tempSub = tempSum[5]-tempSum[1];
                        if(tempSub<ans){
                            ans = tempSub;
                            // cout<<"갱신!!\n";
                            // cout<<"d1 = "<<d1<<" d2 = "<<d2<<" x = "<<x<<" y = "<<y<<"\n";
                            // for(int i=1;i<=n;i++){
                            //     for(int j=1;j<=n;j++){
                            //         cout<< temp[i][j] <<" ";
                            //     }
                            //     cout<<"\n";
                            // }
                        }
                    }
                }
            }
        }
    }

    cout<<ans;
}

void solution(){
    //1. 기준점와 경계의 길이를 정하자.
    firstStep();
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    input();

    solution();

}