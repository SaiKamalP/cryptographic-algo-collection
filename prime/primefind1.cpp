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
vector<pair<BigNumber,BigNumber>> smallPrimes;
BigNumber zero(0);
bool checkdiv(BigNumber &A,BigNumber &B,BigNumber &Bi){
    BigNumber tempBigNumber;
    A.mod(A,B,Bi,tempBigNumber);
    if(tempBigNumber.compare(tempBigNumber,zero)==0){
        return true;
    }
    return false;
}
void primeFinder(int tn,int len=300){
    stringstream ss;
    ss<<1;
    for(int i=1;i<len-1;i++){
        ss<<gRand(0,1);
    }
    ss<<0;
    string s=ss.str();
    //cout<<tn<<" with s: "<<s<<endl;
    cout<<"Starting thread"<<tn<<endl;
    BigNumber checklist[]={2,3,4,5,6,7,8,9,13,17};
    BigNumber allOne;
    BigNumber one(1);
    allOne.setAllOne();
    BigNumber pm1(s),p,pI;
    while(true){
        bool prime=true;
        p.add(pm1,one,p);
        for(auto i:smallPrimes){
            if(checkdiv(p,i.first,i.second)){
                prime=false;
                break;
            }
        }
        if(prime){
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
        }
        if(prime){
            cout<<"found on thread"<<tn<<":"<<endl;
            long long msbB=p.getMSB();
            for(int i=msbB-1;i>=0;i--){
                cout<<p.get(i)?1:0;
            }
            cout<<endl;
            break;
        }
        pm1.add(p,one,pm1);
    }
    primeFinder(tn,len);
}
int main() {
    int n=20;
    int len=500;
    cout<<"number of threads: ";
    cin>>n;
    cout<<endl;
    cout<<"lenght of bits: ";
    cin>>len;
    cout<<endl;
    vector<long long>sprimes=  {3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73,
                                79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173,
                                179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277,
                                281, 283, 293, 307, 311, 313, 317, 331, 337, 347, 349, 353, 359, 367, 373, 379, 383, 389, 397,
                                401, 409, 419, 421, 431, 433, 439, 443, 449, 457, 461, 463, 467, 479, 487, 491, 499, 503, 509,
                                521, 523, 541, 547, 557, 563, 569, 571, 577, 587, 593, 599, 601, 607, 613, 617, 619, 631, 641,
                                643, 647, 653, 659, 661, 673, 677, 683, 691, 701, 709, 719, 727, 733, 739, 743, 751, 757, 761,
                                769, 773, 787, 797, 809, 811, 821, 823, 827, 829, 839, 853, 857, 859, 863, 877, 881, 883, 887,
                                907, 911, 919, 929, 937, 941, 947, 953, 967, 971, 977, 983, 991, 997, 1009, 1013, 1019, 1021,
                                1031, 1033, 1039, 1049, 1051, 1061, 1063, 1069, 1087, 1091, 1093, 1097, 1103, 1109, 1117, 1123,
                                1129, 1151, 1153, 1163, 1171, 1181, 1187, 1193, 1201, 1213, 1217, 1223, 1229, 1231, 1237, 1249,
                                1259, 1277, 1279, 1283, 1289, 1297, 1301, 1303, 1307, 1319, 1321, 1327, 1361, 1367, 1373, 1381,
                                1399, 1409, 1423, 1427, 1429, 1433, 1439, 1447, 1451, 1453, 1459, 1471, 1481, 1483, 1487, 1489,
                                1493, 1499};
    cout<<"Started pre computation of 2^n/p for the primes till 1500 execpt 2."<<endl;
    BigNumber a;
    a.setAllOne();
    for(auto i:sprimes){
        BigNumber b(i),bi;
        b.divide(a,b,bi);
        smallPrimes.push_back({b,bi});
    }
    cout<<"Done pre computation of 2^n/p for the primes till 1500 execpt 2."<<endl<<"Starting threads."<<endl;
    vector<thread> finders;
    for(int i=0;i<n;i++){
        finders.emplace_back(primeFinder,i+1,len);
    }
    for(thread &x:finders){
       x.join();
    }
    return 0;
}