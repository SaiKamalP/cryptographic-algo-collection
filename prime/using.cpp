#include "BigNumber.h"
using namespace std;
//binary exponentation 
long long bie(long long x,long long n, long long mod=1000000007){
 if(n==0) return 1;
    long long temp=bie(x,n/2,mod);
    temp=(temp*temp)%mod;
    if(n&1) return ((x%mod)*temp)%mod;
    return temp;
}

int main(){
    int p=0,q=0;
    BigNumber bv;
    bv.setAllOne();
    for(int i=1;i<1024;i++){
        BigNumber b(i),c;
        bv.divide(bv,b,c);
        for(int j=0;j<1024;j++){
            for(int k=0;k<10;k++){
                BigNumber res;
                BigNumber a(j),e(k);
                BigNumber::bie(a,e,b,c,res);
                BigNumber d(bie(j,k,i));
                q++;
                if(res.toString()==d.toString()){
                    p++;
                }
                else{
                    cout<<res<<" not same "<<d<<" for "<<j<<"^"<<k<<"%"<<i<<endl;
                    goto done;
                }
            }
        }
            cout<<i<<endl;
    }
    done:{}

    // BigNumber a("0000000000000010111001001000001000000000");
    // BigNumber c;
    // for(int i=0;i<18;i++){
    //     a.shiftLeft(a,i,c);
    //     cout<<c<<"   "<<c.getMSB()<<endl;
    // }
    cout<<"passed "<<p<<"/"<<q<<endl;

    return 0;
}