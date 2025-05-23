#include <iostream>
#include <string>
using namespace std;

int main() {
    int numBas;
    cin>>numBas;
    
    int num3=0, num5=0, sum=5000;
    
    for(int i=0;i<=numBas/3;i++){
        for(int j=0;j<=numBas/5;j++){
            if(i*3+j*5 == numBas) sum = min(sum, i+j);
        }
    }
    
    if(sum!=5000) cout<< sum;
    else cout<<-1;
}