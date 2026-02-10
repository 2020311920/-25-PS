#include <bits/stdc++.h>

using namespace std;

string str;
string bomb;

void testPrint(stack<pair<int, int>> s){
    cout<<"현재 스택 상태입니다 : ";
    while(!s.empty()){
        cout<<"{"<<s.top().first<<", "<<s.top().second<<"} ";
        s.pop();
    }
    cout<<"\n";
}

//스택상태를 확인하고 폭탄 완성 시 즉시 제외하는 함수
//왜냐 폭탄 길이가 1일 수도 있어서
void bombDelete(stack<pair<int, int>> &s){
    if(s.top().second == bomb.size()-1){
        int num = bomb.size();
        while(num--) s.pop();
    }
}


void solution(){
    
    //내 전략은 다음과 같아
    /*str를 처음부터 끝까지 순회하면서 일치하는 만큼 늘려
    예를 들어 str = ababccacaabcd, bomb = abc라고 하면
    1212331311230 이렇게, 일치하면 str의 위치값(시작이 1)으로 변화하고 bomb이랑 안맞으면 0으로 하고 해서
    숫자가 bomb 길이랑 일치하는 순간 str에서 날리기, 이렇게 한번 순회하면
    abcacad(=1231310) 이렇게 되고 다시 순회하면 또 123이 있으니 또 쉽게 제거가 가능하지 않을까..*/

    /*내 기억에 이런 결의 유명한 알고리즘이 있던걸로 아는데*/

    /*그니까, 순회하면서 뭐 숫자를 컨트롤하고, 그 숫자가 어디에 도달하면 즉시 지우는 작업이 되는 식이면 될 거야. 단순한 순회방식이면 무조건 시간초과다*/

    /*다음은 내가 생각해낸 로직이다
    0. stack은 문자,순번으로 이루어져있다.
    1. stack의 top을 바라본다, top의 순번을 n이라고 하고 현재 위치의 문자와 폭탄의 n+1이 일치하는지 파악한다
    1-1. 일치하다면 stack에 현재 위치 문자와 n+1을 넣어주고 현재위치를 옮긴다
    1-2. 일치하지 않다면 top의 문자가 해당 순번 이전에 bomb에 존재하는지를 역으로 탐색한다. 
    1-2-1. 이전에도 있다면 해당 위치+1의 bomb 문자가 현재 위치 문자와 같은지, 같다면 해당위치+1을 넣어준다
    1-2-2. 끝까지 없다면 현재 위치 문자가 애초에 bomb 문자와는 다르다는 것이므로 -1로 하여 stack에 넣는다.*/

    //이를 위해 stack이 비어있다면 현재 위치의 문자가 bomb의 0번 자리와 일치하는지 보고 -1로 넣을지 0으로 넣을지 결정한다.
    stack<pair<int, int>> s;
    for(auto i : str){
        //testPrint(s);
        if(s.empty()){
            //i는 현재 위치의 문자
            if(i==bomb[0]){
                //같으니까 0으로 s에 삽입
                s.push({i,0});
            }
            else{
                //애초에 시작점과 문자가 다르니까 -1로 삽입
                s.push({i,-1});
            }

            //폭탄의 길이가 1일수도 있어서 
            bombDelete(s);
        }
        else{
            //일단 top의 순번을 파악
            int element =  s.top().first;
            int num = s.top().second;
            if(i==bomb[num+1]){
                //즉, 지금 위치가 이전거에 이어지는 폭탄의 일종이라면
                s.push({i,num+1});
                //그러고 폭탄이 완성됐는지 아닌지
                bombDelete(s);
            }
            else{
                //s에 들어간 이전것과 이어지는게 아니라면 top이 들어가면서 입력된 순번 이전에도 bomb의 일종이었는지
                for(int ind = num-1; ind>=0;ind--){
                    //역으로 끝(=문자열 맨 처음)까지 탐색
                    if(bomb[ind]==element){
                        //있다면 다시 확인
                        if(i==bomb[ind+1]){
                            s.push({i, ind+1});
                            break;
                        }
                        //아니면 계속 이어서 역으로 탐색
                    }
                }
                //이 역으로 탐색하는 게 비용이 좀 셀 것 같고, 결국 시간초과가 될거라는 확신이 드는데.. 아 근데 최악이 bomb의 길이니까 엄청 큰일은 아니겠다. 만약에 bomb이 시간초과가 날만큼 충분히 길다면 어떻게 해야할까. 일단은 영향 없으니 패스해도 돼


                //끝까지 탐색했다는 사실
                //즉, 가장 최근 문자가 이전에 동일하게 있어서 그 다음과 현재가 일치하는 경우가 없다는 거니까
                //현재 문자가 시작점과 일치하는지 체크
                if(i==bomb[0]) s.push({i,0});
                else s.push({i,-1});
            }
        }
    }
    
    if(s.empty()) cout<<"FRULA";
    else{
        string result="";
        while(!s.empty()){
            result+=s.top().first;
            s.pop();
        }
        reverse(result.begin(), result.end());
        cout<<result;
    }
}

void input(){
    cin>>str;
    cin>>bomb;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    input();
    solution();
}