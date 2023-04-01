#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int exgcd(int a, int b, int &x, int &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    int d = exgcd(b, a % b, y, x);
    y -= (a / b) * x;
    return d;
}

unsigned int A, B, C;
inline unsigned int rng61() {
    A ^= A << 16;
    A ^= A >> 5;
    A ^= A << 1;
    unsigned int t = A;
    A = B;
    B = C;
    C ^= t ^ A;
    return C;
}
const int N=10100000;
int p, n, a[N];
ll s[N], t[N];

int main() {
    scanf("%d%d%u%u%u", &p, &n, &A, &B, &C);
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        a[i] = rng61()%p;
        if (a[i] == 0) {
            a[i] = 1;
            ans ^= 1;
        }
    }
    s[0] = 1;
    for (int i = 1; i <= n; i++) s[i] = s[i - 1] * a[i] % p;
    int x, y;
    exgcd(s[n], p, x, y);
    if (x < 0) x += p;
    t[n] = x;
    assert(s[n] * x % p == 1);
    for (int i = n; i >= 1; i--) t[i - 1] = t[i] * a[i] %p;
    for (int i = 1; i <= n; i++) {
        int v = s[i - 1] * t[i] %p;
        ans ^= v;
    }
    printf("%d\n", ans);
}
