//컨베이어 시작점을 하나씩 줄인다
//시작점이 올리는 위치, 시작점 + (n-1)가 내리는 위치

#include <bits/stdc++.h>

using namespace std;

int n,k;
struct belt{
    int left;
    bool robot=false;
};
belt belts[201];

deque<int> robots; //로봇을 놓을 때마다 push_back하고 개수만큼  front부터 검색 후 pop_front하면 돼, 이동 후 다시 push_back
int beltStart = 1;
int beltEnd;
int vacantCnt=0;

void testPrint(){
    int ind = beltStart;
    // cout<<beltStart<<"~"<<beltEnd<<"\n";
    cout<<"벨트 윗부분 : ";

    while(!(ind == (beltEnd+1>2*n ? beltEnd+1-(2*n) : beltEnd+1))){
        cout<<belts[ind].left<<"[";
        if(belts[ind].robot) cout<<"R";
        else cout<<" ";
        cout<<"] ";
        ind++;
        if(ind>2*n) ind-=2*n;
    }
    cout<<"\n";
    //벨트 아랫부분도
    cout<<"벨트 딴부분 : ";
    while(!(ind == beltStart)){
        cout<<belts[ind].left<<"[";
        if(belts[ind].robot) cout<<"R]";
        else cout<<" ";
        cout<<"] ";
        ind++;
        if(ind>2*n) ind-=2*n;
    }
    cout<<"\n";
}

void beltRotate(){
    beltStart--;
    beltEnd--;
    if(beltStart<1) beltStart += 2*n;
    if(beltEnd<1) beltEnd += 2*n;


}

void robotMove(){
    int robotCnt = robots.size();
    for(int i=1;i<=robotCnt;i++){
        //모든 로봇들을 전수 조사
        //벨트 회전을 한 뒤에 실행되기에 먼저 도착위치인지 확인
        auto robot = robots.front(); robots.pop_front();
        if(robot == beltEnd){
            //이동하기 전에 이 놈이 이미 끝에 도착이면 그냥 이동도 없이 걍 pop하면 돼
            //대신 해당 위치 존재여부는 고쳐야 해
            belts[beltEnd].robot=false;
        }
        else{
            //끝이 아니라면?
            //이동을 해야지
            //이동하려는 칸에 로봇이 없어야 한다는데, 이건 그냥 먼저 올라간 로봇부터 검색하면 돼
            //먼저 올라간 놈은 상식적으로 못갈 수 가 없어, 끝까지가면 알아서 사라지기 때문에
            //그럼 이동하려는 칸의 내구도가 중요한데, 만약 이동하려는 칸이 마지막 칸이면 이동했다치고 바로 없애야 함
            int nextInd = robot+1;
            if(nextInd>2*n) nextInd-=(2*n);
            if(belts[nextInd].left>0 && belts[nextInd].robot==false){
                //그니까 이동하려는 칸이 가능한 칸이긴 한거임
                //근데 평범한 칸이냐, 끝칸이냐의 차이임
                if(nextInd == beltEnd){
                    //끝칸으로 가는거면
                    belts[robot].robot=false;
                    belts[nextInd].left--;
                    if(belts[nextInd].left == 0) vacantCnt++;
                }
                else{
                    //평범칸으로 가는거면
                    belts[robot].robot = false;
                    belts[nextInd].robot = true;
                    belts[nextInd].left--;
                    if(belts[nextInd].left == 0) vacantCnt++;
                    robots.push_back(nextInd);
                }
            }
            else{
                //이동이 불가하다.
                robots.push_back(robot);//다시 넣어주고 끝
            }
        }
    }
}


void input(){
    cin>>n>>k;
    beltEnd = n;
    for(int i=1;i<=2*n;i++){
        cin>>belts[i].left;
    }
}

void solution(){
    // cout<<"초기 상태\n";
    // testPrint();
    int ans=0;
    while(vacantCnt<k){
        ans++;
        beltRotate();
        //회전
        // cout<<"회전 진행\n";
        // testPrint();

        robotMove();
        //로봇 이동
        // cout<<"로봇들 이동 완료\n";
        // testPrint();

        if(belts[beltStart].left>0) { //올리는 위치에 올릴 수 있음 올려라.
            robots.push_back(beltStart);
            belts[beltStart].robot = true;
            belts[beltStart].left--;
            if(belts[beltStart].left==0) vacantCnt++;
        }
        //시작에 로봇 올리기
        // cout<<beltStart<<"에 내구도가 "<<belts[beltStart].left+1<<"였어서 올렸습니다.\n";
        // testPrint();
    }

    cout<<ans;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    input();
    solution();
}