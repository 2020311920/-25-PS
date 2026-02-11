#include <bits/stdc++.h>

using namespace std;

int n,m;

struct linkNode{
    int linkNum;
    int end;
    int alive;
};
struct node{
    bool isIn=false;
    vector<linkNode> linkNodes;
};

node nodes[100001];

struct spanningTree{
    vector<int> linkNum;
    vector<int> nodeNum;
};
vector<spanningTree> spanningTrees;

void makeForest(){
    for(int i=1;i<=n;i++){
        //모든 노드들을 돌면서 어떤지 체크해보자
        if(nodes[i].isIn==false){
            //어디 속하지 않았다면 길드 생성 후 거기서부터 시작되는 여행
            vector<int> blank;
            vector<int> nodeNum;
            nodes[i].isIn = true;
            nodeNum.push_back(i);

            queue<int> q;
            q.push(i);
            while(!q.empty()){
                int now = q.front(); q.pop();
                //now랑 연결된 점들 중 아직 포함 이력이 없는애들만 골라보고, 그 간선 넘버도 넣어준다
                for(auto j : nodes[now].linkNodes){
                    if(nodes[j.end].isIn==false){
                        //감사히 포함시켜야지
                        blank.push_back(j.linkNum);
                        nodeNum.push_back(j.end);

                        q.push(j.end);
                        nodes[j.end].isIn = true;

                    }
                }
            }

            spanningTrees.push_back({blank, nodeNum});
        }

        else{
            continue;
        }
    }
}

void printAnswer(){
    //spanningTrees 사이즈가 2라는 전제 하입니다.
    cout<<spanningTrees[0].nodeNum.size()<<" "<<spanningTrees[1].nodeNum.size()<<"\n";

    for(auto i : spanningTrees[0].nodeNum) cout<<i<<" ";
    cout<<"\n";
    for(auto i : spanningTrees[0].linkNum) cout<<i<<" ";
    cout<<"\n";

    for(auto i : spanningTrees[1].nodeNum) cout<<i<<" ";
    cout<<"\n";
    for(auto i : spanningTrees[1].linkNum) cout<<i<<" ";
    cout<<"\n";
 }

void solution(){
    //하나하나 보면서 스패닝 포레스트를 구성해보자.
    makeForest();
    //cout<<"숲 만든 뒤 개수 : "<<spanningTrees.size()<<"\n";
    //그럼 spanningTrees에 잘 나뉘어져 들어갔을거시여
    if(spanningTrees.size()==1){
        //쪼개는 작업
        
        if(spanningTrees[0].nodeNum.size()<=2) cout<<-1;
        else{
            vector<int> link;
            vector<int> nodeNum;

            //link.push_back(spanningTrees[0].linkNum.back());
            spanningTrees[0].linkNum.pop_back();
            nodeNum.push_back(spanningTrees[0].nodeNum.back());
            spanningTrees[0].nodeNum.pop_back();
            spanningTrees.push_back({link, nodeNum});

            printAnswer();
        }

        
        return;
    }
    else if(spanningTrees.size()==2){
        //기쁘게 바로 기기
        //아니지 사이즈가 하필 같을 수도
        if(spanningTrees[0].nodeNum.size() == spanningTrees[1].nodeNum.size()){
            cout<<-1;
        }
        else printAnswer();

        return;
    }
    else{
        //불가
        cout<<-1;
        return;
    }
}

void input(){
    cin>>n>>m;
    //안전하게 전처리가 필요해 보임
    //n개의 노드에 간선이 아예 없을 수도 있으니!
    for(int i=1;i<=n;i++){
        nodes[i].isIn = false;
        nodes[i].linkNodes.clear();
    }
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        nodes[u].linkNodes.push_back({i,v,true});
        nodes[u].isIn = false;
        nodes[v].linkNodes.push_back({i,u,true});
        nodes[v].isIn = false;
    }
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    input();
    solution();
}