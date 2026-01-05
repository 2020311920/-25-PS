#include <bits/stdc++.h>

using namespace std;

int n;
vector<pair<int, int>> plan;
int ans = 0;
int temp = 0;
void dfs(int i){
    //현재 0번을 수행한다.
    int t = plan[i].first;
    //cout<<i+1<<"일차 업무를 수행하려고 합니다.\n";
    if(i+t<=n){
        temp += plan[i].second;
        //cout<<i+1<<"일차 업무를 수행해서 "<<plan[i].second<<"만큼을 get ->"<<temp<<"만큼 범\n";
    }
    else{
        //cout<<i+1<<"일차 업무를 마지막으로 종료합니다. 지금까지 총 "<<temp<<"만큼 범\n";
        //이때 해당 시나리오가 종료
        //이전 temp가 해당 시나리오 수익
        if(temp>ans) ans = temp;
        //cout<<"\n";
        return;
    }

    // i+t번째부터 차례로 할 지 말 지를 차례대로 시나리오 돌려야 함
    int now = i+t;
    while(now < n){
        int temptemp = temp;
        //cout<<now+1<<"일차 업무 수행이 가능할 지 테스트합니다.\n";
        dfs(now);
        now++;
        temp = temptemp;
        
    }

    //여기까지 도착해도 해당 시나리오가 종료
    if(temp>ans) ans =temp;
    //cout<<"\n";
    return;
}

int main(){
    cin>>n;

    for(int i=1;i<=n;i++){
        int t,p;
        cin>>t>>p;
        plan.push_back(make_pair(t,p));
    }

    for(int i=1;i<=n;i++){
        temp=0;
        dfs(i-1);

    }

    cout<<ans;
}