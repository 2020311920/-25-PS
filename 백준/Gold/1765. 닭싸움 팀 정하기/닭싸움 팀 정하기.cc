//각각이 나머지에 대한 "친구"조건을 확립해야 한다. 적인 거는 음.. 노 상관
    //팀의 조건은 내부인원이 서로 "반드시 친구"여야 한다이기 때문

    /*잠깐 생각을 해봤는데 이런 더러운 경우도 있어
    1과4는 친구
    1과2 적
    2와3 적 -> 1과 3은 친구가 돼
    3과4 적
    이렇게 1은 3과 4와는 친구인데
    하필 3과 4가 적이야. 이러면 1,3,4는 팀이 될 수는 없어. 그러나 이건 문제에서 인정되는 케이스일거야 왜냐
    두 학생이 동시에 친구이면서 적인경우만 없다 했으니 ㅇㅇ
    *****라고 생각했는데, 아니야 이건 입력이 불가능한 케이스이네, 왜냐하면 서로의 친구는 친구이니까
    동시에 친구이면서 원수인 케이스가 되고, 위 입력은 불가능하네 ㅇㅇ 오키 이건 해결 완료
    ----
    즉, 이 문제를 해결하는 키는 사실상 1에게 있어 먼저 2,3,4,5 나머지와의 친구 관계를 설정
    각각 이 각 나머지에 대한 친구 관계를 확립하고
    그다음 다시 각각 돌면서 팀 관계를 설정해야해*/

    /*또 굉장히 더러운 경우가
    나의 적 의 적은 친구지. 그니까
    1과2가 적, 2와 3이 적이면 1과 3은 친구야
    근데 하필 3과 4가 적이고, 4와 5가 적이면
    결론적으로 1과 5는 친구 아닌가? 이거는 또 어떻게 알아낼 것인가.. 참 문제라는 거임
    ****이것도 해결이 돼. 왜냐. 2.e 1,3이니까 1과3은 친구라고 바로 볼 수 있네 ㅇㅇ
    4.e 3,5이니까 3과 5는 친구가 되고 그럼 자연스럽게 1과 5도 친구가 돼. 즉, 친구 체인이 있다면, 그 중 한명이라도 친구이면 친구가 되는거야 ㅇㅇ

    /*아하.. x에게 a,b,c가 적이라면 abc는 서로 친구이겠구나 x라는 적을 공통으로 가지니까*/
    /*대박,, 관계를 전부 입력받으면 애초에 서로서로가 친구이고 적이라는 정보가 생기니까, 적 정보를 바탕으로 친구인지도 파악이 되면 친구인지를 파악할 수 있겠네*/

/*최종 풀이 방향
1. 초기 친구 설정
2. 공통 적을 가진 서로가 친구 설정
개인적으로는 "연결망"으로 풀어보고 싶다. 
3. 이후에 각각에게 물어보며 팀을 설정*/

#include <bits/stdc++.h>

using namespace std;

int n,m;
struct Node{
    vector<int> friends;
    vector<int> enemys;
};

Node node[1001];

//사실 친구라는 것은 대표 친구 한명만 있으면 되는데, 이게 곧 그래프로 푸는 거 같은데.. 하 답답하네
//적은 리스트로 관리한 다음에 나중에 대표 친구로 연결해주면 또 되고
int parent[1001];

int getParent(int a){
    if(parent[a]==a) return a;
    parent[a] = getParent(parent[a]);
    return parent[a];
}

void unionFind(int a, int b){
    int parentA = getParent(a);
    int parentB = getParent(b);
    if(parentA!=parentB){
        //둘이 다르면 합친다는 거임
        int minParent = min(parentA, parentB);//보통 보니까 항상 작은 걸로 하던데 왜지?
        parent[a] = minParent; parent[b]=minParent;
    }
}

void input(){
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        char ch;
        cin>>ch;
        int a,b;
        cin>>a>>b;

        if(ch=='E'){
            node[a].enemys.push_back(b);
            node[b].enemys.push_back(a); //연결망으로 간다하면 굳이 이렇게 양방향으로 안놔도 되려나
        }
        else if(ch=='F'){
            node[a].friends.push_back(b);
            node[b].friends.push_back(a);
            //사실상 위의 경우는 무시해도 되고
            unionFind(a,b);//a와 b의 부모를 동일시 한다. 대표 친구가 같다!
        }
    }
}

void makeFriend(){
    for(int i=1;i<=n;i++){
        //i의 적들이 있을거 아니야, 그 적 원소들끼리 unionfind를 진행해보자
        //대표 한명 정해.
        int eSize = node[i].enemys.size();
        if(eSize==0) continue; //i에겐 적이 없어.
        else{
            int president = node[i].enemys[0];
            for(int j=1;j<eSize;j++){
                unionFind(president, node[i].enemys[j]);
            }
        }
    }
}

void solution(){
    //이미 대표 친구가 같은 애들도 있고 아닌 경우도 있는데, 공통 적을 가진 애들끼리도 친구가 되기에 적 리스트를 바탕으로 또 정리
    makeFriend();
    
    //최종적으로 각각의 부모의 수를 카운트하면 돼. 쉽게 set쓰자
    set<int> parentCnt;
    for(int i=1;i<=n;i++){
        int p = getParent(i);
        parentCnt.insert(p);
    }

    cout<<parentCnt.size();
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    for(int i=1;i<=1001;i++) parent[i]=i;//처음에는 각각이 친구 대표가 된다.

    input();
    solution();
}