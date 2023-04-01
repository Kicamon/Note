#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef double db;

const int N=1000005;

int n, p;
ll sum[N];
int h, t, q[N];
ll dp[N];

inline ll X(int x) { return sum[x];}
inline ll Y(int x) { return dp[x] + sum[x] * sum[x];}
inline ll K(int x) { return 2 * (sum[x] - p);}
inline db slope(int x, int y) { return db(Y(y)-Y(x)) / (X(y)-X(x));}

int main() {
    scanf("%d%d", &n, &p);
    p++;
    for(int i = 1; i <= n; i++) {
        int x;
        scanf("%d",&x);
        sum[i] = sum[i - 1] + x + 1;
    }
    h = 1; t = 0;
    q[++t] = 0;
    for (int i = 1; i <= n; i++) {
        ll k = K(i);
        while (h < t && Y(q[h]) - k * X(q[h]) >= Y(q[h + 1]) - k * X(q[h + 1]))
            h++;
        dp[i] = dp[q[h]] + (sum[i] - sum[q[h]] - p) * (sum[i] - sum[q[h]] - p);
        while (h < t && slope(q[t], q[t - 1]) >= slope(q[t], i)) t--;
        q[++t] = i;
    }
    printf("%lld\n",dp[n]);
    return 0;
}