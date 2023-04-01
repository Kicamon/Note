#include<bits/stdc++.h>
#define ll long long
using namespace std;
int n, m, d;
ll f[300100], dp[300100];
int p[300100];
int main(){
    cin >> n >> m >> d;
    int t1 = 1;
    while(m--){
        int a, b, t;
        scanf("%d%d%d", &a, &b, &t);
        int D = min(1ll * n,1ll * (t - t1) * d);
        t1 = t;
        int l = 1, r = 0;
        auto add = [&](int x) {
            while (l <= r && f[p[r]] <= f[x]) r--;
            p[++r] = x;
        };
        for (int i = 1; i <= D; i++) add(i);
        for (int i = 1; i <= n; i++) {
            if (i + D <= n) add(i + D);
            while (l <= r && p[l] < i - D) l++;
            dp[i] = f[p[l]] + b - abs(a - i);
        }
        for (int i = 1; i <= n; i++) f[i] = dp[i];
    }
    printf("%lld\n",*max_element(f + 1, f + n + 1));
}