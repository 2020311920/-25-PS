#include <bits/stdc++.h>

using namespace std;

int negative[51];
int zero[51];
int positive[51];
int one[51];

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n_ind=0, z_ind=0, p_ind=0;
    int one_ind=0;
    int n;
    cin>>n;
    for(int i=1;i<=n;i++){
        int num;
        cin>>num;

        if(num>0){
            if(num==1) one[one_ind++]=num;
            else positive[p_ind++]=num;
        }
        else if(num<0) negative[n_ind++]=num;
        else zero[z_ind++] = num;
    }

    sort(negative, negative+n_ind);
    sort(positive, positive+p_ind);

    int ans=0;
    
    if(n_ind>0 && n_ind%2==0){
        //음수가 존재하는데 짝수개? 그럼 걍 곱해주면 돼
        for(int i=0;i<=n_ind-1;i+=2){
            ans += (negative[i]*negative[i+1]);
        }
    }
    else if(n_ind>0 && n_ind%2!=0){
        //이때 0의 존재가 활약하는거임
        if(z_ind>0){
            //일단 0이 존재한다면 남는 하나를 걍 처리할 수 있어 즉, 짝수개인 것처럼 해도 무관
            for(int i=0;i<n_ind-1;i+=2){
                ans += (negative[i]*negative[i+1]);
            }
        }

        //근데 0이 없다면? 짝을 지어서 하다가, 나머지는 제일 작은놈은 그냥 해야지 뭐
        else{
            for(int i=0;i<n_ind-1;i+=2){
                ans += (negative[i]*negative[i+1]);
            }
            ans+=negative[n_ind-1];
        }
    }

    if(p_ind%2==0){
        for(int i=p_ind-1; i>=1; i-=2){
            ans += (positive[i]*positive[i-1]);
        }
    }
    else if(p_ind%2!=0){
        for(int i=p_ind-1; i>1; i-=2){
            ans += (positive[i]*positive[i-1]);
        }

        ans+=positive[0];
    }
    
    cout<<ans+one_ind;

}