# Ela's Fitness and the Luxury Number题解
这道题的rating是1300，是一道数论题，代码实现倒是比较简单，所以这里着重讲解公式的推导，代码贴在最后就好了

我们假设有一个数x，它的取值范围为[$i^2$,$(i+1)^2$)，那么它的$\lfloor \sqrt{x} \rfloor$的值就是$i$

那么，我们来算一下在[$i^2$,$(i+1)^2$)之间的符合要求的数，即[$i^2$,$(i+1)^2$)之间的$i$的倍数

我们将每个数都除以$i$，得到$i \to i + 2 + \frac{1}{i}$，在这些数之间，只有$i,i+1,i+2$是整数，其余的都是分数

如果我们将它们重新乘上$i$，那么就是$i^2,i^2 + i,i^2 + 2i$，这三个值都是小于$(i+1)^2 = i^2 + 2i + 1$的。那么，$x$内符合要求的数的数量为$(\sqrt{x} - 1) \sdot 3 + y$

y的值为：
$$ y=\left\{
\begin{array}{rcl}
0       &      & {x < i^2+i}\\
1     &      & {i^2+i \leq x < i^2 + 2i}\\
2       &      & {x = i^2+2i}
\end{array} \right. $$

上边就是整个的推到过程了，代码在下边

<font size='6' color='red'>注意：这里的开根号不能用sqrt函数，会有精度问题，要用二分来写</font>

```c++
#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define ll long long

ll sum(ll x)
{
    ll l = 0, r = 1e9;
    while (l < r)
    {
        ll mid = l + r + 1 >> 1;
        if (mid * mid > x)
            r = mid - 1;
        else
            l = mid;
    }
    ll y = l;
    ll res = (y - 1) * 3;
    res -= (x < y * (y + 1));
    res -= (x < y * (y + 2));
    return res;
}

void solve()
{
    ll l, r;
    cin >> l >> r;
    cout << sum(r) - sum(l - 1) << endl;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--)
        solve();

    return 0;
}
```
