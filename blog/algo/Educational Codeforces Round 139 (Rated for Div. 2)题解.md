## A. Extremely Round

当n为3位数时，例如$n=120$，满足题目要求的情况有

<center><font size='4' color='blue'>1 2 3 4 5 6 7 8 9 10 20 30 40 50 60 70 80 90 100</font></center>

以上19种情况，一位和二位去满各有九种情况，三位只能取一种情况，所以共19种

`code`

```c++
#include <bits/stdc++.h>
using namespace std;
#define endl '\n'

void solve()
{
	int n;
	cin >> n;
	int res = 0;
	while(n)
	{
		res += min(n,9);
		n /= 10;
	}
	cout << res << endl;
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



## B. Notepad#

只要有两个相同的两位子串，就说明可以用小于n次操作将字符串输入

`code`

```c++
#include <bits/stdc++.h>
using namespace std;
#define endl '\n'

bool vis[30][30];

void solve()
{
	int n;
	cin >> n;
	string s;
	cin >> s;
	memset(vis,0,sizeof vis);
	for(int i = 1;i < n;++i)
	{
		int x = s[i - 1] - 'a',y = s[i] - 'a';
		if(vis[x][y])
		{
			puts("YES");
			return;
		}
		vis[x][y] = true;
		if(x == y && ((i < n - 1) && y == s[i + 1] - 'a'))
			++i;
	}
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



## C. Hamiltonian Wall

这里的话，我们将每一纵坐标标记为三种状态，$c_{1,j}=B$时为状态1，$c_{2,j}=B$时为状态2，均为$B$时为状态3

以下两种情况不能一笔画完：

1. <font color="blue">状态1(2), 偶数个状态3，状态2(1)</font>前后状态不同
2. <font color="blue">状态1(2), 偶数个状态3，状态1(2)</font>前后状态相同

`code`

```c++
#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define vint vector<int>

void solve()
{
    int n;
    cin >> n;
    string a, b;
    cin >> a >> b;
    vint num(n,0);
    int idx = -1;
    for (int i = 0; i < n; ++i)
    {
        if (a[i] == 'B')
            num[i] += 1;
        if (b[i] == 'B')
            num[i] += 2;
        if(num[i] != 3)
        {
        	if(idx == -1)
        		idx = i;
        	else
        	{
        		if((i - idx & 1) == abs(num[i] - num[idx]))
        		{
        			puts("NO");
        			return;
        		}
        		idx = i;
        	}
        }
    }
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


## D. Lucky Chains

有且仅有两者差值为1的时候，链可以无限长

然后通过差值寻找答案即可，当差值为k的时候，长度一定是k的因数

`code`

```c++
#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define vint vector<int>
const int N = 1e7;

int vis[N + 1];
vint prime;

void solve()
{
    int x, y;
    cin >> x >> y;
    int d = y - x;
    if (d == 1)
    {
        cout << -1 << endl;
        return;
    }
    int res = inf;
    while(d > 1)
    {
    	int p = vis[d];
    	d /= p;	
    	res = min(res,(p - x % p) % p);
    }
    cout << res << endl;
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    for (int i = 2; i <= N; ++i)
    {
        if (!vis[i])
            prime.pb(i),vis[i] = i;
        for (int j : prime)
        {
            if (j * i > N)
                break;
            vis[j * i] = j;
            if (i % j == 0)
                break;
        }
    }

    int t = 1;
    cin >> t;
    while (t--)
        solve();

    return 0;
}
```



