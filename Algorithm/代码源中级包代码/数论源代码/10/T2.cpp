#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int a, b, m;

// 欧几里得
ll gcd(ll a, ll b) {
    if (b == 0) return a;
    else return gcd(b, a % b);
}

// 快速幂
ll powmod(ll a, ll b, ll mod) {
    ll ret = 1;
    for (; b; b >>= 1) {
        if (b & 1) ret = ret * a % mod;
        a = a * a % mod;
    }
    return ret;
}


// 扩展欧几里得
ll exgcd(ll a, ll b, ll &x, ll &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    ll d = exgcd(b, a % b, y, x);
    y -= (a / b) * x;
    return d;
}

// 求 a * x = b (mod m) 的解
ll modequ(ll a, ll b, ll m) {
    ll x, y;
    ll d = exgcd(a, m, x, y);
    if (b % d != 0) return -1;
    m /= d; a /= d; b /= d;
    x = x * b % m;
    if (x < 0) x += m;
    return x;
}

int MAGIC = 30;
void solve() {
    scanf("%d%d%d",&a, &b, &m);
    ll v = 1;
    for (int i = 0; i < MAGIC; i++) {
        // v = a ^ i mod m
        if (v == b) {
            printf("%d\n", i);
            return;
        }
        v = v * a % m;
    }
    // v * a ^ (x - 30) = b(mod m)
    ll g = gcd(v, m);
    if (b % g != 0) {
        puts("-1");
        return;
    }
    b /= g;
    m /= g;
    a %= m;
    b = modequ(v / g, b, m);

    int T = sqrt(m) + 2;
    v = powmod(a, T, m);
    ll d = 1;
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
        printf("%d\n", ans + MAGIC);
    }
}

int main() {
    int T;
    scanf("%d", &T);
    for (int tc = 0; tc < T; tc++) {
        solve();
    }
}