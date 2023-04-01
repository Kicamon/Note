#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef double db;

const int N=1000005;

int n, m;
int h, t, q[N];
ll dp[N];
array<int, 2> p[N], qq[N];

inline ll X(int x) { return -qq[x+1][1]; }
inline ll Y(int x) { return dp[x]; }
inline ll K(int x) { return qq[x][0]; }
inline db slope(int x,int y) { return db(Y(y)-Y(x)) / (X(y)-X(x));}

int main() {
    scanf("%d",&n);
    for (int i = 1; i <= n; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        p[i]={x, y};
    }
    sort(p + 1, p + n + 1);
    int py = 0;
    for (int i = n; i >= 1; i--) {
        if (p[i][1] <= py) continue;
        py = p[i][1];
        qq[++m] = p[i];
    }
    reverse(qq + 1, qq + m + 1);
    h = 1; t = 0;
    q[t++] = 0;
    for (int i = 1; i <= m; i++) {
        ll k = K(i);
        while (h < t && Y(q[h]) - k * X(q[h]) >= Y(q[h + 1]) - k * X(q[h+1]))
            h++;
        dp[i] = Y(q[h]) - k * X(q[h]);
        if (i == m) break;
        while (h < t && slope(q[t], q[t-1]) >= slope(q[t], i)) t--;
        q[++t] = i;
    }
    printf("%lld\n",dp[m]);
    return 0;
}