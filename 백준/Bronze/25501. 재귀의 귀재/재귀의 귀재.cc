#include <stdio.h>
#include <string.h>

int n;
char str[1001];
int cnt=0;

int recursion(const char *s, int l, int r){
    cnt++;
    if(l >= r){
        printf("1 %d\n", cnt);
        cnt=0;
        return 0;
    }
    else if(s[l] != s[r]){
        printf("0 %d\n", cnt);
        cnt=0;
        return 0;
    }
    else return recursion(s, l+1, r-1);
}

int isPalindrome(const char *s){
    return recursion(s, 0, strlen(s)-1);
}



int main(){
    scanf("%d", &n);

    for(int i=1;i<=n;i++){
        scanf("%s", str);

        isPalindrome(str);
    }
}