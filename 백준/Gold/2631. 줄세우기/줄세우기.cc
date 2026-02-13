#include <bits/stdc++.h>

using namespace std;

int n;
deque<int> children;
int dp[201];

void solution(){
    //DP를 활용해서 LIS를 구해보기
    for(int i=1;i<=n;i++) dp[i]=1;

    int maxLIS = 0;
    for(int i=1;i<=n;i++){
        int childInd = i;
        for(int j=1;j<i;j++){
            int tempMaxLIS=0;
            if(children[j]<children[i]){
                //어? 내가 i인데, 내 앞에 있는 j보다 크니까 증가하겠네? 그럼
                dp[i] = max(dp[j]+1, dp[i]);
            }
        }
        //이렇게 dp[i]가 확정이 돼
        if(dp[i]>maxLIS) maxLIS = dp[i];
    }    

    cout<<n-maxLIS;
}

void input(){
    cin>>n;
    children.push_back(0);//1번부터 시작하기 위해서
    for(int i=1;i<=n;i++){
        int num;
        cin>>num;
        children.push_back(num);
    }
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    input();
    solution();
}