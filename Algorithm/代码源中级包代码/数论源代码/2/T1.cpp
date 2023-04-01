#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    int T;
    scanf("%d", &T);
    for (int tc = 0; tc < T; tc++) {
        int n;
        scanf("%d",&n);
        int phin = n;
        for (int d = 2; d * d <= n; d++) if (n % d == 0) {
            phin = phin / d * (d - 1);
            while (n % d == 0) n /= d;
        }
        if (n != 1) {
            phin = phin / n * (n - 1);
        }
        printf("%d\n", phin);
    }
}