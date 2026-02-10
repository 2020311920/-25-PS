// //모든 수가 양수이기에 그나마 쉽게 풀 수 있는 문제다
// //만약에 음수가 존재하는 수열이라면 어떻게 풀어야할지 너무 무섭네

#include <bits/stdc++.h>

using namespace std;

int n,s;
vector<int> v;

void input(){
    cin>>n>>s;

    for(int i=1;i<=n;i++){
        int num;
        cin>>num;
        v.push_back(num);
    }
}

void solution(){
    int sum=v[0];
    int minAns = 100001;
    int l=0; int r=0;
    while(l<=r && r<=n && l<=n){
        if(sum>=s){
            int length = r-l+1;
            if(length<minAns) minAns = length;

            if(minAns==1) break;
            
            if(l==r){
                sum-=v[l];
                l++;
                r++;
                if(r<=n) sum+=v[r];
                
            }
            else{
                sum-=v[l];
                l++;
            }
        }
        else if(sum<s){
            r++;
            if(r<=n) sum+=v[r];         
        }
    }

    if(minAns<100001) cout<<minAns;
    else cout<<0;
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(0);

    input();
    solution();
}

//위는 투포인터로 풀이
//아래는 누적합 배열로 가보자
// #include <bits/stdc++.h>

// using namespace std;

// int n,s;
// vector<int> v;

// void input(){
//     cin>>n>>s;
//     long long sum = 0;
//     for(int i=1;i<=n;i++){
//         long long num;
//         cin>>num;
//         sum+=num;
//         v.push_back(sum);
//     }
// }

// void solution(){
//     //v[r]-v[l]은 l+1부터 r까지의 합
//     //단 반드시 l은 r보다 작아야 함
// }

// int main(){
//     cin.tie(0);
//     ios::sync_with_stdio(0);

//     input();
//     solution();
// }