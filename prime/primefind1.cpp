#include <bits/stdc++.h>
#include "BigNumber.h"
using namespace std;
//random number generation
long long gRand(long long min=0,long long max=100){
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static long long RMin = 0;
    static long long RMax = 1000000000000000000ll;
    static std::uniform_int_distribution<long long> Distribution(RMin, RMax);
    return min+ Distribution(gen)%(max-min+1);
}
int main() {
    int len=1000;
    stringstream ss;
    for(int i=0;i<len-1;i++){
        ss<<gRand(0,1);
    }
    ss<<0;
    string s=ss.str();
    cout<<"with s: "<<s<<endl;
    cout<<"Starting"<<endl;
    BigNumber checklist[]={2,3,4,5,6,7,8,9,13,17};
    BigNumber allOne;
    BigNumber one(1);
    allOne.setAllOne();
    BigNumber pm1(s),p,pI;
    while(true){
        bool prime=true;
        p.add(pm1,one,p);
        pI.divide(allOne,p,pI);
        BigNumber res;
        int pp=0;
        for(int i=0;i<10;i++){
            res.bie(checklist[i],pm1,p,pI,res);
            if(res.compare(res,one)){
                prime=false;
                break;
            }

            pp++;
        }
        if(prime){
            cout<<"found :"<<endl;
            long long msbB=p.getMSB();
            for(int i=msbB-1;i>=0;i--){
                cout<<p.get(i)?1:0;
            }
            cout<<endl;
        }
        else{
            //cout<<"failed for "<<p<<endl;
        }
        pm1.add(p,one,pm1);
    }
    return 0;
}