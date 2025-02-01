#include <iostream>
#include <vector>
using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; ++i)
        cin >> a[i];
    while (m--)
    {
        int op, x, k;
        cin >> op >> x >> k;
        if (op == 1)
            a[x] += k;
        else
        {
            int res = 0;
            for (int i = x; i <= k; ++i)
                res += a[i];
            cout << res << endl;
        }
    }
    return 0;
}
