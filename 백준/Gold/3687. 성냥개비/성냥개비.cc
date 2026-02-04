#include <bits/stdc++.h>

using namespace std;

int t, n;

int minArr[8]={-1, -1, 1, 7, 4, 2, 0, 8}; //minArr[n] : n개의 성냥을 쓸 때 최소의 숫자
int minArr2[10]={6,2,5,5,4,5,6,3,7,6}; //minArr2[n] : n을 만들기 위해 필요한 성냥 개수

string makeMax(){
    long long ans = 1;
    string str="1";
    int num = n;
    if(num%2==0){
        //이 말은 모든 칸을 그냥 1로 채우는게 최대
        //num/2만큼의 1을 넣음 된다
        for(int i=1;i<(num/2);i++){
            ans*=10;
            ans+=1;
            str.append("1");
        }
        return str;
    }
    else{
        //이럼 일단 num/2 -1만큼만 1을 해주고, 마지막 가장 높은 자리에 7 넣음 돼
        ans = 7;
        str = "7";
        for(int i=1;i<(num/2);i++){
            ans*=10;
            ans+=1;
            str.append("1");
        }

        return str;
    }
}

long long makeMin(){
    long long ans=1;
    //수를 만들 때 7개가 가장 많이 쓰는 경우라 7로 나눔으로서 최소로 만드는 자릿수를 알 수  있다.
    int num = n;
    if(num%7==0){
        //이러면 전부 8을 써버리는게 최소가 돼
        int k = num/7; //k자리수
        ans = 8;
        for(int i=1;i<k;i++){
            ans*=10;
            ans+=8;
        }

        return ans;
    }
    else{
        //이러면 num/7 +1 자리수가 되기에 
        //맨 앞자리부터 차례대로 넣을 수 있는 최소,
        //여기서 넣을 수 있냐라는 물음은 해당 수를 넣어, 뒤에 총 성냥 남은 개수가 커버가 되느냐
        ans = 0;
        int k = num/7 + 1;
        while(k){
            if(k==1){
                //남은 모든 성냥을 털어야 함
                if(ans==0 && num==6){
                    //하필 첫턴에 끝나는 경우인데 그때가 6개라면 
                    ans+=6;
                    break;
                }
                ans+=minArr[num];
                break;
            }
            for(int i=0;i<=9;i++){
                //0부터 9까지 넣어볼거임 단 첫 순서에서 0은 넣을 수 없음
                if(ans==0 && i==0) continue;//첫턴이면 해당 자리에 0은 들어가면 안돼
                int temp = minArr2[i];//i라는 수를 만들기 위한 성냥 수 
                if(num-temp <= 7*(k-1)){
                    ans+=i;
                    ans*=10;
                    num-=temp;
                    break;
                }
            }

            k--;
        }
        return ans;
    }

}

void solution(){
    //우선 가장 큰 수는 
    string maxV = makeMax();
    long long minV = makeMin(); 
    cout<<minV<<" "<<maxV<<"\n";
}

void input(){
    cin>>t;
    for(int i=1;i<=t;i++){
        cin>>n;
        solution();
    }
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    input();
}