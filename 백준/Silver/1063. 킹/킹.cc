#include <bits/stdc++.h>

using namespace std;

string str;

int arr[9][9];
int dx[8] = {0,0,1,-1,-1,-1,1,1};
int dy[8] = {1,-1,0,0,+1,-1,1, -1};
int a, b, c, d;

void king_move(int n){
    int nextA = a + dx[n];
    int nextB = b + dy[n];
    if(nextA<1 || nextA>8 || nextB <1 || nextB>8){
        return;
    }
    else{
        //일단 킹은 움직일 수 있다는 소리
        //거기에 돌이 있냐 없냐가 이제 중요한거죠

        if(nextA == c && nextB == d){
            //돌이랑 겹침
            int nextC = c+dx[n];
            int nextD = d + dy[n];
            if(nextC<1 || nextC>8 || nextD<1 || nextD>8){
                return;
            }
            else{
                //이럼 돌도 움직일 수 있다!
                a = nextA; b = nextB; c= nextC, d = nextD;
            }
        }
        else{
            //킹만 움직여
            a = nextA; b=nextB;
        }

    }
}

int main(){
    cin>>str;
    //킹의 위치
    b = str[0]-'A'+1;
    a = 9-(str[1]-'0');
    //이렇게 하면 a,b에 킹이 위치한다.

    cin>>str;
    d = str[0]-'A'+1;
    c = 9-(str[1]-'0');
    //이렇게 하면 돌이 c,d에 위치한다
    int n;
    cin>>n;

    //cout<<a<<b<<c<<d<<"\n";
    
    for(int i=1;i<=n;i++){
        cin>>str;

        if(str=="R"){//0
            king_move(0);
        }
        else if(str == "L"){//1
            king_move(1);
        }
        else if(str == "B"){//2
            king_move(2);
        }
        else if(str == "T"){//3
            king_move(3);
        }
        else if(str == "RT" ){//4
            king_move(4);
        }
        else if(str == "LT"){//5
            king_move(5);
        }
        else if(str == "RB"){//6
            king_move(6);
        }
        else if(str == "LB"){//7
            king_move(7);
        }

        //cout<<"현재위치 : "<<a<<" "<<b<<" "<<c<<" "<<d<<"\n";

    }

    cout<<char('A'+b-1)<<9-a<<"\n"<<char('A'+d-1)<<9-c;
}