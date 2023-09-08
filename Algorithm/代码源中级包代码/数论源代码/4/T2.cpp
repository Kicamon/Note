#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long u64;

u64 n, sum;

int main() {
    scanf("%llu", &n);
    for (u64 l = 1; l <= n; l++) {
        u64 d = n / l, r = n / d;
        sum += (n - l * d + n - r * d) * (r - l + 1) / 2;
        l = r;
    }
    printf("%llu\n", sum % (1ull << 60));
    //printf("%llu\n", sum & ((1ull << 60) - 1));
}