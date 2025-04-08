#include <iostream>
#include <string>
using namespace std;

int main() {
    int n, N=0, count=0;
    cin>>n;
    
    while(!(count==n)){
        N++;
        string str = to_string(N);
        bool found = str.find("asb");
        //cout<<found<<endl;
        if(str.find("666")!=string::npos) count++;
    }
    
    cout<<N;
    
}