/*
아무래도 당장 든 생각은 DFS로 무식하게 풀어보는거지
매순간 두개중 하나 먹을 것이라 생각하고 푸는거야.
근데 T가 매우 큰데 a,b가 작다면 2^큰수가 돼서 금방 힘들어질 거 같다는 생각 ㅇㅇ

근데뭔가 DP로 풀면 될 것 같다는 생각이 드네..?
DP[]를 잘 정의만 하면 되겠다 싶은데

그니까 DP[n]은 n이라는 최대 포만감이 있을 때, A,B를 가지고 만드는 최대 포만감 수치
문제의 답과 정확히 동일한 규칙인거지
그래서 A=5, B=6일 때 DP[0]=0, DP[1]=0...DP[4]=0, DP[5]=5, DP[6]=6, DP[7]=6...DP[9]=6, DP[10]=10
오,, 어떤 점화식이 가능하려나
DP[n]=max(DP[n-A]+DP[A], DP[n-B]+DP[B])이거 인거지
그니까 마지막에 A또는 B를 먹어서 해당 n에 가장 가깝게 만드는 건데, n-A또는 n-B를 만드는 경우의 수를 
미리 알 수만 있으면 되는거잖아.

이렇게 해서 미리 T상항선 까지 구하면 되는거지!

그렇게 하면 예를 들어
T라는 상한선이 있어
그럼 DP[T]는 T라는 포만감이 있을 때 채울 수 있는 최대 포만감
이때의 포만감을 반으로 줄이고, T까지의 나머지를 T'이라 하자
그럼 이 T'을 또 채울 수 있을거 아니야? 이게 곧 DP[T']일거고? 
그럼 정답은 DP[T], DP[T]/2 + DP[T'] 중 더 큰 값이겠지 ㅇㅇ
물론 일반적으로 후자가 더 크기야 하겠지만, 아닐 수도 있으니까 ㅇㅇ
입력값이 7,5,6이면 그냥 6먹고 물 마시면 3이 되고 거기서 뭘 더 못하면 3이 답이되는데, 물 안마시는게 더 이득이니!
*/

//생각보다 T가 커서 이거는 bottom-up방식으로 가겠습니다잉

#include <bits/stdc++.h>

using namespace std;

int t,a,b;

void input(){
    cin>>t>>a>>b;

    if(a>b){
        swap(a,b);//a를 더 작은 값으로 유지하자
    }
}

int dp[5000001];

int getDP(int n){
    
    if(n<a){
        dp[n]=0;
        return 0;
    }
    if(dp[n]>0) return dp[n];
    if(n==a){
        dp[a]=a;
        return dp[a];
    }
    if(n==b){
        dp[b]=b;
        return dp[b];
    }

    dp[n] = max(getDP(n-a)+getDP(a), getDP(n-b)+getDP(b));
    return dp[n];
}

void makeDP(){
    for(int i=0;i<=t;i++){
        if(i<a) dp[i]=0;
        else if(i==a) dp[a]=a;
        else if(i==b) dp[b]=b;
        
        else if(i<b) dp[i] = dp[i-a]+dp[a];

        else dp[i] = max(dp[i-a]+dp[a], dp[i-b]+dp[b]);
    }
}

void solution(){
    //cout<<max(getDP(t), getDP(t)/2 + getDP(t-(getDP(t)/2)));
    makeDP();
    int ans = dp[t]; // 물을 안 마셨을 때의 최대 포만감을 기본 정답으로 둠
    
    // 도달 가능한 모든 포만감(dp[i])에서 한 번씩 다 물을 마셔보고, 언제가 제일 이득인지 찾기
    for(int i = 0; i <= t; i++){
        int current = dp[i]; // 현재 도달한 포만감
        int after_water = current / 2; // 여기서 물을 마셨을 때의 포만감
        int max_additional = dp[t - after_water]; // 남은 용량(t - after_water)으로 채울 수 있는 최대치
        
        // 가장 큰 값을 정답으로 갱신
        ans = max(ans, after_water + max_additional);
    }
    
    cout << ans;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    input();
    solution();
}