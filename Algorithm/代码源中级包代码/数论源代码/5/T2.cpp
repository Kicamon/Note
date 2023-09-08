#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 10000000;
const int mod = 1000000007;

ll powmod(ll a, ll b) {
    ll ret = 1;
    for (; b; b >>= 1) {
        if (b & 1) ret = ret * a % mod;
        a = a * a %mod;
    }
    return ret;
}

ll fac[N + 10], fnv[N + 10];

ll binom(int n, int m) {
    if (m < 0 || m > n) return 0;
    return fac[n] * fnv[m] % mod * fnv[n - m] % mod;
}

int main() {
    fac[0] = 1;
    for (int i = 1; i <= N; i++)
        fac[i] = fac[i - 1] * i % mod;
    fnv[N] = powmod(fac[N], mod - 2);
    for (int i = N; i >= 1; i--)
        fnv[i - 1] = fnv[i] * i %mod;
    assert(fnv[0] == 1);
    int T;
    scanf("%d", &T);
    for (int tc = 0; tc < T; tc++) {
        int a, b;
        scanf("%d%d", &a, &b);
        printf("%lld\n", binom(a, b));
    }
}