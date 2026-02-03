#include <bits/stdc++.h>

using namespace std;

int n;
unordered_map<long long, int> nums;
vector<long long> v;
unordered_map<long long, bool> goodNums;

void input(){
    cin>>n;
    for(int i=1;i<=n;i++){
        int num;
        cin>>num;
        auto it = nums.find(num);
        if(it!=nums.end()){
            nums[num] = it->second + 1;
        }
        else{
            nums[num]=1;
        }
        v.push_back(num);
    }
}

void solution(){
    int cnt=0;
    sort(v.begin(), v.end());
    for(int i=0;i<=n-1;i++){
        int target = v[i];
        int l = 0; int r = n-1;
        while(l<r){
            if(l==i){
                l++;
                continue;
            }
            if(r==i){
                r--;
                continue;
            }

            if(v[l]+v[r]==target){
                cnt++;
                break;
            }
            else if(v[l]+v[r]<target){
                l++;
            }
            else if(v[l]+v[r]>target){
                r--;
            }

        }
    }

    cout<<cnt;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    input();
    solution();
}