这题的rating是1400，对于我这种蒟蒻来说，还是稍微有点难度的QAQ

但是这题没有涉及任何算法，纯纯的思维题，还是有点巧妙的（有点类似KMP的思路，使用跳转数组）

## 朴素的暴力

最初的字符串为$mark$

> 第一次拼接的结果为$markmark$
> 
> 第二次拼接的结果为$markmarkmar$
> 
> 第三次拼接的结果为$markmarkmarrkmark$

那么，我们可以试试直接拼接

```c++
long long l,r;
cin >> l >> r;
for(long long i = l - 1;i < r;++i)
    str += str[i];
```

看上去可行，我们来提交看看

![wa](https://i0.hdslb.com/bfs/new_dyn/3b30f3702cb16738a239793a92598dcc2048099495.png@260w_260h_1e_1c.webp)

不出所料，看看数据的范围就知道不太可能。所以我们想想不同的写法。在这里，我们可以试试类似KMP的跳转数组，当这个地方满足某个条件的时候，就可以跳转到前边的某个坐标

那么我们来看看这个思路的具体实现方式

## 跳转坐标

首先我想的方法是创建一个数组，$num[N]$，不直接去存储字符串，而是存储跳转的坐标，如：

> {0,0,0,0,-4,-4,-4,-4,-4,-4,-4,-8,-8,-8,-8,-8,-8}

在读取一个坐标的时候，不停地往前跳转，一直跳转到跳转数组的值为0的地方，就是我们想要读取的字符

看起来可行，但是…………，这不还是要存储大量的数据吗，只不过从字符变成了数字

emmmm…………，不过还是有可取的地方的，至少跳转数组这个想法是可行的。还需要进一步的优化，于是我注意到了

<center><font size="5"><mark>0,0,0,0</mark>,-4,-4,-4,-4,<mark>-4,-4,-4</mark>,-8,-8,-8,-8,-8,-8</font></center>

将原有的数组分成四部分，首先是原有的部分，然后分别为第一、二、三次拼接的部分。可以注意到，同一次拼接当中的跳转位数都是相同的，我们可以将同一次的拼接全部放在一个数组中，如：（这里就不写原位置了）

<center><font size="5">-4,-4,-8</font></center>

看样子可行，那么需要解决的问题就剩下一个了：<font color="red">如何确定我想要输出的下标在哪个区域内呢？</font>

当下标为$[5,8]$的时候，在第一个区域；下标为$[9,11]$的时候，在第二个区域；下标为$[12,17]$的时候，在第三个区域

那么，将每个区域表示的下标的最大值存储下来，每次查找的时候使用二分来确定在哪个区域即可

来看看结果吧

```c++
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
#define all(a) a.begin(), a.end()
#define vint vector<int>
#define pb push_back

int n,m,q;
string s;

void solve()
{
    cin >> n >> m >> q;
    cin >> s;
    vint j1(m),j2(m);
    int len = s.size();
    for(int i = 0;i < m;++i)
    {
    	int l,r;
    	cin >> l >> r;
    	len += r - l + 1;
    	j1[i] = len;
    	j2[i] = len - r;
    }
    
    while(q--)
    {
    	int x;
    	cin >> x;
    	while(x > s.size())
    	{
    		int l = 0,r = m - 1;
    		while(l < r)
    		{
    			int mid = l + r >> 1;
    			if(j1[mid] < x)
    				l = mid + 1;
    			else
    				r = mid;
    		}
    		x -= j2[l];
    	}
    	cout << s[x - 1] << endl;
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
提交：

![ac](https://i0.hdslb.com/bfs/new_dyn/82078e84d426a9b9f0db42292dfde21e2048099495.png@1295w.webp)
