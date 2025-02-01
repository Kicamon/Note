#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int gcd(int a, int b) {
    if (b == 0) return a;
    else return gcd(b, a % b);
}

int main() {
    int T;
    scanf("%d", &T);
    for (int tc = 0; tc < T; tc++) {
        int a, b;
        scanf("%d%d",&a, &b);
        int d = gcd(a, b);
        printf("%d %lld\n", d, 1ll * a / d * b);
    }
}