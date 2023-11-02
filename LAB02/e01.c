#include <stdio.h>

int isOdd(int n);
int long gcd(int a, int b);

int main(){
    printf("%d\n", gcd(22,11)); 
}

int isOdd(int n){
    if(n%2==0) return 1;
    return 0;
}

int long gcd(int a, int b){
    if(a==b) return a;
    if(a==1 || b==1) return 1;
    
    if(a<b) return gcd(b,a);
    if(isOdd(a) && isOdd(b)) 
        return 2*gcd(a/2, b/2);
    if(!isOdd(a) && isOdd(b)) 
        return gcd(a,b/2);
    if(isOdd(a) && !isOdd(b)) 
        return gcd(a/2, b);
    if(!isOdd(a) && !isOdd(b)) 
        return gcd((a-b)/2, b);
}
