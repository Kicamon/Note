#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll gcd(ll a, ll b) {
    if (b == 0) return a;
    else return gcd(b, a % b);
}

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

const ll inf = 1ll << 60;
int n, m, q;

ll merge(ll a, ll b, ll c, ll d) {
    ll x, y;
    ll g = exgcd(b, d, x, y);
    if ((c - a) % g != 0) return inf;
    d /= g;
    ll t0 = ((c - a) / g) % d * x % d;
    if (t0 < 0) t0 += d;
    return b * t0 + a;
}

ll solve(ll x, ll y) {
    x = (x + 2 * n) % (2 * n);
    y = (y + 2 * m) % (2 * m);
    return merge(x, 2 * n, y, 2 * m);
}

int main() {
    scanf("%d%d%d", &n, &m, &q);
    ll T = n / gcd(n, m) * m;
    for (int i = 0; i < q; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        ll ans = min({solve(x, y), solve(-x, y),
            solve(x, -y), solve(-x, -y)});
        if (ans > T) puts("-1");
        else printf("%lld\n", ans);
    }
}