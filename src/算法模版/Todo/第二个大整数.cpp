//#include <bits/stdc++.h>
#include <iostream>
#include <iomanip>
#include <math.h>
#include <cmath>
#include <algorithm>
#include <climits>
#include <functional>
#include <cstring>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cstdio>
#include <vector>
#include <stack>
#include <queue>
#include <deque>
#include <map>
#include <set>
#include <bitset>
#include <complex>
#include <random>
#ifndef __x86_64__
#error Only x86-64 targets are supported
#endif
#include<cstdint>
#include<vector>
#include<string>
#include<iosfwd>
//#define __builtin_ia32_adc(x,y,flag) __asm__("addb   %3, %0\n\t" "adcq   %2, %1\n\t" "setc   %0":"+r"(flag),"+r"(x):"r"(y),"i"(-1):"cc")
void __builtin_ia32_adc(unsigned long long &x, unsigned long long y, bool &flag) {
    __int128 t = x;
    t += y;t+=flag;
    x = t&0xffffffffffffffff;
    flag = (t>>64)&0x1;
}

struct bigint{// made by dengyaotriangle!
    typedef unsigned long long u64;
    typedef unsigned __int128 u128;
    typedef std::size_t st;
    std::vector<u64> data;
    bigint()= default;
    bigint(u64 x):data(x?std::vector<u64>{x}:std::vector<u64>{}){}
    bigint(const std::string &s){
        //二进制
        st pos=s.length();
        int cnt=0;
        u64 val=0;
        while(pos){
            pos--;
            if(cnt==64){
                data.push_back(val);
                val=0;cnt=0;
            }
            val|=(u64)(s[pos]=='1')<<cnt;
            ++cnt;
        }
        if(cnt&&val)data.push_back(val);
    }
    bigint(const bigint& rhs) {
        data = rhs.data;
    }
    bigint(bigint&& rhs) {
        data = std::move(rhs.data);
    }
    bigint& operator = (const bigint& rhs) {
        data = rhs.data;
        return *this;
    }
    bigint& operator = (bigint&& rhs) {
        data = std::move(rhs.data);
        return *this;
    }

    explicit operator std::string()const{
        if(data.empty())return "0";
        bool t=0;
        std::string ret;
        for(int i=63;i>=0;i--){
            t|=(data.back()>>i)&1;
            if(t)ret+='0'|((data.back()>>i)&1);
        }
        st i=data.size()-1;
        while(i){
            i--;
            for(int j=63;j>=0;j--)ret+='0'|((data[i]>>j)&1);
        }
        return ret;
    }
    explicit operator bool()const{return !data.empty();}
    explicit operator u64()const{return data.empty()?0:data[0];}
    st digit()const{
        if(data.empty())return 0;
        return (data.size()<<6)-__builtin_clzll(data.back());
    }
    bool operator==(const bigint &a)const{return a.data==data;}
    bool operator!=(const bigint &a)const{return a.data!=data;}
    bool operator<(const bigint &a)const{
        if(data.size()!=a.data.size())return data.size()<a.data.size();
        for(st i=data.size();i;){
            i--;
            if(data[i]!=a.data[i])return data[i]<a.data[i];
        }
        return 0;
    }
    bool operator>(const bigint &a)const{return a<(*this);}
    bool operator<=(const bigint &a)const{return !(*this>a);}
    bool operator>=(const bigint &a)const{return !(*this<a);}
    bigint &operator<<=(st n){
        if(data.empty())return *this;
        int w=n&63;st z=n>>6;
        st i=data.size();
        bool flg=0;
        if(w&&(data.back()>>(64-w)))data.push_back(0),flg=1;
        data.resize(data.size()+z);
        while(i){
            i--;
            if(flg)data[i+z+1]|=data[i]>>(64-w);
            data[i+z]=data[i]<<w;
            flg|=bool(w);
        }
        for(st i=0;i<z;i++)data[i]=0;
        return *this;
    }
    bigint &operator>>=(st n){
        int w=n&63;st z=n>>6,i=0;
        for(;i+z<data.size();i++){
            if(w&&i)data[i-1]|=data[i+z]<<(64-w);
            data[i]=data[i+z]>>w;
        }
        while(data.size()>i)data.pop_back();
        while(!data.empty()&&data.back()==0)data.pop_back();
        return *this;
    }
    bigint operator<<(st n)const{return bigint(*this)<<=n;}
    bigint operator>>(st n)const{return bigint(*this)>>=n;}
    bigint &operator+=(const bigint &a){
        data.resize(std::max(data.size(),a.data.size()));
        bool carry=0;
        for(st i=0;i<data.size();i++){
            u64 rg=0;
            if(i<a.data.size())rg=a.data[i];
            __builtin_ia32_adc(data[i],rg,carry);
        }
        if(carry)data.push_back(1);
        return *this;
    }
    bigint &operator-=(const bigint &a){
        bool carry=1;
        for(st i=0;i<data.size();i++){
            u64 rg=-1;
            if(i<a.data.size())rg=~a.data[i];
            __builtin_ia32_adc(data[i],rg,carry);
        }
        while(!data.empty()&&data.back()==0)data.pop_back();
        return *this;
    }
    bigint &operator++(){return *this+=bigint(1);}
    bigint &operator--(){return *this-=bigint(1);}
    bigint operator++(int){bigint tmp=*this;++*this;return tmp;}
    bigint operator--(int){bigint tmp=*this;--*this;return tmp;}
    bigint &operator*=(const bigint &a){
        std::vector<u64> ret(data.size()+a.data.size());
        for(st i=0;i<data.size();i++){
            u64 carry=0; bool wcarry=0;
            st k=i;
            for(st j=0;j<a.data.size();j++,k++){
                u128 r=data[i]*(u128)a.data[j]+carry;
                u64 cur=r;
                carry=r>>64;
                __builtin_ia32_adc(ret[k],cur,wcarry);
            }
            while(carry||wcarry){
                __builtin_ia32_adc(ret[k],carry,wcarry);
                carry=0;k++;
            }
        }
        while(!ret.empty()&&ret.back()==0)ret.pop_back();
        data=ret;
        return *this;
    }
    bigint &operator/=(const bigint &a){
        if(*this < a) (*this) = 0;
        else {
            if (a.digit() > digit()) {
                data.clear();
                return *this;
            }
            st z = digit() - a.digit();
            std::vector<u64> ret;
            while (1) {
                bigint tmp = a << z;
                if (tmp <= *this) {
                    *this -= tmp;
                    st v1 = z >> 6;
                    if (ret.size() <= v1)ret.resize(v1 + 1);
                    ret[v1] |= (u64) (1) << (z & 63);
                }
                if (!z)break;
                z--;
            }
            data = ret;
        }
        return *this;
    }
    bigint &operator%=(const bigint &a){
        if(a.digit()>digit())return *this;
        st z=digit()-a.digit();
        while(1){
            bigint tmp=a<<z;
            if(tmp<=*this)*this-=tmp;
            if(!z)break;
            z--;
        }
        return *this;
    }
    bigint operator+(const bigint &a)const{return bigint(*this)+=a;}
    bigint operator-(const bigint &a)const{return bigint(*this)-=a;}
    bigint operator*(const bigint &a)const{return bigint(*this)*=a;}
    bigint operator/(const bigint &a)const{return bigint(*this)/=a;}
    bigint operator%(const bigint &a)const{return bigint(*this)%=a;}
};
std::istream &operator>>(std::istream &st,bigint &a){
    while (isspace(st.peek()))
        st.ignore();
    std::string s;st>>s;
    a = 0;
    for(auto i: s){
        a*=10;
        a+=i-'0';
    }
    return st;
}
std::ostream &operator<<(std::ostream &st,const bigint &a){
    if(a==0) st<<0;
    else{
        bigint t = a;
        std::string ans;
        while (t!=0) {
            ans += (char)(((unsigned long long)(t % 10))+'0');
            t /= 10;
        }
        std::reverse(ans.begin(),ans.end());
        st<<ans;
    }
    return st;
}
//#include <ext/pb_ds/assoc_container.hpp>
//#include <ext/pb_ds/tree_policy.hpp>
#define itn int
#define nit int
#define ll long long
#define ms multiset
#define F(i,a,b) for(register int i=a,i##end=b;i<=i##end;++i)
#define UF(i,a,b) for(register int i=a,i##end=b;i>=i##end;--i)
#define re register
#define ri re int
#define il inline
#define pii pair<int,int>
#define cp complex<double>
#define vi vector<int>
#define ull unsigned long long
#define mem0(x) memset(x,0,sizeof(x))
#define mem0x3f(x) memset(x,0x3f,sizeof(x))
using namespace std;
using std::bitset;
//using namespace __gnu_pbds;
const double Pi=acos(-1);
namespace fastIO {
    template<class T>
    inline void read(T &x) {
        x=0;
        bool fu=0;
        char ch=0;
        while(ch>'9'||ch<'0') {
            ch=getchar();
            if(ch=='-')fu=1;
        }
        while(ch<='9'&&ch>='0') x=(x*10+(ch-48)),ch=getchar();
    }
    inline int read() {
        int x=0;
        bool fu=0;
        char ch=0;
        while(ch>'9'||ch<'0') {
            ch=getchar();
            if(ch=='-')fu=1;
        }
        while(ch<='9'&&ch>='0') x=(x*10-48+ch),ch=getchar();
        return x;
    }
    template<class T,class... Args>
    inline void read(T& t,Args&... args) {
        read(t);
        read(args...);
    }
    char _n_u_m_[40];
    template<class T>
    inline void write(T x) {
        if(x==0){
            putchar('0');
            return;
        }
        T tmp = x;
        int cnt = 0 ;
        while( tmp > 0 ) {
            _n_u_m_[ cnt ++ ] = (ull)(tmp % 10) + '0' ;
            tmp /= 10 ;
        }
        while( cnt > 0 ) putchar(_n_u_m_[ -- cnt ]) ;
    }
    template<class T>
    inline void write(T x ,char ch) {
        write(x);
        putchar(ch);
    }
}
using namespace fastIO;
bigint gcd(bigint a, bigint b) {
    bigint temp;
    while (b != 0) {
        temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

bigint lcm(bigint a, bigint b) {
    return (a/gcd(a,b))*b;
}
bigint a,b;
int main() {
    //freopen("D:\\444_unix.in", "r", stdin);
    //freopen("D:\\444_test.txt", "w", stdout);

    int x,y;
    std::string s;

    while(std::cin>>x>>y) {
        std::cin >> s;
        a = 0;
        for (auto i: s) {
            a *= x;
            if (i>='0' and i<='9') a += (i - '0');
            else if (i >= 'A' and i <= 'Z') a += (i - 'A') + 10;
            else a += i - 'a' + 36;
        }

        if (a == 0) {
            std::cout << 0 << endl;
        } else {
            std::string ans;
            while (a != 0) {
                ll k = (bigint::u64) (a % y);
                a /= y;
                if (k < 10) ans += (char) ('0' + k);
                else if (k < 36) ans += (char) ('A' + k - 10);
                else ans += (char) ('a' + k - 36);
            }
            std::reverse(ans.begin(), ans.end());
            std::cout << ans << endl;
        }
    }
    return 0;
}


