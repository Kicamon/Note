#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 5077;
const ll inf = 1ll<<60;
int n, opt[maxn][maxn];
ll f[maxn][maxn], a[maxn];

int main() {
    scanf("%d",&n);
    for (int i = 1; i <= n; i++) {
        scanf("%lld",&a[i]);
        a[i] += a[i-1];
        opt[i][i] = i;
    }
    for (int i = n; i >= 1; i--)
        for (int j = i + 1; j <= n; j++){
            ll t = inf;
            int ti = 0;
            //for (int k = i; k <= j - 1; k++)
            for (int k = opt[i][j - 1]; k <= opt[i + 1][j]; k++)
                if (t > f[i][k] + f[k + 1][j] + a[j] - a[i - 1]) {
                    t = f[i][k] + f[k + 1][j] + a[j] - a[i - 1];
                    ti = k;
                }
            f[i][j] = t;
            opt[i][j] = ti;
        }
    printf("%lld\n",f[1][n]);
}