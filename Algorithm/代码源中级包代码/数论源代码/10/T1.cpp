#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> VL;

VL dp[100],pos[110],spos[110];

ll comb[120][120];
int n, p;

VL operator + (VL a, VL b) {
    VL c(p, 0);
    for (int i = 0; i < p; i++)
        c[i] = a[i] + b[i];
    return c;
}

VL operator * (VL a, VL b) {
    VL c(p, 0);
    for (int i = 0; i < p; i++)
        for (int j = 0; j < p; j++)
            c[i * j % p] += a[i] * b[j];
    return c;
}

VL solve(ll x) {
    x += 1;
    vector<int> d;
    while (x) {
        d.push_back(x % p);
        x /= p;
    }
    reverse(d.begin(), d.end());
    int m = d.size();
    VL ans(p, 0);
    VL pre(p, 0);
    pre[1] = 1;
    // dp[i] 还剩 i 位，mod p = ...
    dp[0] = VL(p, 0); dp[0][1] = 1;
    for (int i = 1; i < m; i++) {
        // 这一位填上 <p ，后面 i - 1 位随便填。
        dp[i] = dp[i - 1] * spos[p];
    }

    // 3 4 2345
    // 3 0???? + 3 1???? + 3 2???? + 3 3????
    // 3 <4 ????
    // 34
    for (int i = 0; i < m; i++) {
        // 前面确定了pre，这一位填 0... d[i] - 1
        ans = ans + pre * spos[d[i]] * dp[m - i - 1];
        pre = pre * pos[d[i]];
    }
    return ans;
}

int main() {
    scanf("%d%d", &n, &p);
    for (int i = 0; i < p; i++) {
        comb[i][0] = comb[i][i] = 1;
        for (int j = 1; j < i; j++)
            comb[i][j] = (comb[i - 1][j - 1] + comb[i - 1][j]) % p;
    }
    // 这一位填 i，然后mod p = 0 ... p - 1的方案
    for (int i = 0; i < p; i++) {
        pos[i] = VL(p, 0);
        for (int j = 0; j <= i; j++) pos[i][comb[i][j]]++;
    }
    // 这一位填 <i，然后mod p = 0 ... p - 1的方案
    spos[0] = VL(p, 0);
    for (int i = 1; i <= p; i++)
        spos[i] = spos[i - 1] + pos[i - 1];
    auto ans = solve(n);
    ll ans0 = (ll)(n + 2) * (n + 1) / 2;
    for (int i = 1; i < p; i++)
        ans0 = ans0 - ans[i];
    ans[0] = ans0;
    for (int i = 0; i < p; i++)
        printf("%lld%c",ans[i]," \n"[i==p-1]);
}