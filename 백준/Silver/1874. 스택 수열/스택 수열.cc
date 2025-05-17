#include <bits/stdc++.h>

using namespace std;

int n;
stack<int> s;
int cnt=1;
vector<char> ans;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    s.push(0);
    cin>>n;

    for(int i=1;i<=n;i++){
        int num;
        cin>>num;
        while(s.top()!=num && cnt<=n+1){
            //사용자 입력한 수가 s.top에 존재하는가?
            //s.top을 비어있을 때는 할 수 없으니까, 미리 0을 넣어둔다.

            s.push(cnt);
            ans.push_back('+');
            cnt++;
        }
        
        //이제는 찾았겠지 아니면 이미 다 n까지 넣어봤거나
        if(s.top()==num){
            s.pop();
            ans.push_back('-');
        }

        else{
            //이 말은 그냥 못찾은거니까 불가한거죠
            break;
        }
    }

    //for문 다 돌았어.. 근데 만약 결국 불가했다면? 스택에 원소가 남아있겠지
    if(s.top()!=0) cout<<"NO";
    else for(auto i : ans) cout<< i<<"\n";
}