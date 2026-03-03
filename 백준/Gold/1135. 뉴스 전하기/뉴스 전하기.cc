// #include <bits/stdc++.h>

// using namespace std;

// //와 이거 은근 어렵다.. 부하들 중, 큰 덩어리 먼저 전화를 해야하는 구조여야, 동시 진행이 여러개가 돼서 좋은거네
// //홀리 몰리 자식의 사이즈가 큰것만 중요한게 아니야. 사이즈가 아니라 깊이가 깊은 놈을 골라야 하는 거였어!!!!!!!!!!
// //그니까 정확히는 깊은 것 우선, 깊이가 같다면 사이즈 우선인거야. 아닌가? 아니면 고쳐야지 뭐
// //이거에 대한 예시가
// /*
// 15
// -1 0 0 0 0 2 2 3 3 6 7 7 4 12 13
// */
// //어라 다른 예시에서는 사이즈를 우선해야하네, 그럼 사이즈 우선, 그다음은 깊이 우선으로 고쳐
// /*
// 10
// -1 0 0 1 2 2 2 3 7 2
// */

// //젠장 이렇게 했는데도 틀림. 뭐 어떻게 해야 하냐...
// int n;
// struct Node{
//     bool received=false;
//     int depth=0;
//     int childSize=0;
//     vector<int> children;
// };
// Node node[50];
// int parent[50];

// void input(){
//     cin>>n;
//     for(int i=0;i<n;i++){
//         cin>>parent[i];
//         if(parent[i]==-1) continue;
//         else{
//             //아니면 직속 상사가 존재한다는 소리
//             //parent[i]의 자식은 i이다 라는 소리
//             node[parent[i]].children.push_back(i);
//             int j = i;
//             int depth=0;
//             while(parent[j]!=-1){
//                 depth++;
//                 node[parent[j]].depth = max(node[parent[j]].depth, depth);
//                 node[parent[j]].childSize++;
//                 j = parent[j];
//             }
//         }
//     }
// }

// void call(){
//     //0부터 시작해서 차례로 call을 때릴거야
//     int cnt = 1;
//     //queue<int> receiver;
//     //receiver.push(0);//0번이 시작이니까
//     node[0].received = true;

//     int time = 0;
//     while(cnt<n){//n명이 전화를 받으면 끝인거임
//         //매번 모든 노드를 돌며 전화를 받은 사람들에 한해서 전화를 건다.
//         //cout<<"현재 시간 : "<<time<<" 이며 현재까지 전달된 사람 수 : "<<cnt<<"\n";
//         time++;
//         vector<int> newReceiver;
//         for(int i=0;i<n;i++){
//             if(node[i].received==true){
//                 //이 i의 자식들 중 전화를 안받은 놈 중 가장 큰 놈에게 전화를 한다
//                 int num = node[i].children.size();
//                 int maxSize = -1;
//                 int maxDepth=-1;
//                 int maxInd = -1;
//                 for(int j = 0; j<num;j++){
//                     int childInd = node[i].children[j];
//                     if(node[childInd].received==true) continue;
//                     if(maxSize < node[childInd].childSize){
//                         maxDepth = node[childInd].depth;
//                         maxSize = node[childInd].childSize;
//                         maxInd = j;
//                     }
//                     else if(maxSize == node[childInd].childSize){
//                         //깊이가 동일하다면 사이즈가 큰거로 가야 해.
//                         if(maxDepth<node[childInd].depth){
//                             maxDepth = node[childInd].depth;
//                             maxInd = j;
//                         }
//                     }
//                 }

//                 //이렇게 하면 i의 자식들 중 전화를 안받았으며 사이즈가 가장 큰 놈이 maxSizeInd번째 자식이다.
//                 //근데 이 놈은 나중에 처리를 해줘야 한다.
//                 //node[node[i].children[maxSizeInd]].received = true;
//                 if(maxSize>-1){
//                     //cout<<i<<"가 "<<node[i].children[maxInd]<<"에게 전화를 겁니다\n";
//                     newReceiver.push_back(node[i].children[maxInd]);
//                 }
//             }
//         }

//         for(auto i : newReceiver){
//             //이번 턴에 새롭게 전화받은 애들의 수신여부를 체크
//             node[i].received = true;
//             cnt++;
//         }

//         newReceiver.clear();
//     }

//     cout<<time;
// }

// void solution(){
//     //input에서 저렇게 복잡하게 한 이유는 0번 인덱스부터 시작했을때, 가장 많은 자식을 가지고 있는 자식에게 먼저 전화를 때리는 것이 이득이기 때문이야
//     call();
// }

// int main(){
//     // ios_base::sync_with_stdio(0);
//     // cin.tie(0); cout.tie(0);

//     input();
//     solution();
// }

// //와 이거 은근 어렵다.. 부하들 중, 큰 덩어리 먼저 전화를 해야하는 구조여야, 동시 진행이 여러개가 돼서 좋은거네
// //홀리 몰리 자식의 사이즈가 큰것만 중요한게 아니야. 사이즈가 아니라 깊이가 깊은 놈을 골라야 하는 거였어!!!!!!!!!!
// //그니까 정확히는 깊은 것 우선, 깊이가 같다면 사이즈 우선인거야. 아닌가? 아니면 고쳐야지 뭐
// //이거에 대한 예시가
// /*
// 15
// -1 0 0 0 0 2 2 3 3 6 7 7 4 12 13
// */
// //어라 다른 예시에서는 사이즈를 우선해야하네, 그럼 사이즈 우선, 그다음은 깊이 우선으로 고쳐
// /*
// 10
// -1 0 0 1 2 2 2 3 7 2
// */

/*이런 고민들을 했는데, 둘다 조건이 아니다, 매번 달라지기 때문이다. 깊어도, 사이즈가 커도, 그 내부에 조건이
실제로 어떻냐에 따라 달라지는 것이다.

그렇기에 "시간"이라는 것에 집중해서 하위 노드에서부터 차근차근 올라가야만 하다..
내가 내 자식들에게 전화를 돌려야한다면
내 자식들이 또 그 아래에게 전화를 돌리는 시간이 구해졌있다면, 내림차순으로 정렬 후에
가장 오래 걸리는 아이에게 먼저 전화를 주는 식으로 하여 최대가 곧 내 시간이다.
예를 들어, 내 자식이 1,2,3,4,인데 각각 5,5,3,2초가 걸린다고 하자.
그렇다면 나는 5+1초에 1번 자식에게, 5+2초에 2번 자식에게 3+3초에 3번자식에게, 2+4초에 4번 자식에게 전화를 걸면 된다. 즉 총 7초가 걸릴것이다.

다시 말해 DP가 되는 문제이다...*/


#include <bits/stdc++.h>

using namespace std;

int n;
struct Node{
    vector<int> children;
    int parent;
};

Node node[50];

void input(){
    cin>>n;

    for(int i=0;i<n;i++){
        int num;
        cin>>num;
        //i의 부모는 num입니다.
        node[i].parent = num;//num이 존재하는 놈이면 곧 num의 자식은 i이기도 한거다.
        if(num!=-1) node[num].children.push_back(i);
    }
}

int dp[50];

int makeDp(int parent){
    //parent의 자식들의 시간에 1,2,3,4를 더하면서 최대를 구하면 된다.
    if(dp[parent]!=-1){
        return dp[parent];
    }

    if(node[parent].children.size()==0){
        //말단 노드라는 것이기에 dp는 0이 되겠군
        dp[parent]=0;
        return dp[parent];
    }

    
    int childNum = node[parent].children.size();
    vector<int> parentDp;
    for(int i=0;i<childNum;i++){
        parentDp.push_back(makeDp(node[parent].children[i]));
    }

    sort(parentDp.begin(), parentDp.end());
    reverse(parentDp.begin(), parentDp.end());

    int plus = 1;
    int maxV = -1;
    for(auto i : parentDp){
        maxV = max(maxV, i+plus);
        plus++;
    }
    return maxV;
}

void solution(){
    for(int i=0;i<n;i++) dp[i]=-1;
    cout<<makeDp(0);
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    input();
    solution();
}