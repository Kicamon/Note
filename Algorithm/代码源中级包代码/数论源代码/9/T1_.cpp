#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 20010000;
int p[N], pr[N / 5], n, phi[N], tot;
int main() {
    scanf("%d", &n);
    p[1] = 1;
    for (int i = 2; i <= n; i++) {
        if (!p[i]) p[i] = i, phi[i] = i - 1, pr[++tot] = i;
        for (int j = 1; j <= tot && pr[j] * i <= n; j++) {
            p[i * pr[j]] = pr[j];
            if (p[i] == pr[j]) {
                phi[i * pr[j]] = phi[i] * pr[j];
                break;
            } else {
                phi[i * pr[j]] = phi[i] * (pr[j] - 1);
            }
        }
    }
    printf("%u\n", ans);
}