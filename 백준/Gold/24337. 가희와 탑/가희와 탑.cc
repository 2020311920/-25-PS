#include <bits/stdc++.h>

using namespace std;

int n, a, b;
int field[100001];

void input(){
    cin>>n>>a>>b;
}

void solution(){
    //1~a까지는 1,2,3,4,... a이렇게 늘어야 해
    //?,,,n 까지 총 b개가 ?...1 이렇게 줄어야 해.

    //이때 가능한 경우에는 a b 중 큰 게 각 시야의 끝을 차지하도록 해야 해
    //일단 개수 조건이 그럼 생긴다
    //a+b가 n+1보다 작거나 같으면 무조건 답은 존재한다.
    for(int i=1;i<=n;i++) field[i]=1;
    if(a+b<=n+1){
        //일단 양쪽 시야의 끝은 둘 중 최대
        
        //이 문제가 어려운 이유는 끝에서부터 채워나가야 하기 때문이다
        //왜? 사전순으로 배치해야하기에 최대한 앞은 1로만 채우는 것이 좋기 때문
        //그래서 미리 다 1로 채워놓고 뒤에서부터 조작하는거야.
        //앞에서 볼때 2개가 보이면 그냥 해도 되지만
        //앞에 1개밖에 안보인다면 맨 앞을 m을 박는게 최선
        
        int m = max(a,b);
        //끝에서 b-1만큼 채워
        for(int i=1;i<=b-1;i++){
            field[n+1-i] = i;
            
        }
        if(a>1){
            field[n+1-b] = m;
            //이어서 a-1개를 차례로 넣어줘
            for(int i=1;i<=a-1;i++){
                field[n+1-b-i] = a-i;
            }
        }
        else{
            //a가 하나만 보여야 한다?
            field[1] = m;
        }

        for(int i=1;i<=n;i++) cout<<field[i]<<" ";
    }

    else {
        cout<<-1;
    }
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    input();
    solution();
}