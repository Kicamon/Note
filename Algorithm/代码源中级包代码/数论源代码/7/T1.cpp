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


int calc(int p) {
    if (p == 1) return 0;
    int phip = p, q = p;
    for (int i = 2; i * i <= q; i++) if (q % i == 0) {
        phip = phip / i * (i - 1);
        while (q % i == 0) q /= i;
    }
    if (q != 1) phip = phip / q * (q - 1);
    return powmod(2, calc(phip) + phip, p);
}

void solve() {
    int p;
    scanf("%d", &p);
    printf("%d\n", calc(p));
}

int main() {
    int T;
    scanf("%d", &T);
    for (int tc = 0; tc < T; tc++) {
        solve();
    }
}