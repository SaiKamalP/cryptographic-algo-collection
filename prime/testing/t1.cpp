#include <bits/stdc++.h>
 
using namespace std;
 void func(int x){
    for(int i=0;i<10000000;i++)
    cout<<"Hello wolrd "<<x<<endl;
 }
int main() {
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    thread t1(func,1);
    thread t2(func,2);
    thread t3(func,3);
    thread t4(func,4);
    thread t5(func,5);
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    
    return 0;
}