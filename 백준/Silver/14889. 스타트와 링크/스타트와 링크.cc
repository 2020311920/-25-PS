#include <bits/stdc++.h>

using namespace std;

int n;
int members[21]; //팀 가르기 재귀할 때, 얘가 이미 뽑힌 애인지 아닌지 체크용
int table[21][21];

vector<int> teamA;
vector<int> teamB;

int minSub=2000000000;
//int cnt=0;

void teamColor(){
    //cnt++;
    // cout<<"팀A : ";
    // for(auto i : teamA){
    //     cout<<i<<" ";
    // }
    // cout<<"\n 팀B : ";
    // for(auto i : teamB){
    //     cout<<i<<" ";
    // }
    // cout<<"\n";

    int sumA=0;
    for(auto i : teamA){
        for(auto j : teamA){
            sumA+=table[i][j];
        }
    }

    int sumB=0;
    for(auto i : teamB){
        for(auto j : teamB){
            sumB += table[i][j];
        }
    }

    int sub = (sumA-sumB > 0 ? sumA-sumB : sumB-sumA);

    if(sub<minSub) minSub = sub;

}

void teamSplit(int k){ //k는 현재 A팀의 멤버 수
    if(k==n/2){
        for(int i=1;i<=n;i++){
            if(members[i]==0) teamB.push_back(i);
        }
        teamColor();
        teamB.clear();
        return;
    }

    for(int i=1;i<=n;i++){
        if(members[i]==0){
            if(!teamA.empty() && teamA.back()>i) continue;
            //i를 뽑겠다.
            members[i]=1;
            teamA.push_back(i);
            teamSplit(k+1);
            members[i]=0;
            teamA.pop_back();
        }
    }

}

int main(){
    cin>>n;

    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cin>>table[i][j];
        }
    }

    //입력 완료

    /*
    우선 S11, S55 이런거가 다 0이라는 것은 앞으로 팀컬러를 계산하는데에 있어
    굳이 본인을 제외한 사람들과의 조합만 계산해야한다는 불편함을 없어준다.
    
    즉, a b c팀원이 있다면 그냥 Saa,ab,ac,bb,ba,bc,cc,ca,cb 이렇게 
    다 계산해버려도 된다는거임
    
    그다음에 하나의 팀을 계산했다면, 미리 계산한 테이블의 모든 경우의 수에 따른 합에서
    빼버리면 되지 않을까라는 생각 - 은 틀림 바보야, 서로가 팀이 아닌데 그 수도 더해지니까

    편하게 계산할 수 있는 방법이 있을까... 
    일단 무식하게는
    팀을 나누고, 그걸 벡터에 넣고, 거기 수를 2중으로 순회하면서 걍 배열 값 접근해서 더하면 됨 ㅇㅇ

    그렇다면 문제는 이제 팀을 나누는 방식인데, 따지고 보면 곧 이게 핵심이 되겠다.
    계산 방식의 고민은 그 뒤에 해야겠음
    */

    //팀나누기

    //를 생각해봤는데, 팀을 나누려면 어짜피 재귀로 팀을 쪼개야 할 듯? 그럼 재귀로 쪼개면서
    //바로바로 계산하는게 맞겠다 ㅇㅇ


    teamSplit(0);
    cout<<minSub;
    //cout<<cnt;
}