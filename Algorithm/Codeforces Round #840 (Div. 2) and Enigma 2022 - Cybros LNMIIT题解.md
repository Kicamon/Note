~~这场好难~~我是废物，掉大分了

## A. Absolute Maximization

利用`|`找最大值和`&`找最小值即可

```c++
#include <bits/stdc++.h>
using namespace std;
// #define int long long
#define endl '\n'

void solve()
{
	int n;
	cin >> n;
	int maxn = 0,minn = 1023;
	for(int i = 0,c;i < n;++i)
	{
		cin >> c;
		maxn |= c;
		minn &= c;
	}
	cout << maxn - minn << endl;
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

	int t = 1;
	cin >> t;
	while(t--)
		solve();
    
    return 0;
}
```



## B. Incinerate

万万没想到，思维题竟然没有错在思维上，而是错在了代码上（被fst了）

思路简单，按照$p[i]$从小到大排序后直接遍历判断一遍即可。

```c++
#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define all(a) a.begin(), a.end()
#define rall(a) a.rbegin(), a.rend()
#define vint vector<int>

void solve()
{
    int n, m;
    cin >> n >> m;
    vector<array<int, 2>> a(n);
    int maxn = 0;
    for (int i = 0; i < 2; ++i)
    {
        int k = i ^ 1;
        for (int j = 0; j < n; ++j)
        {
            cin >> a[j][k];
            maxn = max(maxn, a[j][1]);
        }
    }
    sort(all(a));
    int res = m;
    for(int i = 0;i < n;++i)
    {
    	while(res < a[i][1] && m > 0)
    	{
    		m -= a[i][0];
    		res += m;
    	}
    	if(m < 0)
    		break;
    }
    if (res < maxn)
        puts("NO");
    else
        puts("YES");
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



## C. Another Array Problem

c有三种情况，分别为$n=2,n=3,n \ge 4$

1. $n=2$：取$abs(a[1] - a[2]) * 2和a[1] + a[2]$的最大值即可

2. $n \ge 4$：这种情况下为$a[max\_i] * n

   1. ![](https://i0.hdslb.com/bfs/new_dyn/73db4b823eb49131597fc958e3321f2b2048099495.png@1295w.webp)
   2. ![](https://i0.hdslb.com/bfs/new_dyn/8618fd6cd4b24f7a60069cd2b8d8a2492048099495.png@1295w.webp)

   3. $n=3$时，分四种情况：
      1. 最大值在下标1或下标3的位置：$a[max_i] * 3$
      2. 最大值在中间：下列三种情况取最大值
         1. 三数之和
         2. 最大值和最小值之差的绝对值*3
         3. 次大值*3

```c++
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
#define all(a) a.begin(), a.end()
#define rall(a) a.rbegin(), a.rend()
#define vint vector<int>

void solve()
{
    int n;
    cin >> n;
    vint a(n + 1);
    int idx = 0;
    for (int i = 1; i <= n; ++i)
    {
        cin >> a[i];
        if (a[i] > a[idx])
            idx = i;
    }
    if (n == 2)
        cout << max(abs(a[2] - a[1]) * 2, a[1] + a[2]) << endl;
    else if (n == 3)
    {
        if (idx == 1 || idx == 3)
            cout << a[idx] * 3 << endl;
        else
        {
            int x = min(a[1], a[3]), y = max(a[1], a[3]);
            int k = a[2] - x;
            cout << max({k * 3,y * 3,a[1] + a[2] + a[3]}) << endl;
        }
    }
    else
        cout << a[idx] * n << endl;
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

