看看时间还有十几分钟，开不出来题了，写个题解

## A. Cut the Triangle

检查是不是直角边平行于坐标轴的直角三角形即可

这里可以用异或来写，代码较为简洁，我就不改了，直接贴上我的丑代码

`code`

```c++
// Problem: A. Cut the Triangle
// Contest: Codeforces - Educational Codeforces Round 140 (Rated for Div. 2)
// URL: https://codeforces.com/contest/1767/problem/0
// Memory Limit: 512 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

// #pragma GCC optimize(2)
#include <bits/stdc++.h>
using namespace std;
// #define int long long
#define endl '\n'
#define all(a) a.begin(),a.end()
#define rall(a) a.rbegin(),a.rend()
#define C2(n) (n * (n - 1) >> 1)
#define ll long long
#define ull unsigned long long 
#define PII pair<int, int>
#define vint vector<int>
#define pb push_back
#define fi first
#define se second
#define inf 0x3f3f3f3f
#define eqs 1e-6
// const int mod = 
// const int N = 

void solve()
{
	int x[3],y[3];
	for(int i = 0;i < 3;++i)
		cin >> x[i] >> y[i];
	if(x[0] == x[1] && (y[1] == y[2] || y[0] == y[2]))
		puts("NO");
	else if(x[1] == x[2] && (y[0] == y[1] || y[0] == y[2]))
		puts("NO");
	else if(x[0] == x[2] && (y[0] == y[1] || y[1] == y[2]))
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
	while(t--)
		solve();
    
    return 0;
}
```

## B. Block Towers

排序后往第一个加即可，记得第一个不要排序

`code`

```c++
// Problem: B. Block Towers
// Contest: Codeforces - Educational Codeforces Round 140 (Rated for Div. 2)
// URL: https://codeforces.com/contest/1767/problem/B
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

// #pragma GCC optimize(2)
#include <bits/stdc++.h>
using namespace std;
// #define int long long
#define endl '\n'
#define all(a) a.begin(),a.end()
#define rall(a) a.rbegin(),a.rend()
#define C2(n) (n * (n - 1) >> 1)
#define ll long long
#define ull unsigned long long 
#define PII pair<int, int>
#define vint vector<int>
#define pb push_back
#define fi first
#define se second
#define inf 0x3f3f3f3f
#define eqs 1e-6
// const int mod = 
// const int N = 

void solve()
{
	int n;
	cin >> n;
	vint a(n);
	for(int i = 0;i < n;++i)
		cin >> a[i];
	sort(a.begin() + 1,a.end());
	for(int i = 1;i < n;++i)
	{
		int k = a[i] - a[0];
		if(k > 0)
		{
			k = (k + 1) >> 1;
			a[0] += k;
		}
	}
	cout << a[0] << endl;
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



c的难度有点大，没写出来，赛后看看大佬的代码想想，想出来的就另写一个题解



## D. Playoff

结论题，有$k$个1就减去前面$2^k - 1$个元素，有$k$个0就减去后面$2^k - 1$个元素

`code`

```c++
// Problem: D. Playoff
// Contest: Codeforces - Educational Codeforces Round 140 (Rated for Div. 2)
// URL: https://codeforces.com/contest/1767/problem/D
// Memory Limit: 256 MB
// Time Limit: 2000 ms
//
// Powered by CP Editor (https://cpeditor.org)

// #pragma GCC optimize(2)
#include <bits/stdc++.h>
using namespace std;
// #define int long long
#define endl '\n'
#define all(a) a.begin(), a.end()
#define rall(a) a.rbegin(), a.rend()
#define C2(n) (n * (n - 1) >> 1)
#define ll long long
#define ull unsigned long long
#define PII pair<int, int>
#define vint vector<int>
#define pb push_back
#define fi first
#define se second
#define inf 0x3f3f3f3f
#define eqs 1e-6
// const int mod =
// const int N =

void solve()
{
    int n;
    cin >> n;
    string s;
    cin >> s;
    int num[2]{0, 0};
    for (int i = 0; i < n; ++i)
        num[s[i] == '1']++;

    auto get = [&](int x) {
        if (!x)
            return 0;
        return (1 << x) - 1;
    };

    int x = get(num[1]) + 1, y = get(num[0]);
    for (int i = x; i <= (1 << n) - y; ++i)
        cout << i << ' ';
    cout << endl;
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    // cin >> t;
    while (t--)
        solve();

    return 0;
}
```

