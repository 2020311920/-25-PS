#include <bits/stdc++.h>

using namespace std;

int n;
int sum;
struct coin{
    int price;
    int num;
};
vector<coin> coins;
bool found = false;

bool compare(const coin &c1, const coin &c2){
    return c1.price>c2.price;

}

//int selected[101];

int dp[101][100001];//dp[i][j] -> i번째 코인부터 골라서 j원을 만들 수 있나요? 0 미확인, 1실패, 2성공

int dpFunc(int ind, int goal){
    if(goal==0){
        dp[ind][goal] = 2;
        return 2;
    }
    if(ind==n){
        dp[ind][goal]=1;
        return 1;
    }
    if(dp[ind][goal]==2) return 2;
    if(dp[ind][goal]==1) return 1;
    if(goal%coins[ind].price==0 && coins[ind].num >= (goal/coins[ind].price)){
        dp[ind][goal] = 2;
        return 2;
    }
    //ind번째 코인을 몇개 골랐다고 치고 
    int tempFound = 0;
    for(int i=0;i<=coins[ind].num;i++){
        if(i*coins[ind].price<=goal){
            //ind번쨰 코인을 i개 택했다고 치면
            tempFound = dpFunc(ind+1, goal-(coins[ind].price*i));
            if(tempFound==2){
                dp[ind][goal] = 2;
                break;
            }
        }
    }

    if(tempFound!=2) dp[ind][goal] = 1;
    return dp[ind][goal];
}

int possible(){
    //coins들 중에서 sum/2를 만들 수만 있다면 되는 거잖아요?
    sort(coins.begin(), coins.end(), compare);
    
    //dfs(0, 0);
    return dpFunc(0, sum/2);
}

void solution(){
    //cout<<"sum = "<<sum<<"\n";
    //cout<<selected[1]<<"\n";
    if(sum%2==0){
        if(possible()==2) cout<<1<<"\n";
        else cout<<0<<"\n";
    }
    else cout<<0<<"\n";
}

void input(){
    for(int i=1;i<=3;i++){
        memset(dp,0,sizeof(dp));
        coins.clear();
        found=false;
        sum=0;
        cin>>n;
        for(int j=1;j<=n;j++){
            int price; int num;
            cin>>price>>num;
            coins.push_back(coin{price, num});
            sum += (price*num);
            //selected[j] = num;
        }

        solution();
    }
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    input();
}