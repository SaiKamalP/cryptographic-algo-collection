#include <bits/stdc++.h>
 
using namespace std;
 
int main() {
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    long long n=32,p=32;
    long long nv=(1ll<<n),pv=(1ll<<p);

    long long b=1;

    long long c=nv/b;
    long long tv=100000000;
    int pc=0;
    for(int j=1;j<=tv;j++){
        b=j;
        c=nv/b;
        cout<<"starting "<<b<<endl;
        for(int i=1;i<=tv;i++){
            if(i/b-((i*c)>>n)>1 || i/b<((i*c)>>n)){
                cout<<"failed "<<i<<"/"<<b<<" expected "<<i/b<<" found "<<((i*c)>>n)<<endl;
            }
            else{
                pc++;
            }
        }
    }
    cout<<"passed "<<pc<<"/"<<tv*tv<<endl;
    
    return 0;
}