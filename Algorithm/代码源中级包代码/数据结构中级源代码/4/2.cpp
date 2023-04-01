#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 1010000;
int n, q, lg[N];
unsigned int A, B, C, a[N], f[22][N], ans;

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
int main(){
    scanf("%d%d%u%u%u", &n, &q, &A, &B, &C);
    for (int i = 1; i <= n; i++) {
        a[i] = rng61();
        f[0][i] = a[i];
    }
    for (int j = 1; j <= 20; j++) {
    	for (int i = 1; i + (1 << j) - 1 <= n; i++) {
    		f[j][i] = max(f[j - 1][i], f[j - 1][i + (1 << (j - 1))]);
    	}
    }
    for (int i = 1; i <= q; i++) {
        unsigned int l = rng61() % n + 1, r = rng61() % n + 1;
        if (l > r) swap(l, r);
        int len = 31 - __builtin_clz(r - l + 1);
        ans ^= max(f[len][l], f[len][r - (1 << len) + 1]);
    }
    printf("%u\n", ans);
}