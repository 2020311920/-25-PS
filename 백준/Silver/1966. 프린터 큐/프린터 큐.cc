#include <bits/stdc++.h>

using namespace std;

int n, place;


int main(){
    int testCase;
    cin>>testCase;

    while(testCase>0){
        queue<int> priority;
        queue<int> numbering;
        vector<int> priority_sort;
        testCase--;
        cin>>n>>place;

        for(int i=0;i<n;i++){
            numbering.push(i);
            int p;
            cin>>p;
            priority.push(p);
            priority_sort.push_back(p);
        }
        sort(priority_sort.begin(), priority_sort.end());
        bool found = false;
        int max_ind = n-1;
        int cnt=0;
        while(!found){//내가 원하는 놈 나올때까지
            cnt++;
            while(priority.front() != priority_sort[max_ind]){
                //최대인 놈이 맨 앞에 있을 때까지
                int num = numbering.front();
                numbering.pop();
                numbering.push(num);
                num = priority.front();
                priority.pop();
                priority.push(num);
            }

            //이제 인쇄할거야. 이때가 내가 원하는 놈인지 체크
            if(numbering.front()==place) found = true;
            else{
                //cout<<numbering.front()<<"가 우선순위"<<priority.front()<<"이므로 뽑음\n";
                numbering.pop();
                priority.pop();
                max_ind--;
            }
        }
        cout<<cnt<<"\n";
    }
}