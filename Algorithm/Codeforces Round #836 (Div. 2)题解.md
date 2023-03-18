### A. SSeeeeiinngg DDoouubbllee

这题倒是简单，将字符串正反输出一遍就好了

```c++
#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define all(a) a.begin(),a.end()

void solve()
{
	string s;
	cin >> s;
	cout << s;
	reverse(all(s));
	cout << s << endl;
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

### B. XOR = Average

**这里考虑两种情况：**

当$n$为<font color="red">奇数</font>时，所有数均取$1$，异或结果为$1$，平均数为$1$

当$n$为<font color="red">偶数时</font>，前$n-2$个数取$2$，后面两个数分别取$1$和$3$，异或结果为$2$，平均值为$2$

```c++
#include <bits/stdc++.h>
using namespace std;
#define endl '\n'

void solve()
{
	int n;
	cin >> n;
	if(n & 1)
	{
		for(int i = 0;i < n;++i)
			cout << 1 << ' ';
		cout << endl;
	}
	else
	{
		for(int i = 0;i < n - 2;++i)
			cout << 2 << ' ';
		cout << 1 << ' ' << 3 << endl;
	}
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

### C. Almost All Multiples

**首先来看看不存在的情况：**

当$n$不是$x$的倍数时，我们无法将所有坐标填满，则不存在

**再来看看怎么构造出这个数组：**

看看这个例子：

<center><font size="5" color="blue">18 3</font></center>

我们先把$n$放到$x$上，构造出一个可行但是字典序不一定是最小的数组

| 1    | 2    | 3    | 4    | 5    | 6    | 7    | 8    | 9    | 10   | 11   | 12   | 13   | 14   | 15   | 16   | 17   | 18   |
| ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- |
| 3    | 2    | 18   | 4    | 5    | 6    | 7    | 8    | 9    | 10   | 11   | 12   | 13   | 14   | 15   | 16   | 17   | 1    |

我们将18放在了3上，18是3的倍数，这个操作是可行的

然后我们继续往后看，发现$6,9,12,15$也都是$3$的倍数，可以将他们当中的数与$3$交换，来减小字典序。那么，与3交换的下标除了满足是3的倍数这一条件之外，还要是18的因数，这样才能将18放在上面。这样，剩下的还有$6,9$两个数。显然，与6交换时字典序最小的，那么，该数组最终的模样应该是：

| 1    | 2    | 3    | 4    | 5    | 6    | 7    | 8    | 9    | 10   | 11   | 12   | 13   | 14   | 15   | 16   | 17   | 18   |
| ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- |
| 3    | 2    | 6    | 4    | 5    | 18   | 7    | 8    | 9    | 10   | 11   | 12   | 13   | 14   | 15   | 16   | 17   | 1    |

就这样一直交换下去即可

```c++
#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define vint vector<int>

void solve()
{
    int n, x;
    cin >> n >> x;
    if (n % x)
    {
        cout << -1 << endl;
        return;
    }
    vint res(n + 1);
    res[1] = x,res[n] = 1;
    int k = x;
    for(int i = 2;i <= n;++i)
    {
    	if(i > x && i % k == 0 && n % i == 0)
    	{
    		res[k] = i;//将该下标的值放到上一个符合要求的下标k上
    		k = i;//更新k值
    	}
    	else
    		res[i] = i;
    }
    res[n] = 1;
    
    for (int i = 1; i <= n; ++i)
        cout << res[i] << ' ';
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



### D. Range = √Sum

**首先来看看n为偶数的情况：**

我们选取$[n - \frac{n}{2},n - 1] \cup [n + 1,n + \frac{n}{2}]$。不难看出，他们的和为$n^2$，最大值和最小值的差为$n$，满足要求

**然后是n为奇数的时候：**

此时我们构造出$(n + 1) ^ 2$出来

$[n - \frac{n + 1}{2} + 2,n] \cup [n + 2,n + \frac{n + 1}{2} + 2]$。不难看出，他们的和为$(n + 1)^2$，差值为$n+1$，满足要求

```c++
#include <bits/stdc++.h>
using namespace std;
#define endl '\n'

void solve()
{
    int n;
    cin >> n;
    if(n & 1)
    {
    	int k = (n + 1) / 2;
    	for(int i = n - k + 2;i <= n;++i)
    		cout << i << ' ';
    	for(int i = n + 3;i <= n + 2 + k;++i)
    		cout << i << ' ';									
    }
    else
    {
    	for(int i = n - n / 2;i < n;++i)
    		cout << i << ' ';
    	for(int i = n + 1;i <= n + n / 2;++i)
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



后面两题不会<font size='5' color='pink'>QAQ</font>
