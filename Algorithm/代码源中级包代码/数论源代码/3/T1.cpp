#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

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

void merge(ll &a, ll &b, ll c, ll d) { // d <= 10^9
    // bt=c-a(mod d)
    if (a == -1 && b == -1) return;
    ll x, y;
    ll g = exgcd(b, d, x, y);
    //bx=g(mod d)
    if ((c - a) % g != 0) {
        a = b = -1;
    }
    d /= g; // d'
    ll t0 = ((c - a) / g) % d * x % d;
    if (t0 < 0) t0 += d;
    // t = t0 (mod d')
    a = b * t0 + a;
    b = b * d;
}

void solve() {
    int n;
    scanf("%d", &n);
    ll a = 0, b = 1; // x mod b = a
    for (int i = 0; i < n; i++) {
        int c, d;
        scanf("%d%d", &c, &d);
        merge(a, b, c, d);
    }
    printf("%lld\n", a);
}

int main() {
    int T;
    scanf("%d", &T);
    for (int tc = 0; tc < T; tc++) {
        solve();
    }
}