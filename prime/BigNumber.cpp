#include "BigNumber.h"

BigNumber::BigNumber(){
    init();
}
BigNumber::BigNumber(long long number){
    init();
    long long *endptr=dataEnd;
    while(number){
        if(endptr+1==dataStart){
            //std::clog<<"log: Value too large to create"<<std::endl;
            break;
        }
        *endptr=number&basem1;
        endptr--;
        number=number>>base2p;
    }
}
BigNumber::BigNumber(const std::string &binaryString){
    init();
    fromString(binaryString);
}
BigNumber::BigNumber(const BigNumber &obj){
    init();
    for(int i=0;i<SIZE;i++){
        dataStart[i]=obj.dataStart[i];
    }
}
BigNumber::~BigNumber(){
    delete [] dataStart;
}

void BigNumber::init(){
    base2p=25;
    base=(1ll<<base2p);
    basem1=base-1;
    SIZE=100; //can only be an even number.
    dataStart=new long long [SIZE]{};
    dataEnd=dataStart+(SIZE-1);
}

void BigNumber::fromString(const std::string &binaryString){
    clear();
    if(binaryString.length()>SIZE*base2p){
        throw std::runtime_error("Can't hold data as max.");
    }
    long long *endptr=dataEnd;
    int n=binaryString.length()/base2p;
    for(int i=0;i<n;i++){
        int pnt=binaryString.length()-(i+1)*base2p;
        long long v=0;
        for(int j=pnt;j<pnt+base2p;j++){
            v=(v<<1)+(binaryString[j]-'0');
        }
        *endptr=v;
        endptr--;
    }
    int rb=binaryString.length()%base2p;
    if(rb){
        long long v=0;
        for(int j=0;j<rb;j++){
            v=(v<<1)+(binaryString[j]-'0');
        }
        *endptr=v;
    }
}

void BigNumber::clear(){
    for(int i=0;i<SIZE;i++){
        dataStart[i]=0;
    }
}

void BigNumber::shiftLeft(BigNumber &A,long long n,BigNumber &C){
   C.clear();
   for(int i=n;i<A.SIZE*A.base2p;i++){
        if(A.get(i-n)){
            C.set(i);
        }
   }
}
void BigNumber::shiftRight(BigNumber &A,long long n,BigNumber &C){
   C.clear();
   for(int i=n;i<A.SIZE*A.base2p;i++){
        if(A.get(i)){
            C.set(i-n);
        }
   }
}
long long BigNumber::getMSB(){
    long long ans=0;
    for(int i=0;i<SIZE;i++){
        if(dataStart[i]==0) ans+=base2p;
        else{
            long long q=dataStart[i];
            long long v=0;
            while(q) {
                v+=1;
                q>>=1;
            }
            ans+=base2p-v;
            break;
        }
    }
    return SIZE*base2p-ans;
}

bool BigNumber::add(BigNumber &A,BigNumber &B,BigNumber &C){
    long long carry=0;
    for(int i=0;i<A.SIZE;i++){
        long long q=A[i]+B[i]+carry;
        C[i]=q&A.basem1;
        carry=q>>A.base2p;
    }
    if(carry){
        return false;
    }
    return true;
}
void BigNumber::sub(BigNumber &A,BigNumber &B,BigNumber &C){
    int carry=0;
    for(int i=0;i<A.SIZE;i++){
        if(A[i]+carry<B[i]){
            C[i]=A.base+A[i]+carry-B[i];
            carry=-1;
        }
        else{
            C[i]=A[i]+carry-B[i];
            carry=0;
        }
    }
    if(carry==-1){
       
        throw std::runtime_error("Tried subtracting bigger number form smaller number.");
    }
}
void BigNumber::multiply(BigNumber &A,BigNumber &B,BigNumber &C){
    long long carry=0;
    for(int i=0;i<A.SIZE;i++){
        long long val=carry;
        long long newCarry=0;
        for(int j=0;j<=i;j++){
            val+=A[j]*B[i-j];
            newCarry+=val>>A.base2p;
            val=val&A.basem1;
        }
        C[i]=val;
        carry=newCarry;
    }
    if(carry){
        std::clog<<"log: Made an overflow multiplication "<<A<<" with "<<B<<std::endl;
    }
}

void BigNumber::divide(BigNumber &A,BigNumber &B,BigNumber &C){
    long long msbB=B.getMSB();
    long long finallength=B.SIZE*B.base2p -msbB;
    BigNumber AuxilarySum,TSUM;
    std::stringstream ss;
    for(int i=0;i<=finallength;i++){
        B.shiftLeft(B,finallength-i,C);
        bool overflow=!(AuxilarySum.add(AuxilarySum,C,TSUM));
        if(overflow || TSUM.compare(TSUM,A)==1){
            ss<<0;
        }
        else{
            AuxilarySum.copy(TSUM);
            ss<<1;
        }
    }
    C.fromString(ss.str());
}

void BigNumber::mod(BigNumber &A,BigNumber &B,BigNumber &C, BigNumber &result){
    BigNumber A1,A2,C1,C2;
    long long hs=A.SIZE/2;
    for(int i=0;i<hs;i++){
        A1.dataStart[i+hs]=A.dataStart[i];
        C1.dataStart[i+hs]=C.dataStart[i];
    }
    for(int i=hs;i<A.SIZE;i++){
        A2.dataStart[i]=A.dataStart[i];
        C2.dataStart[i]=C.dataStart[i];
    }
    result.multiply(A1,C1,result);
    BigNumber temp;
    temp.multiply(A1,C2,temp);
    for(int i=0;i<hs;i++){
        temp.dataStart[i+hs]=temp.dataStart[i];
        temp.dataStart[i]=0;
    }
    result.add(result,temp,result);
    temp.multiply(A2,C1,temp);
    for(int i=0;i<hs;i++){
        temp.dataStart[i+hs]=temp.dataStart[i];
        temp.dataStart[i]=0;
    }
    result.add(result,temp,result);
    temp.multiply(result,B,temp);
    result.sub(A,temp,result);
    while(result.compare(B,result)!=1){
        result.sub(result,B,result);
    }
}
void BigNumber::bie(BigNumber &A,BigNumber &B,BigNumber &modV,BigNumber &modVI,BigNumber &result){
    result.clear();
    BigNumber temp(1);
    BigNumber power(A);
    BigNumber temp2;
    long long msbB=B.getMSB();
    for(int i=0;i<msbB;i++){
        if(B.get(i)){
            temp2.multiply(power,temp,temp2);
            temp.mod(temp2,modV,modVI,temp);
        }
        temp2.multiply(power,power,temp2);
        power.mod(temp2,modV,modVI,power);
    }
    result.copy(temp);
}
void BigNumber::copy(BigNumber &A){
    for(int i=0;i<SIZE;i++){
        dataStart[i]=A.dataStart[i];
    }
}
std::string BigNumber::toString(){
    std::stringstream ss;
    for(int i=0;i<SIZE-1;i++){
        ss<<dataStart[i]<<":";
    }
    ss<<dataStart[SIZE-1];
    return ss.str();
}

std::ostream& operator<<(std::ostream& stream,BigNumber& A){
    for(int i=0;i<A.SIZE-1;i++){
        stream<<A.dataStart[i]<<":";
    }
    stream<<A.dataStart[A.SIZE-1];
    return stream;
}
int BigNumber::compare(BigNumber &A,BigNumber &B){
    for(int i=0;i<A.SIZE;i++){
        if(A.dataStart[i]>B.dataStart[i]) return 1;
        if(A.dataStart[i]<B.dataStart[i]) return -1;
    }
    return 0;
}