#include <bits/stdc++.h>

using namespace std;

int t,n;
//int result[10];//1+, 2-, 3''
deque<int> result;
//int nums[10]={0,1,2,3,4,5,6,7,8,9};

void dfs(int k){
    //현재 k번째 기호를 처리
    if(k==n-1){
        deque<int> nums;
        nums.push_back(1);
        for(int i=0;i<n-1;i++){
            if(result[i]==1){
                int num = nums.back(); nums.pop_back();
                num = num*10 + (i+2);
                nums.push_back(num);
            }
            else nums.push_back(i+2);
        }
        int numsInd=0;
        int tempSum=nums[numsInd];
        numsInd++;
        for(int i=0;i<n-1;i++){
            if(result[i]==1) continue;
            else if(result[i]==2){
                tempSum+=nums[numsInd];
                numsInd++;
            }
            else if(result[i]==3){
                tempSum-=nums[numsInd];
                numsInd++;
            }
        }

        if(tempSum==0){
            cout<<1;
            for(int i=0;i<n-1;i++){
                if(result[i]==2) cout<<'+'<<i+2;
                else if(result[i]==3) cout<<'-'<<i+2;
                else if(result[i]==1) cout<<' '<<i+2;
            }
            cout<<"\n";
        }
        return;
    }
    k++;
    for(int i=1;i<=3;i++){
        result.push_back(i);
        dfs(k);
        result.pop_back();
    }
}

void solution(){
    //n개의 수를 가지고 조작 들어가기
    dfs(0);
    cout<<"\n";
}

void init(){
    result.clear();
}

void input(){
    cin>>t;
    for(int i=1;i<=t;i++){
        cin>>n;
        init();
        solution();
    }
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    input();
}