#include <bits/stdc++.h>

using namespace std;

int n;
//int wheel[5][9];
vector<vector<int>> wheels;
vector<int> wheel;

//현재로서 드는 생각은, 우선 맞물리는 세트를 어떻게 쉽게 쉽게 파악하느냐, 
//그리고, 스핀 때마다, 어떻게 하나의 함수로 빠르게 회전 과정을 처리하느냐

/*
맞물리는건, 1번톱니 3번-2번톱니 7번, 2번톱니 3번-3번톱니 7번, 3번톱니 3번-4번톱니 7번
파악을 하는것보다는, 즉시즉시 wheel배열을 계속 교체를 해준단 마인드로
그렇다면 벡터가 굉장히 편하겠는걸?*/

void wheelSpin(int what, int dir){
    //우선 현재의 상태를 파악해서, what이 dir로 돌릴 때, 나머지는 어떻게 되는지를 
    //알게 된다면 뭐 어려울 거 없잖아. 그니까, 이 SPIN이라는 함수는 어떤 톱니를, 어떻게 돌릴지를 생각하는거야. 그니까, 입력은 1번 톱니를 시계방향으로 돌린다이지만,
    //연쇄적인 반응을 미리 계산해서 여러번 SPIN을 돌린다.

    //checkState를 만들었으니, 여기는 그냥 ㄹㅇ what 톱니바퀴를 dir방향으로 돌리면 됨
    vector<int> a = wheels[what];
    if(dir>0){
        //시계방향
        //마지막 원소만 맨 앞으로 가면 돼
        wheels[what].clear();
        wheels[what].push_back(a[7]);
        for(int i=0;i<7;i++) wheels[what].push_back(a[i]);
    }
    else if(dir<0){
        //반시계
        wheels[what].clear();
        for(int i=1;i<8;i++) wheels[what].push_back(a[i]);
        wheels[what].push_back(a[0]);
    }
}

void checkState(int what, int dir){
    //맞물리기 체크 들어갑시다잉

    int state[3]={0,0,0};

    for(int i=0;i<3;i++){
        //i i+1 check
        if(wheels[i][2]!=wheels[i+1][6]){
            state[i]=1;
            //cout<<i<<"와"<<i+1<<"이 맞물립니다!\n";
        }
    }

    int l=what, r=what;
    bool lState=true, rState=true;
    while(l>=0 || r<=3){
        //cout<<"test";
        if(l==r) wheelSpin(l, dir);//현재 위치 돌리기
        else{
            if(l>=0 && state[l]==1 && lState){
                //그렇다면 맞물린다면 돌려야지
                //l기준 l+1과의 맞물렸는가이니까, state[l]을 보면 돼
                wheelSpin(l, dir*-1);
            }
            else{
                lState=false;
            }
            if(r<=3 && state[r-1]==1 && rState){
                wheelSpin(r,dir*-1);
            }
            else{
                rState=false;
            }

            //맞물려 돌아갔기에 dir이 바뀌어야 함
            dir*=-1;
            //근데, 안맞물렸는데, 다음거가 맞물리면 돌아가게 되거덩? 이거 처리합시다.
            //한번이라도 안 맞물렸다면, 그 이후에 그 방향은 맞물리든 말든 스킵
        }
        l--;
        r++;
    }
}



int main(){
    // ios::sync_with_stdio(0);
    // cin.tie(0);

    for(int i=1;i<=4;i++){
        wheel.clear();
        string str;
        cin>>str;
        for(auto i : str) wheel.push_back(i-'0');
        wheels.push_back(wheel);
    }

    cin>>n;
    for(int i=1;i<=n;i++){
        int what;
        int dir;
        cin>>what>>dir;

        checkState(what-1, dir);

        // for(int j=0;j<=3;j++){
        //     for(auto k : wheels[j]) cout<<k<<" ";
        //     cout<<"\n";
        // }

    }

    cout<<(wheels[0][0]+wheels[1][0]*2 + wheels[2][0]*4 + wheels[3][0]*8);
}