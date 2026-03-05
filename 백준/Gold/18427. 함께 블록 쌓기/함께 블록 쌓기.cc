/*
생각의 흐름
1. 처음에 그냥 무식하게 특정 학생을 선택하냐 안하냐 고르고, 선택된 학생들이 가지고 있는 블록들 하나씩 선택해서 
만들어지느냐를 따져보려했다. 특정 학생을 고르냐 안고르냐를 무식하게 DFS를 돌리는 거는 2^50이라서 나가리일 것이다. 설령 학생들을 다 골랐다 해도, 각 학생이 가진 블록수 최대가 10개인데, 만약 n(최대 50)명 골랐으면 10^50개의 조합이 생기므로 이것대로 나가리다

2. 그래서 생각을 뒤집어서 목표 H를 1개의 이상의 수로 쪼깬다면 (H=x+y+z...), 그 부분h들을 가진 학생수 모든 h에 대해 곱해서 구할 수 있겠다 생각했어. 
그니까 쪼개는 경우의 수 * 쪼개진 결과의 부분h들 가진 학생들의 조합 수를 하려고 했는데
H는 공통된 수로 분리가 되기도 할거라서 최대 1000을 1~1000의 숫자의 조합으로 공통이 되게 하는 것이기 때문에 
얘야말로 말도 안되는 시간 복잡도가 걸릴 것이다 ㅇㅇ, 쪼개지기만 하면 사실 미리 특정 높이를 가진 학생의 수는 쉽게 구해지니까 (예. height[n].push_back(학생 넘버)-> 1번 학생이 n 높이 블록을 가지면 저렇게 보관하는거지), 학생의 쉽게 나올 거라 생각했어. 암튼 안될 것 같다는 결론

3. 혹시 DP? 그니까 n명의 학생으로 만든 경우의 수를 구했다면, 추가 한명이 생길 경우, 그 학생을 반드시 사용했을 때, 새롭게 생겨나는 경우의 수를 쉽게 구할 수만 있다면 그니까 새로 온 친구가 (x,y,z...)의 블록을 가졌다고 한다면
f(n,h)이라 함은 새로운 친구가 없었던 경우에 h를 만드는 경우 = 새로운 친구를 쓰지 않고 h를 만드는 경우의 수
f(n+1,h)은 {f(n,h)+(새로운 친구를 반드시 쓰고 가진 블록 하나 쓴다, h-새 친구가 쓴 블록)}=f(n,h)+{f(n,h-x)+f(n,h-y)+...}
오.. 꽤 괜찮아는 보인다 */

#include <bits/stdc++.h>

using namespace std;

int n,m,h;
int answer[51][1001]; //넉넉 잡아 60*1000 = 6만개의 정수 -> 6*10^4개의 4byte -> 약 2*(10^6)byte = 2MB 정도
vector<int> student[51];//student[n]은 n번 학생이 가진 블록들 높이 vector // 만약 모든 50명의 학생이 10개의 원소 를 가진다면 메모리 계산 어떻게 함?

void input(){
    cin>>n>>m>>h;
    string str;
    getline(cin, str);

    for(int i=1;i<=n;i++){
        string str;
        getline(cin, str, '\n');
        int blockH=0;
        int strSize = str.length();
        //cout<<strSize<<"길이..\n";
        for(int j=0;j<=strSize;j++){
            if(str[j]==' ' || j==strSize){
                //하나의 블록 높이 발견
                //cout<<"블록 높이 발견 : "<<blockH<<"\n";
                student[i].push_back(blockH);
                blockH = 0;
                continue;
            }
            blockH*=10;
            blockH += (str[j]-'0');
        }
    }
}

int getAnswer(int num, int height){//지금 보니 최악의 경우 n(<=50)번동안 매번 m(<=10)개의 재귀가 발생할 수 있으니 그럼 m^n의 재귀가 생길 수 있네 시간초과 나겠다..;; 아래에 calculate함수 만들어서 하면 되겠다. 근데 왜 재귀로 하면 터지고 저렇게 하면 안터지지?
    if(answer[num][height]>-1){
        return answer[num][height];
    }
    if(height == 0){
        answer[num][height] = 1;
        return answer[num][height];
    }
    //if(height<0) return 0;

    //그게 아니라면 이제 재귀로 찾아내야 해
    int ans = getAnswer(num-1, height);
    for(auto i : student[num]){
        if(height-i>=0) ans += getAnswer(num-1, height-i);
    }

    answer[num][height] = ans;
    return ans;
}

void calculate(){
    //1번 학생만 있다 생각하고 한명씩 추가하면서 ans배열을 채우고 생각해볼까?
    //init에서 처리해줬을 거고 ㅇㅇ
    for(int i=2;i<=n;i++){
        for(int j=0;j<=h;j++){
            answer[i][j] = answer[i-1][j];
            for(auto k : student[i]){
                if(j-k>=0) answer[i][j] = (answer[i][j] + answer[i-1][j-k])%10007;
            }
        }
    }
}

void init(){
    for(int i=0;i<51;i++){
        for(int j=0;j<1001;j++){
            //answer[i][j]=-1; 재귀로 할 때
            answer[i][j]=0; //calculate함수 쓸 때
        }
    }

    answer[1][0] = 1;
    for(auto k : student[1]){
        //1번 학생이 가진 블록들의 높이가 각각 h인거임
        answer[1][k] = 1; //1번 학생만 가지고 h를 만들 수 있잖아 지가 가지고 있으니까 그럼 1가지
    }
}

void solution(){
    init();

    calculate();
    cout<<answer[n][h]%10007;
    //cout<<getAnswer(n,h)%10007;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    input();
    solution();
}