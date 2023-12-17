这场的状态不太好

## A. Divide and Conquer

如果和为偶数，输出0

如果和为奇数，则输出最小减少奇数的步骤。如样例2，$7/2=3,3/2=1,1/2=0$三次，$4/2=2,2/=1$两次

所以输出2

`code`

```c++
#include <bits/stdc++.h>
using namespace std;
// #define int long long
#define endl '\n'

int get(int u)
{
	bool f = u % 2;
	int k = 0;
	while(u && u % 2 == f)
	{
		k++;
		u >>= 1;
	}
	return k;
}

void solve()
{
    int n;
    cin >> n;
    ll res = 0;
    int ans = inf;
    for (int i = 0,a; i < n; ++i)
    {
        cin >> a;
        res += a;
		ans = min(ans,get(a));
    }
    if(res % 2 == 0)
    {
    	cout << 0 << endl;
    	return;
    }
    cout << ans << endl;
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



## B. Make Array Good

用一个结构体存下每一位的值，以及原来位置的下标。从小到大排序后，将后一位变成前一位的倍数即可，该种情况最多操作$n-1$次

`code`

```c++
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
#define all(a) a.begin(), a.end()
#define vint vector<int>

struct node
{
    int x, i;
    
    bool operator < (const node & M) const
    {
    	return x < M.x;
    }
};

void solve()
{
    int n;
    cin >> n;
    vector<node> a(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> a[i].x;
        a[i].i = i + 1;
    }
    sort(all(a));
    vector<array<int, 2>> q;
    for (int i = 1; i < n; ++i)
    {
        int k = a[i].x % a[i - 1].x;
        if (k)
        {
            q.pb({a[i].i, a[i - 1].x - k});
            a[i].x += a[i - 1].x - k;
        }
    }
    cout << q.size() << endl;
    for(auto x : q)
    	cout << x[0] << ' ' << x[1] << endl;
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



## C. Binary Strings are Fun

一般情况下每位一种情况。当这一位的数和上一位的数相同的时候，这一位的情况是上一位的两倍。如：`111`

$f[1,1]=1,f[1,2]=2,f[1,3]=4$，答案为7

`code`

```c++
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
const int mod = 998244353;

void solve()
{
    int n;
    cin >> n;
    string s;
    cin >> s;
    int res = 1, cnt = 1;
    for (int i = 1; i < (int)s.size(); ++i)
    {
        if (s[i] == s[i - 1])
            cnt = cnt * 2 % mod;
        else
            cnt = 1;
        res = (res + cnt) % mod;
    }	
    cout << res << endl;
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



d太长了，不想看