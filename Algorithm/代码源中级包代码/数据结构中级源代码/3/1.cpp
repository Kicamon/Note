#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 201000;

vector<int> vx;
vector<array<int, 4>> event;
int n, q, m;

int c[N], ans[N];

int query(int x)
{ // 1 ... x
    int s = 0;
    for (; x; x -= x & (-x))
    {
        s += c[x];
    }
    return s;
}

void modify(int x, int s)
{ // a[x] += s
    for (; x <= m; x += x & (-x))
    {
        c[x] += s;
    }
}

int main()
{
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++)
    {
        int x, y;
        scanf("%d%d", &x, &y);
        vx.push_back(x);
        // y坐标，类型，x坐标
        event.push_back({y, 0, x});
    }
    for (int i = 1; i <= q; i++)
    {
        int x1, x2, y1, y2;
        scanf("%d%d%d%d", &x1, &x2, &y1, &y2);
        //<= x2 <= y2, - <= x1-1 <= y2 - ... + ...
        // y坐标，类型 1 - 2 + ，x坐标，哪个询问
        event.push_back({y2, 2, x2, i});
        event.push_back({y1 - 1, 2, x1 - 1, i});
        event.push_back({y2, 1, x1 - 1, i});
        event.push_back({y1 - 1, 1, x2, i});
    }
    sort(event.begin(), event.end());
    sort(vx.begin(), vx.end());
    vx.erase(unique(vx.begin(), vx.end()), vx.end());
    m = vx.size();
    for (auto evt : event)
    {
        if (evt[1] == 0)
        {
            int y = lower_bound(vx.begin(), vx.end(), evt[2]) - vx.begin() + 1;
            modify(y, 1);
        }
        else
        {
            int y = upper_bound(vx.begin(), vx.end(), evt[2]) - vx.begin();
            int tmp = query(y);
            if (evt[1] == 1)
                ans[evt[3]] -= tmp;
            else
                ans[evt[3]] += tmp;
        }
    }
    for (int i = 1; i <= q; i++)
    {
        printf("%d\n", ans[i]);
    }
}
