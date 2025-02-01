#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = (1 << 20) + 10;
const int M = 20;
const int mod = 1000000007;

int n;
ll f[N], pw[N];
int main() {
    scanf("%d", &n);
    pw[0] = 1;
    for (int i = 1; i <= n; i++)
        pw[i] = pw[i - 1] * 2 % mod;
    for (int i = 0; i < n; i++) {
        int x;
        scanf("%d", &x);
        f[x]++;
    }
    // x -> how many i  a[i] & x = x
    for (int i = 0; i < M; i++)
        for (int j = 0; j < (1 << M); j++)
            if ((j & (1 << i)) == 0) 
                f[j] += f[j + (1 << i)];
    // H[i] = 2^f[i]
    for (int i = 0; i < (1 << M); i++) f[i] = pw[f[i]];

    // H[i] -> h[i];
    for (int i = 0; i < M; i++)
        for (int j = 0; j < (1 << M); j++)
            if ((j & (1 << i)) == 0) 
                f[j] -= f[j + (1 << i)];
    f[0] %= mod;
    if (f[0] < 0) f[0] +=mod;
    printf("%lld\n", f[0]);
}
 