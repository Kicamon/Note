/*
[[ ⣇⣿⠘⣿⣿⣿⡿⡿⣟⣟⢟⢟⢝⠵⡝⣿⡿⢂⣼⣿⣷⣌⠩⡫⡻⣝⠹⢿⣿⣷ ]],
[[ ⡆⣿⣆⠱⣝⡵⣝⢅⠙⣿⢕⢕⢕⢕⢝⣥⢒⠅⣿⣿⣿⡿⣳⣌⠪⡪⣡⢑⢝⣇ ]],
[[ ⡆⣿⣿⣦⠹⣳⣳⣕⢅⠈⢗⢕⢕⢕⢕⢕⢈⢆⠟⠋⠉⠁⠉⠉⠁⠈⠼⢐⢕⢽ ]],
[[ ⡗⢰⣶⣶⣦⣝⢝⢕⢕⠅⡆⢕⢕⢕⢕⢕⣴⠏⣠⡶⠛⡉⡉⡛⢶⣦⡀⠐⣕⢕ ]],
[[ ⡝⡄⢻⢟⣿⣿⣷⣕⣕⣅⣿⣔⣕⣵⣵⣿⣿⢠⣿⢠⣮⡈⣌⠨⠅⠹⣷⡀⢱⢕ ]],
[[ ⡝⡵⠟⠈⢀⣀⣀⡀⠉⢿⣿⣿⣿⣿⣿⣿⣿⣼⣿⢈⡋⠴⢿⡟⣡⡇⣿⡇⡀⢕ ]],
[[ ⡝⠁⣠⣾⠟⡉⡉⡉⠻⣦⣻⣿⣿⣿⣿⣿⣿⣿⣿⣧⠸⣿⣦⣥⣿⡇⡿⣰⢗⢄ ]],
[[ ⠁⢰⣿⡏⣴⣌⠈⣌⠡⠈⢻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣬⣉⣉⣁⣄⢖⢕⢕⢕ ]],
[[ ⡀⢻⣿⡇⢙⠁⠴⢿⡟⣡⡆⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣵⣵⣿ ]],
[[ ⡻⣄⣻⣿⣌⠘⢿⣷⣥⣿⠇⣿⣿⣿⣿⣿⣿⠛⠻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿ ]],
[[ ⣷⢄⠻⣿⣟⠿⠦⠍⠉⣡⣾⣿⣿⣿⣿⣿⣿⢸⣿⣦⠙⣿⣿⣿⣿⣿⣿⣿⣿⠟ ]],
[[ ⡕⡑⣑⣈⣻⢗⢟⢞⢝⣻⣿⣿⣿⣿⣿⣿⣿⠸⣿⠿⠃⣿⣿⣿⣿⣿⣿⡿⠁⣠ ]],
[[ ⡝⡵⡈⢟⢕⢕⢕⢕⣵⣿⣿⣿⣿⣿⣿⣿⣿⣿⣶⣶⣿⣿⣿⣿⣿⠿⠋⣀⣈⠙ ]],
[[ ⡝⡵⡕⡀⠑⠳⠿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠿⠛⢉⡠⡲⡫⡪⡪⡣ ]],
*/
// #pragma GCC optimize(2)
#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define all(a) a.begin(), a.end()
#define rall(a) a.rbegin(), a.rend()
#define ll long long
#define vint vector<int>
#define pb push_back
#define Debug(x) cout << #x << ':' << x << endl
int input = 0;
const int N = 5e5 + 10;
#define int long long

int n, m;
int a[N];

struct node
{
    int val;
    int lazy;
    int size;
} tr[N << 2];

void pushup(int u)
{
    tr[u].val = tr[u << 1].val + tr[u << 1 | 1].val;
}

void pushdown(int u)
{
    node &rt = tr[u], &l = tr[u << 1], &r = tr[u << 1 | 1];
    l.val += l.size * rt.lazy, l.lazy += rt.lazy;
    r.val += r.size * rt.lazy, r.lazy += rt.lazy;
    rt.lazy = 0;
}

void build(int u, int ml, int mr)
{
    if (ml == mr)
    {
        tr[u] = {a[ml], 0, mr - ml + 1};
        return;
    }
    tr[u] = {0, 0, mr - ml + 1};
    int mid = mr + ml >> 1;
    build(u << 1, ml, mid), build(u << 1 | 1, mid + 1, mr);
    pushup(u);
}

void modify(int u, int l, int r, int k, int ml, int mr)
{
    if (l <= ml && mr <= r)
    {
        tr[u].lazy += k;
        tr[u].val += tr[u].size * k;
        return;
    }
    int mid = ml + mr >> 1;
    pushdown(u);
    if (l <= mid)
        modify(u << 1, l, r, k, ml, mid);
    if (r > mid)
        modify(u << 1 | 1, l, r, k, mid + 1, mr);
    pushup(u);
}

int query(int u, int l, int r, int ml, int mr)
{
    if (l <= ml && mr <= r)
        return tr[u].val;
    int mid = ml + mr >> 1;
    pushdown(u);
    int res = 0;
    if (l <= mid)
        res += query(u << 1, l, r, ml, mid);
    if (r > mid)
        res += query(u << 1 | 1, l, r, mid + 1, mr);
    return res;
}

void solve()
{
    cin >> n >> m;
    for (int i = 1; i <= n; ++i)
        cin >> a[i];
    build(1, 1, n);
    while (m--)
    {
        int op, l, r;
        cin >> op >> l >> r;
        if (op == 1)
        {
            int k;
            cin >> k;
            modify(1, l, r, k, 1, n);
        }
        else
            cout << query(1, l, r, 1, n) << endl;
    }
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    // clock_t start, finish;
    // start = clock();

    int t = 1;
    if (input)
        cin >> t;
    while (t--)
        solve();

    // finish = clock();
    // cout <<endl<<"the time cost is:" << double(finish - start) / CLOCKS_PER_SEC<<endl;

    return 0;
}
