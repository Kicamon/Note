#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int exgcd(int a, int b,int &x,int &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    /*int xx, yy;
    int d = exgcd(b, a % b, xx, yy);
    x = yy;
    y = xx - (a / b) * yy;*/

    /*int d = exgcd(b, a % b, x, y);
    int k = y;
    y = x - (a / b) * y;
    x = k;*/

    int d = exgcd(b, a % b, y, x);
    y -= (a / b) * x;
    return d;
}

int main() {
    int T;
    scanf("%d", &T);
    for (int tc = 0; tc < T; tc++) {
        int a, b, x, y;
        scanf("%d%d",&a, &b);
        int d = exgcd(a, b, x, y);
        y = -y;
        /*while (x < 0 || y < 0) x += b / d, y += a / d;
        while (x >= b / d && y >= a / d) x -= b / d, y -= a / d;*/
        //a x - b (-y) = d
        if (x < 0) {
            x += b / d;
            y += a / d;
        }
        printf("%d %d\n", x, y);
    }
}