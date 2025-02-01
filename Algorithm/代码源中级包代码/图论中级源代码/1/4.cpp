#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 101000;
vector<int> e[N];

int n, m, mod, cnt;

int dfn[N], low[N], ins[N], bel[N], idx;
stack<int> stk;
int val[N], bar[N];
ll dp[N];

void dfs(int u)
{
    dfn[u] = low[u] = ++idx;
    ins[u] = true;
    stk.push(u);
    for (auto v : e[u])
    {
        if (!dfn[v])
            dfs(v);
        if (ins[v])
            low[u] = min(low[u], low[v]);
    }
    if (dfn[u] == low[u])
    {
        ++cnt;
        ll sval = 0;
        bool sbar = false;
        dp[cnt] = -(1ll << 60);
        while (true)
        {
            int v = stk.top();
            ins[v] = false;
            bel[v] = cnt;
            sval += val[v];
            sbar |= bar[v];
            for (int w : e[v])
                if (bel[w] != cnt && bel[w] != 0)
                {
                    dp[cnt] = max(dp[cnt], dp[bel[w]]);
                }
            stk.pop();
            if (v == u)
                break;
        }
        if (sbar)
            dp[cnt] = max(dp[cnt], 0ll);
        dp[cnt] += sval;
    }
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        e[u].push_back(v);
    }
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", val + i);
    }
    int s, p;
    scanf("%d%d", &s, &p);
    for (int i = 1; i <= p; i++)
    {
        int x;
        scanf("%d", &x);
        bar[x] = 1;
    }
    dfs(s);
    printf("%lld\n", dp[bel[s]]);
}
