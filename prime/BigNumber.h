#ifndef BigNumber_FILE
#define BigNumber_FILE
#include<bits/stdc++.h>
#include<iostream>
class BigNumber{
    long long base;
    long long base2p;
    long long basem1;
    long long *dataStart;
    long long *dataEnd;
    long long SIZE;
    public:
    BigNumber();
    BigNumber(long long number);
    BigNumber(const std::string &binaryString);
    BigNumber(const BigNumber &obj);
    ~BigNumber();
    void init();
    void fromString(const std::string &binaryString);
    void setAllOne(){
        for(int i=0;i<SIZE;i++){
            dataStart[i]=basem1;
        }
    }
    void clear();
    static void shiftLeft(BigNumber &A,long long shift,BigNumber &c);
    static void shiftRight(BigNumber &A,long long shift,BigNumber &c);
    long long getMSB();
    static bool add(BigNumber &A,BigNumber &B,BigNumber &result);
    static void sub(BigNumber &A,BigNumber &B,BigNumber &result);
    static void multiply(BigNumber &A,BigNumber &B,BigNumber &result);
    static void divide(BigNumber &A,BigNumber &B,BigNumber &result);
    static void mod(BigNumber &A,BigNumber &B,BigNumber &BI, BigNumber & result);
    static void bie(BigNumber &A,BigNumber &B,BigNumber &modV,BigNumber &modVI,BigNumber &result);
    void copy(BigNumber &A);

    std::string toString();
    friend std::ostream& operator<<(std::ostream& stream,BigNumber& A);
    long long & operator[](int x){
        if(x<0 ||x>=SIZE) throw std::range_error("out of range request");
        return dataStart[SIZE-x-1];
    }
    bool get(long long n){
        return operator[](n/base2p)&(1ll<<(n%base2p));
    }
    void set(long long n){
        operator[](n/base2p)|=(1ll<<(n%base2p));
    }
    static int compare(BigNumber &A,BigNumber&B);

};

#include "BigNumber.cpp"
#endif