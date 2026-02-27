#include <bits/stdc++.h>

using namespace std;

int t;
int n;
vector<int> preOrder;
vector<int> inOrder;

struct Node{
    int left=0;
    int right=0;
};
Node node[1001];

void makeTree(int preOrderInd, int l, int r){//preOrderInd번쨰의 preOrder값을 head로 할 때, inorder의 좌우 범위가 l~r

    int head = preOrder[preOrderInd];
    //쪼개는거야
    int headInd;
    for(int i=l;i<=r;i++){
        if(inOrder[i]==head) headInd = i;
    }

    //경우의 수가 다음과 같다
    //1. 리프노드라 좌우 자식이 없다
    //2. 한쪽만 자식이 없다.
    //3. 전부 자식이 있다.

    //1. l==r==headInd
    //2-1. headInd>l && headInd==r 왼쪽에만 자식이 있다
    //2-2. headInd<r && headInd==l 오른쪽에만 자식이 있다
    //3. headInd>l && headInd<r 양쪽에 다 자식이 있다

    if(l==r && r==headInd) return;
    else if(headInd>l && headInd==r){
        //이게 뭔소리야. 왼쪽에 자식이 있대. 그럼 preOrderInd+1가 곧 지 왼쪽
        node[head].left = preOrder[preOrderInd+1];
        //이렇게 되면, 그 놈이 다시 head가 돼서 위 과정을 반복해야하니
        makeTree(preOrderInd+1, l, headInd-1);
    }
    else if(headInd<r && headInd==l){
        //얘는 오른쪽에만 자식이 있는거야. 그럼  preOrderInd+1가 곧 지의 오른쪽
        node[head].right = preOrder[preOrderInd+1];
        makeTree(preOrderInd+1, headInd+1, r);
    }

    else if(headInd>l && headInd<r){
        //얘는 왼쪽과 오른쪽에 자식이 전부 있는거야
        //우선 확실한 건 당장 preOrderInd+1이 지의 왼쪽 head가 되는 건 확실해
        //지의 오른쪽 head는 preOrder에서 지 왼쪽 개수만큼 나온 뒤가 지 오른쪽 head
        node[head].left = preOrder[preOrderInd+1];
        makeTree(preOrderInd+1, l, headInd-1);

        node[head].right = preOrder[preOrderInd+1+headInd];
        makeTree(preOrderInd+1+headInd, headInd+1, r);

    }
}

void printTree(){
    for(int i=1;i<=n;i++){
        cout<<i<<"번 트리 설명 : ";
        cout<<"왼쪽 : "<<node[i].left<<" ";
        cout<<"오른쪽 : "<<node[i].right<<"\n";
    }
}

void printPostOrder(int head){
    if(node[head].left!=0) printPostOrder(node[head].left);
    if(node[head].right!=0) printPostOrder(node[head].right);
    cout<<head<<" ";
}

void solution(){
    makeTree(0,0,n-1);

    //printTree();

    printPostOrder(preOrder[0]);
    cout<<"\n";
}

void input(){
    

    cin>>t;
    while(t--){
        preOrder.clear();
        inOrder.clear();
        for(int i=0;i<1001;i++) node[i]=Node{0,0};

        cin>>n;
        for(int i=1;i<=n;i++){
            int num;
            cin>>num;
            preOrder.push_back(num);
        }
        for(int i=1;i<=n;i++){
            int num;
            cin>>num;
            inOrder.push_back(num);
        }

        solution();
    }
}


int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    input();
    //solution();
}