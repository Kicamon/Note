## A. Hall of Fame

寻找最后一个`L`和`R` 的位置，然后判断是否交换即可

```c++
#include <bits/stdc++.h>
using namespace std;
// #define int long long
#define endl '\n'

void solve()
{
    int n;
    cin >> n;
    string s;
    cin >> s;
    int num[2]{-1, -1};
    for (int i = 0; i < n; ++i)
    {
        num[s[i] == 'R'] = i;
    }
    if (num[0] == -1 || num[1] == -1)
        cout << -1 << endl;
    else
    {
        if (num[0] < num[1])
            cout << num[0] + 1 << endl;
        else
            cout << 0 << endl;
    }
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



## B. MKnez's ConstructiveForces Task

当$n=3$时，输出$NO$

当n为奇数时，循环输出$(n - 3) / 2和(n - 2) / 2$即可

当n为偶数时，循环输出$1和-1$即可

```c++
#include <bits/stdc++.h>
using namespace std;
// #define int long long
#define endl '\n'

void solve()
{
    int n;
    cin >> n;
    if (n == 3)
        cout << "NO" << endl;
    else
    {
        cout << "YES" << endl;
        if (n & 1)
        {
            int t = n / 2;
            for (int i = 0; i < n; ++i)
            {
                if (i & 1)
                    cout << t * (-1) << ' ';
                else
                    cout << t - 1 << ' ';
            }
        }
        else
        {
            for (int i = 0; i < n; ++i)
                if (i & 1)
                    cout << -1 << ' ';
                else
                    cout << 1 << ' ';
        }
        cout << endl;
    }
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





## C. Least Prefix Sum

利用大根堆和小根堆即可

从m往前不断加，如果$a_m+a_{m-1}+......+a_k>0(k < m)$时，将$a_{k-m}$中的最大值乘上-1，并将操作次数+1

从m+1不断往后加，如果$a_m+a_{m + 1}+......a_k<0(m<k)$时，将$a_{m-k}$中放任最小值乘上-1，并将操作次数+1

```c++
#include <bits/stdc++.h>
using namespace std;
// #define int long long
#define endl '\n'
#define vint vector<int>
#define ll long long

void solve()
{
    int n, m;
    cin >> n >> m;
    vint a(n + 1);
    for (int i = 1; i <= n; ++i)
        cin >> a[i];

    ll res = 0;
    int ans = 0;
    priority_queue<int,vector<int>,less<int>>q;
    for (int i = m; i > 1; --i)
    {
    	q.push(a[i]);
    	res += a[i];
        if (res > 0)
        {
        	res -= 2 * q.top();
        	q.pop();
        	ans++;
        }
    }
    res = 0;
    priority_queue<int,vector<int>,greater<int>> p;
    for (int i = m + 1; i <= n; ++i)
    {
    	p.push(a[i]);
    	res += a[i];
        if (res < 0)
        {
        	res -= 2 * p.top();
        	p.pop();
        	ans++;
        }
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



## D. Boris and His Amazing Haircut

首先读入的时候判断，如果$b_i>a_i$，则输出$NO$

随后利用`map`将所有的剃刀数量存入

然后从前往后扫描一遍，利用单调栈来存储头发的长度，每次将小于当前长度的头发弹出。如：

```
7 9 4 5 3 3 3 6 8 10 3 2 5
5 3 1 5 3 2 2 5 8 5 1 1 5
```

以上样例，我们先是将`5,3,1`依次存入栈当中，剃刀`5,3,1`依次消耗掉1个。然后下一个遇到的长度是`5`，依次将`1,3`弹出栈。由于此时与栈顶元素相同，不消耗剃刀。同理，如此将所有的元素扫描一遍。如果遇到剃刀数量不够的情况，则输出 $NO$

扫描完之后输出$YES$

```c++
#include <bits/stdc++.h>
using namespace std;
// #define int long long
#define endl '\n'
#define ll long long
#define vint vector<int>

void solve()
{
    int n;
    cin >> n;
    vint a(n), b(n);
    for (int i = 0; i < n; ++i)
        cin >> a[i];
    bool f = true;
    for (int i = 0; i < n; ++i)
    {
        cin >> b[i];
        if(b[i] > a[i])
        	f = false;
    }
    int m;
    cin >> m;
    map<int, int> num;
    for (int i = 0, c; i < m; ++i)
    {
        cin >> c;
        num[c]++;
    }
    if (f == false)
    {
        puts("NO");
        return;
    }
    stack<int> s;
    for (int i = 0; i < n; ++i)
    {
        while (s.size() && s.top() < b[i])
            s.pop();
        if (a[i] > b[i])
        {
            if (s.empty() || s.top() != b[i])
            {
                if (num[b[i]] > 0)
                {
                    num[b[i]]--;
                    s.push(b[i]);
                }
                else
                {
                    puts("NO");
                    return;
                }
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

