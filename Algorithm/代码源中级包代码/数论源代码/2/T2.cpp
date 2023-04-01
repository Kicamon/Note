#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N=10100000;
ll inv[N];
int n, p;

int main() {
    scanf("%d%d", &p, &n);
    inv[1] = 1;
    int ans = 1;
    for (int i = 2; i <= n; i++) {
        inv[i] = (p - p / i) * inv[p % i] % p;
        ans ^= inv[i];
    }
    printf("%d\n", ans);
}