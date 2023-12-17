# Quests题解

[题目链接](https://codeforces.com/problemset/problem/1760/F)

这题的rating是1500，是我上个月写的。闲着没事再写一遍，发现不能一遍过，写个题解。

首先注意数据范围，$10^{16}$，要开$long~long$。为了省事直接`#define int long long`

我们只需要将数组进行从大到小排序排序，然后尝试每个$d$的数值，得到最大的就可以。当然，这里使用二分来进行优化

```c++
int l = -1,r = d + 1;
while(l < r)
{
    int mid = l + r + 1 >> 1;
    if(check(mid))
        l = mid;
   	else
        r = mid - 1;
}
```

如果最后的结果是-1，则说明不存在$k$值；如果结果是$d+1$，则说明$k$可以是任意值

然后是check函数

```c++
bool ckeck(int k)
{
    int res = 0;
    for(int i = 0;i < d;++i)
    {
        int j = i % (k + 1);
        if(j < n)
            res += a[i];
    }
    return res >= m;
}
```

最后我们来看看完整代码

```c++
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
#define rall(a) a.rbegin(), a.rend()
#define vint vector<int>

void solve()
{
    int n, m, d;
    cin >> n >> m >> d;
    vint a(n);
    for (int i = 0; i < n; ++i)
        cin >> a[i];
    sort(rall(a));

    auto check = [&](int k) {
        int res = 0;
        for (int i = 0; i < d; ++i)
        {
        	int j = i % (k + 1);
            if (j < n)
                res += a[j];
        }
        return res >= m;
    };

    int l = -1, r = d + 1;
    while (l < r)
    {
        int mid = l + r + 1 >> 1;
        if (check(mid))
            l = mid;
        else
            r = mid - 1;
    }
    if (l == -1)
        cout << "Impossible" << endl;
    else if (l == d + 1)
        cout << "Infinity" << endl;
    else
        cout << l << endl;
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    cin >> t;
    while (t--)
        solve();

    return 0;
}
```

