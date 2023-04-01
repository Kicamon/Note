#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll powmod(ll a,ll b,ll mod) {
    ll res = 1; a%=mod;
    for(;b;b>>=1) {
        if(b&1)res=res*a%mod;
        a=a*a%mod;
    }
    return res;
}

int a, b, m;
void solve() {
    scanf("%d%d%d",&a, &b, &m);
    int T = sqrt(m) + 2;
    ll v = powmod(a, T, m), d = 1;
    map<int, int> hs;
    for (int q = 1; q <= T; q++) {
        d = d * v % m;
        if (!hs.count(d)) hs[d] = q * T;
    }
    int ans = m + 1;
    d = b;
    for (int r = 1; r <= T; r++) {
        d = d * a % m;
        if (hs.count(d)) ans = min(ans, hs[d] - r);
    }
    if (ans >= m) {
        puts("-1");
    } else {
        printf("%d\n", ans);
    }
}

int main() {
    int T;
    scanf("%d", &T);
    for (int tc = 0; tc < T; tc++) {
        solve();
    }
}