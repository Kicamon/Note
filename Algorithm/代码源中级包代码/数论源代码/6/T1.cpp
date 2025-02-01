#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll powmod(ll a,ll b,ll mod) {
    ll res=1;a%=mod;
    assert(b>=0);
    for(;b;b>>=1) {
        if(b&1)res=res*a%mod;
        a=a*a%mod;
    }
    return res;
}

const int M=1000000;
ll fac[M+10],fnv[M+10];
ll p;
ll binom(ll a,ll b) {
    if (b<0||b>a) return 0;
    return fac[a]*fnv[b]%p*fnv[a-b]%p;
}
int main() {
    int _;
    scanf("%lld%d",&p,&_);
    fac[0]=1;
    for (int i=1;i<=p-1;i++) {
        fac[i]=fac[i-1]*i%p;
    }
    fnv[p-1]=powmod(fac[p-1],p-2,p);
    for (int i=p-1;i>=1;i--) fnv[i-1]=fnv[i]*i%p;
    assert(fnv[0]==1);
    for (;_;_--) {
        ll n,m;
        scanf("%lld%lld",&n,&m);
        ll ans=1;
        while (n>0||m>0) {
            ans=ans*binom(n%p,m%p)%p;
            n/=p; m/=p;
        }
        printf("%lld\n",ans);
    }
}