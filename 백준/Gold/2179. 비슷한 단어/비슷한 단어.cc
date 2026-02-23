#include <bits/stdc++.h>

using namespace std;

int n;
vector<vector<pair<int, string>>> v;
int maxLength = 0;
pair<int, string> answer[2];

void input(){
    for(int i=1;i<=26;i++){
        vector<pair<int, string>> tempV;
        v.push_back(tempV);
    }
    cin>>n;
    for(int i=1;i<=n;i++){
        string str;
        cin>>str;
        if(i==1){
            answer[0].first = i;
            answer[0].second = str;
        }
        if(i==2){
            answer[1].first = i;
            answer[1].second = str;
        }
        v[str[0]-'a'].push_back({i,str});
    }

    
}

void backtrack(int index, vector<vector<pair<int, string>>> s){
    //index번 인덱스로 분류 시작    
    // for(int i=0;i<26;i++){
    //     cout<<i<<" : ";
    //     for(auto j : s[i]) cout<<j<<", ";
    //     cout<<"\n";
    // }
    for(int i=0;i<26;i++){
        //v[i]라 함은, i라는 수로 시작하는 문자열들이 따로 모여있어.
        if(s[i].size()>=2){
            if(index>maxLength){//이 말은 index까지는 같다는 소리니까
                maxLength = index;
                int cnt=0;
                for(auto j : s[i]){
                    if(cnt==2) break;
                    if(cnt==0){
                        answer[cnt].first = j.first;
                        answer[cnt].second = j.second;
                        cnt++;
                    }
                    else{
                        if(j.second==answer[cnt-1].second) continue;
                        else{
                            answer[cnt].first = j.first;
                            answer[cnt].second = j.second;
                            cnt++;
                        }
                    }
                }
            }
            else if(index==maxLength){
                //개수는 같은 선입력된 후보라면 교체해야 해.
                if(s[i][0].first<answer[0].first){
                    int cnt=0;
                    for(auto j : s[i]){
                        if(cnt==2) break;
                        if(cnt==0){
                            answer[cnt].first = j.first;
                            answer[cnt].second = j.second;
                            cnt++;
                        }
                        else{
                            if(j.second==answer[cnt-1].second) continue;
                            else{
                                answer[cnt].first = j.first;
                                answer[cnt].second = j.second;
                                cnt++;
                            }
                        }
                    }
                }
            }
            //여러개여야 겹친다는 표현이 가능하지
            //이 경우에는 그럼 그 안에서 파고 들어야 하니
            vector<vector<pair<int, string>>> strings;
            for(int k=1;k<=26;k++){
                vector<pair<int,string>> tempV;
                strings.push_back(tempV);
            }

            //strings를 하나 만들어주고
            //index번의 문자로 다시 넣어줘야 해
            for(auto j : s[i]){
                if(j.second.size()>=index+1){
                    strings[j.second[index]-'a'].push_back({j.first,j.second});
                }
            }
            backtrack(index+1, strings);
        }
    }
}

void solution(){
    backtrack(1,v);

    cout<<answer[0].second<<"\n"<<answer[1].second;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    input();
    solution();
}