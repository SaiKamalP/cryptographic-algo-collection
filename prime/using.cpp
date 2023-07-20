#include "BigNumber.h"
using namespace std;
int main(){
    int p=0,q=0;
    BigNumber bv;
    bv.setAllOne();
    for(int i=1;i<1024;i++){
        BigNumber b(i),c;
        bv.divide(bv,b,c);
        for(int j=0;j<1024;j++){
            q++;
            BigNumber a(j);
            BigNumber res;
            BigNumber::mod(a,b,c,res);
            BigNumber d(j%i);
            if(res.toString()==d.toString()){
                p++;
            }
            else{
                cout<<res<<" not same "<<d<<" for "<<i<<"/"<<j<<endl;
                goto done;
            }
        }
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