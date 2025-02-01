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

int main() {
    int T;
    scanf("%d", &T);
    for (int tc = 0; tc < T; tc++) {
        int a, b, x, y;
        ll m;
        scanf("%d%d%lld",&a, &b, &m);
        int d = exgcd(a, b, x, y);
        if (m % d != 0) {
            puts("-1");
            continue;
        }
        a /= d;
        b /= d;
        m /= d;
        // a x + b y = m 10^18   x 10^9
        ll xx = (ll)x * (m % b) % b;
        if (xx < 0) xx += b;
        ll yy = (m - a * xx) / b;
        if (yy < 0) {
            puts("-1");
        } else {
            printf("%lld %lld\n",(ll)xx, (ll)yy);
        }
    }
}