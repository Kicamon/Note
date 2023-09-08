#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int mod = 998244353;
const int M = 62;

int dp[5][M][M], n;
string s;

void add(int &a, int b) {a = (a + b) % mod;}

ll cnt[M];
ll sum, sum2;

void add(int x) {
    sum++;
    cnt[x]++;
    sum2 += 2 * cnt[x] - 1;
}

void del(int x) {
    sum--;
    sum2 -= 2 * cnt[x] - 1;
    cnt[x]--;
}

ll query(int x , int y){
    return ((sum - cnt[x] - cnt[y]) * (sum - cnt[x] - cnt[y]) - 
        (sum2 - cnt[x] * cnt[x] - cnt[y] * cnt[y])) /2 % mod;
}

int convert(char c) {
    if ('a' <= c && c <= 'z') return c - 'a';
    else if ('A' <= c && c <= 'Z') return 26 + c - 'A';
    else return 52 + c - '0';
}

int main(){
    cin >> s;
    n = s.size();
    int ans = 0;
    for (auto t : s) add(convert(t));
    for(int i = 0 ; i < M; ++i)
        for(int j = 0 ; j < M; ++j)
            if(i != j)
                dp[0][i][j] = 1;
    for(int i = n - 1; i >= 0; --i) {
        int t = convert(s[i]);
        del(t);
        for(int k = 0 ; k < M; ++k)
            if(k != t){
                add(dp[1][k][t], dp[0][k][t]);
                add(dp[3][k][t], dp[2][k][t]);
                add(dp[2][t][k], dp[1][t][k]);
                ans = (ans + dp[3][t][k] * query(t , k)) % mod;
            }
    }
    cout << ans << endl;
    return 0;
}