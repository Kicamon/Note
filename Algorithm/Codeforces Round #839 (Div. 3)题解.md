## A. A+B?

直接读入字符串然后把下标0和2的数字提取出来就行

```c++
// Problem: A. A+B?
// Contest: Codeforces - Codeforces Round #839 (Div. 3)
// URL: https://codeforces.com/contest/1772/problem/A
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
	string s;
	cin >> s;
	int a = s[0] - '0',b = s[2] - '0';
	cout << a + b<< endl;
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



## B. Matrix Rotation

最大值和最小值处在对角线上时即为`YES`，或者像我这样列举所有情况

```c++
// Problem: B. Matrix Rotation
// Contest: Codeforces - Codeforces Round #839 (Div. 3)
// URL: https://codeforces.com/contest/1772/problem/B
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

vector<int> get(vector<int> a)
{
	int k = min({a[0],a[1],a[2],a[3]});
	vint b = a;
	if(a[1] == k)
		b[0] = a[1],b[1] = a[3],b[2] = a[0],b[3] = a[2];
	else if(a[2] == k)
		b[0] = a[2],b[1] = a[0],b[2] = a[3],b[3] = a[1];
	else if(a[3] == k)
		b[0] = a[3],b[1] = a[2],b[2] = a[1],b[3] = a[0];
	return b;
}

void solve()
{
	vint a(4);
	cin >> a[0] >> a[1] >> a[2] >> a[3];
	a = get(a);
	if(a[0] < a[1] && a[2] < a[3] && a[0] < a[2] && a[1] < a[3])
		puts("YES");
	else
		puts("NO");
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



## C. Different Differences

先从小到大标记：1、2、4、7……，不足的在从大到小标记

```c++
// Problem: C. Different Differences
// Contest: Codeforces - Codeforces Round #839 (Div. 3)
// URL: https://codeforces.com/contest/1772/problem/C
// Memory Limit: 512 MB
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
    int n, m;
    cin >> n >> m;
    int res = 0;
    vint a(m + 1, 0),ans;
    for (int i = 1; i <= m; res++)
    {
        if (res == n)
            break;
        a[i] = true;
        i += res + 1;
    }
    for (int i = m; i; --i)
    {
        if (res == n)
            break;
        if (!a[i])
        {
            a[i] = true;
            res++;
        }
    }
    for(int i = 1;i <= m;++i)
    {
    	if(a[i])
    		cout << i << ' ';
    }
    cout << endl;
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



## D. Absolute Sorting

我是撒比，这题开始用二分答案来写，卡了一个半小时。正确解法是枚举相邻两位的差来确定取值范围即可

```c++
// Problem: D. Absolute Sorting
// Contest: Codeforces - Codeforces Round #839 (Div. 3)
// URL: https://codeforces.com/contest/1772/problem/D
// Memory Limit: 512 MB
// Time Limit: 2000 ms
//
// Powered by CP Editor (https://cpeditor.org)

// #pragma GCC optimize(2)
#include <bits/stdc++.h>
using namespace std;
#define int long long
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
    vint a(n);
    for (int i = 0; i < n; ++i)
        cin >> a[i];

    int l = 0, r = inf;
    for (int i = 1, c; i < n; ++i)
    {
        if (a[i - 1] < a[i])
        {
            c = (a[i - 1] + a[i]) / 2;
            r = min(r, c);
        }
        else if (a[i - 1] > a[i])
        {
            c = (a[i - 1] + a[i] + 1) / 2;
            l = max(l, c);
        }
    }
    if (l <= r)
        cout << l << endl;
    else
        cout << -1 << endl;
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



## E. Permutation Game

这题的题意有点含糊，其大意是，两个操作，将一个红色染成蓝色， 或者将蓝色的位置之间任意排序。如：

![](https://i0.hdslb.com/bfs/new_dyn/cf4b251c7353eaf9332f3aec4ab9ad452048099495.png@260w_260h_1e_1c.webp)

此时可以选择3或者5将其染成蓝色，这里不做演示。也能对已经染成蓝色的进行重新排布，如：

![](https://i0.hdslb.com/bfs/new_dyn/ae705d932c5d405675b32035a11c351b2048099495.png@260w_260h_1e_1c.webp)

当然也可以选择不操作

上述例子中，后手想要赢的话，只要将3、4、5都染成蓝色， 那么他就可以将这三个数从新排布得到降序的数组；而先手想要赢的话，就要将所有的都染成蓝色， 所以后手赢。

所以这题的重点在于染色上而不是排序上。我们可以将数分为三类，一类是只有先手想要染的（数量为a），第二类是只有后手想要染的（数量为b），第三类是两者都要染的（数量为c）。

所以当

1. a + c <= b时，先手胜（由于是先手，所以可以取等于）
2. b + c < a时，后手胜
3. 平局



```c++
// Problem: E. Permutation Game
// Contest: Codeforces - Codeforces Round #839 (Div. 3)
// URL: https://codeforces.com/contest/1772/problem/E
// Memory Limit: 256 MB
// Time Limit: 4000 ms
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
	int num[3]{0,0,0};
	for(int i = 1,j = n,c;i <= n;++i,--j)
	{
		cin >> c;
		num[1] += (c != i);
		num[2] += (c != j);
		num[0] += (c != i && c != j);
	}
	if(num[1] <= num[2] - num[0])
		puts("First");
	else if(num[2] < num[1] - num[0])
		puts("Second");
	else
		puts("Tie");
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

