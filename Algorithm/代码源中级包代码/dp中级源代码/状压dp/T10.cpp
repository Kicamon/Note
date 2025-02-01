#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define bit(x) (1 << (x))
const int M = 40;
const int inf = 0x20202020;

int n, w[M][M];
pair<int,int> p1[M], p2[M];
char s[M][M];
int dp[(1 << 24) + 10];

void upd(int &a, int b) {
    if (a > b) a = b;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) scanf("%s", s[i]);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &w[i][j]);
    memset(dp, 0x20, sizeof(dp));
    dp[bit(2 * n) - bit(n)] = 0;
    for (int S = bit(2 * n) - 1; S >= 0; S--) if (dp[S] < inf) {
        int x = 0, y = 0;
        int c1 = 0, c2 = 0;
        for (int i = 0; i < 2 * n; i++) {
            if (((S >> i) & 3) == 2) {
                upd(dp[S ^ (3 << i)], dp[S] + w[x][y]);
                if (s[x][y] == 'W') p1[c1++] = {i, w[x][y]};
                if (s[x][y] == 'B') p2[c2++] = {i, w[x][y]};
            }
            if (S & bit(i)) y++; else x++;
        }
        for (int i = 0; i < c1; i++) for (int j = 0; j < c2; j++)
            upd(dp[S ^ (3 << p1[i].first) ^ (3 << p2[j].first)],
                dp[S] + abs(p1[i].second - p2[j].second));
    }
    printf("%d\n", dp[bit(n) - 1]);
}