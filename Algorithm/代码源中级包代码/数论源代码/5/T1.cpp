#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int exgcd(int a, int b,int &x,int &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    int d = exgcd(b, a % b, y, x);
    y -= (a / b) * x;
    return d;
}

ll floordiv(ll a, ll b) {
    if (a % b == 0) return a / b;
    else if (a > 0) return a / b;
    else return a / b - 1;
}

ll ceildiv(ll a, ll b) {
    if (a % b == 0) return a / b;
    else if (a > 0) return a / b + 1;
    else return a / b;
}


int main() {
    int T;
    scanf("%d", &T);
    for (int tc = 0; tc < T; tc++) {
        int a, b, x, y;
        ll l1, r1, l2, r2;
        ll m;
        scanf("%d%d%lld%lld%lld%lld%lld",
            &a, &b, &m, &l1, &r1, &l2, &r2);
        int d = exgcd(a, b, x, y);
        if (m % d != 0) {
            puts("0");
            continue;
        }
        a /= d;
        b /= d;
        m /= d;
        ll xx = (ll)x * (m % b) % b;
        if (xx < 0) xx += b;
        ll yy = (m - a * xx) / b;
        // l1 <= xx + b * t <= r1
        // l2 <= yy - a * t <= r2
        ll r = min(floordiv(r1 - xx, b), floordiv(yy - l2, a));
        ll l = max(ceildiv(l1 - xx, b), ceildiv(yy - r2, a));
        if (l > r) puts("0");
        else printf("%lld\n", r - l + 1);
    }
}