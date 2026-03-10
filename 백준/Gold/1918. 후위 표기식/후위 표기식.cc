#include <bits/stdc++.h>

using namespace std;

string str;
void input(){
    cin>>str;
}

bool isBigger(char ch, char oper){
    if(ch=='*'||ch=='/'){
        if(oper=='+'||oper=='-'){
            return true;
        }
        else{
            return false;
        }
    }
    else{
        //ch= +, -
        return false;
    }
}

int dfs(int i){
    stack<char> s;
    while(i<str.size()){
        char ch = str[i];
        if(ch==')'){
            //괄호를 닫았으니 드디어 세계관 닫아
            //그전 스택에 있는 것들 차례로 다 던저버려
            while(!s.empty()){
                cout<<s.top();
                s.pop();
            }
            return i;
        }

        if(ch>='A' && ch<='Z') cout<<ch;
        else{
            if(ch=='('){
                i = dfs(i+1);
            }
            else{
                //이제 ㄹㅇ 그냥 기호들
                //스택이 비었다면 그냥 넣어
                //나랑 같거나 낮은 우선순위가 나올때까지 빼야 해
                while(!s.empty()){
                    char oper = s.top();
                    if(isBigger(ch, oper)){
                        s.push(ch);
                        break;
                    }
                    else{
                        cout<<s.top();
                        s.pop();
                    }
                }
                if(s.empty()) s.push(ch);
            }
        }
        i++;
    }

    while(!s.empty()){
        cout<<s.top();
        s.pop();
    }

    return i;
}

void solution(){
    //차례차례 피연산자를 출력하고, 기호가 들어오면 잠시 보관했다가, 그 다음을 보고 우선순위에 따라 바로 빼낼지, 아님 더 추가로 보관할지 등등으로 진행
    dfs(0);
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    input();
    solution();
}