/*
초기 생각했던 잘못된 풀이
#include <string>
#include <vector>
#include <iostream>
using namespace std;

//지금 당장 드는 생각은 만약 40, 50, 40 이렇게 집이 있으면 
//50이 가장 크니까 먼저 털어버리면 40,40을 못털게 되는데, 차라리 40,40을 터는게 더 이득인 경우가 생기겠다라는거
int houseN;
int visited[1000000];
bool isOk(int n){
    //n번 인덱스 집을 털어도 되느냐 아니냐로 가보자
    if(visited[n]==1) return false;
    
    int prev = n-1;
    int next = n+1;
    if(prev<0) prev+=houseN;
    if(next>=houseN) next-=houseN;
    
    if(visited[prev]==0 && visited[next]==0) return true;
    else return false;
}

int maxMoney=0;

void dfs(int moneySum, int n, vector<int> &money){
    vector<int> possible;
    for(int i=n;i<houseN;i++){
        if(isOk(i)) possible.push_back(i);
    }
    
    if(possible.empty()){
        //종료되는 세계관
        //cout<<moneySum<<"\n";
        maxMoney = max(maxMoney, moneySum);
    }
    
    for(auto i : possible){
        visited[i]=1;
        dfs(moneySum+money[i], i, money);
        visited[i]=0;
    }
}

int solution(vector<int> money) {
    houseN = money.size();
    //int answer = 0;
    
    dfs(0,0, money);
    
    return maxMoney;
}
*/


//쉽게 가려면 그리디야. 그냥 많은 집을 선택하는게 이득이다라고 생각하는거지
//그러면 최대 100만개의 집을 두번 순회하면 돼.
//증명을 어떻게 해야할지 모르겠지만, 아닌 것 같아.

//생각을 해보니 이런 방식은 어떨까
//원형이니까 하나를 기준으로 잡는거야. 0번 인덱스 기준
//1. 0번 인덱스 집을 턴다 -> -1번과 1번 집은 못 턴다, 나머지는 이제 일렬로 만들어져서 고르면 된다.
//2. 0번 인덱스 집을 털지 않는다 -> 1번부터 -1번까지 일렬로 만들어지는거지!

//오? 그니까 0번 인덱스를 털면 2번 ~ -2번 집을 일렬로 생각하고, 안털면 1번~-1번 집을 일렬로 생각해서 최대를 구하면 되겠다? 원형이라서 되게 힘들었는데, 일렬이면 좀 간단해지지 않을까?
//일렬일때도 물론 어렵기는 한데
//1,2,3,4.....n
//O,X,?
//X,O,X,?
//X,X,? ->이거는 바보짓이지. 원형이면 연달아서 선택하지 않는게 이득일 수도 있어. 근데 일렬이잖아. 연달아 선택하지 않을 이유가 없는거야. 물론 1,4번을 선택하고 싶어서 2,3번을 연달아 X하는건 가능해. 근데 적어도 1,2번을 연달아 X하는 건 바보다.
//이 생각은 맞을까?

//어 맞아. 왜냐, 지금 일렬로 만들었다는 것은 적어도 경계를 넘어선 곳은 선택하지 않았다는 소리야.
//즉, 1번부터 시작해서 연달아 X하는 건 X를 세번하는 것과 같다는 소리야. 이건 바보짓이 확실하지

//그럼 결론이 뭐야. 우선 일렬로 만들어서 생각하는 건 옳다고 생각해.
//일렬로 만든 뒤에 행할 행위는 1번을 선택하거나, 2번을 선택하는거야.
//그럼 또 이를 제외한 일렬을 또 만들 수 있겠지
//뭔소리냐
//처음부터 가보면
/*
0~n까지 원형으로 이루어져있어. 나는 0번을 선택하면 2번부터 n-2까지 일렬로 만든 형태와
0번을 선택하지 않아서 1번 n-1까지 일렬로 만든 형태 두가지 중 최대를 고를거야.
그래서 지금부터 1번부터 n번까지 일렬일 때를 생각하려 해.
1번을 선택하면 3~n인 일렬을 또 생각하면 돼
1번을 선택하지 않으면 2번을 선택해야만 이득이야. 그래서 2번을 선택하면 4~n인 일렬을 또 생각하면 돼.

즉 dp(1,n) = max(1번 값 + dp(3,n), 2번 값 + dp(4,n))


오.. 맞는 거 같애
dp(a,b)는 뭐냐 a부터 b까지 일렬로 있을 때 이 문제 조건에 맞게 최대를 고르는 경우야
dp(a,b) = max(value a + dp(a+2, b), valaue a+1 + dp(a+3, b))

dp(a,a) = value a
dp(a,a+1) = max(value a, value a+1)
dp(a,a+2) = max(value a + vlaue a+2, value a+1)
*/

#include <string>
#include <vector>
#include <cstring>

using namespace std;

int houseN;

int dp[1000001][2];//dp[a][0] : a~houseN-2, dp[a][1] : a~houseN-1
void makeDp(vector<int> &money){
    //이렇게 가버리면, 100만*100만의 배열이 필요한데 이건 공간이 너무 과하니까 bottom-up방식이 아닌
    //top-down 을 택해보자 -> 해보긴 했는데 문제가 있다 ㅇㅇ
    dp[houseN-2][0] = money[houseN-2];
    dp[houseN-3][0] = max(money[houseN-3], money[houseN-2]);
    dp[houseN-4][0] = max(money[houseN-4]+money[houseN-2], money[houseN-3]);
    
    dp[houseN-1][1] = money[houseN-1];
    dp[houseN-2][1] = max(money[houseN-2], money[houseN-1]);
    dp[houseN-3][1] = max(money[houseN-3]+money[houseN-1], money[houseN-2]);
    
    for(int i=houseN-5; i>=0 ; i--){
        dp[i][0] = max(money[i]+dp[i+2][0], money[i+1]+dp[i+3][0]);
    }
    for(int i=houseN-4; i>=0; i--){
        dp[i][1] = max(money[i]+dp[i+2][1], money[i+1]+dp[i+3][1]);
    }
}

int getDp(int l, int r, vector<int> &money){
    //l부터 r까지 일렬로 있다고 생각했을 때의 최대는
    if(r==houseN-1 && dp[l][1]>-1) return dp[l][1];
    if(r==houseN-2 && dp[l][0]>-1) return dp[l][0];
    
    if(l>r) return 0;
    
    if(l==r){
        int value = money[l];
        if(r == houseN-1) dp[l][1] = value;
        else dp[l][0] = value;
        return value;
    }
    if(r==l+1){
        int value = max(money[l], money[l+1]);
        if(r==houseN-1) dp[l][1] = value;
        else dp[l][0] = value;
        return value;
    }
    if(r==l+2){
        int value = max(money[l]+money[l+2], money[l+1]);
        if(r==houseN-1) dp[l][1] = value;
        else dp[l][0] = value;
        return value;
    }
    //dp(a,b) = max(value a + dp(a+2, b), valaue a+1 + dp(a+3, b))
    int value = max(money[l]+getDp(l+2, r,money), money[l+1]+getDp(l+3,r,money));
    if(r==houseN-1) dp[l][1] = value;
    else dp[l][0] = value;
    return value;
}
//이 getDp에서 메모이제이션을 쓸 수 있으면 좋겠는데, 집의 개수가 너무 커서.. 100만*100만 byte의 배열을 만들수는 없잖아.
//4*(10^12) byte인데 4*(10^6)MB인거고...암튼 안돼


//이럼 이 풀이는 이 문제에 적절한 풀이가 아닌것인가!

//맞네 r의 변화는 없으니 1차원 배열 두개(r==houseN-1, houseN-2인거로 두개)를 만들어서 하면 되겠구나

int solution(vector<int> money) {
    houseN = money.size();
    
    memset(dp, -1, sizeof(dp));
    makeDp(money);
    //int answer = max(money[0] + getDp(2,houseN-2,money), getDp(1,houseN-1,money));
    int answer = max(money[0]+dp[2][0], dp[1][1]);
    return answer;
}