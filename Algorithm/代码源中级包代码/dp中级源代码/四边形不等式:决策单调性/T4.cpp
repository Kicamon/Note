#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double db;

const int N = 1000005;

int n, l, p, s[N];
char t[40];
pair<int,int> stk[N];
db dp[N];

void solve() {
    scanf("%d%d%d",&n, &l, &p);
    ++l;
    for (int i = 1; i <= n; i++) {
        scanf("%s", t);
        s[i] = s[i - 1] + strlen(t) + 1;
    }
    int h = 0 , t = 0;
    stk[t++] = {1, 0};
    auto pw = [](int x) {
        db ans = 1;
        for (int i = 0; i < p; i++) ans *= x;
        return ans;
    };
    auto calc = [&](int i, int j) {
        return dp[j] + pw(abs(s[i] - s[j] - l));
    };
    for (int i = 1; i <= n; i++) {
        if (h < t && stk[h].first < i) stk[h].first++;
        if (h + 1 < t && stk[h].first >= stk[h + 1].first) ++h;
        dp[i] = calc(i, stk[h].second);
        while (h < t && calc(stk[t - 1].first, stk[t-1].second) >= calc(stk[t-1].first,i))
                --t;
        if (h < t) {
            int l = stk[t - 1].first, r = n + 1;
            while (l + 1 < r) {
                int md = (l + r) >> 1;
                if (calc(md, stk[t - 1].second) < calc(md, i)) l = md; else r = md;
            }
            if (r <= n) stk[t++] = {r, i};
        } else stk[t++]={i, i};
    }
    if (dp[n] > 1e18) puts("Too hard to arrange");
    else printf("%lld\n",(ll)dp[n]);
    puts("--------------------");
}

int main() {
    int T;
    scanf("%d",&T);
    for (; T; T--) {
        solve();
    }
}