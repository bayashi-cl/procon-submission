#define _GLIBCXX_DEBUG
#include <bits/stdc++.h>

using namespace std;

int digsum(int n) {
    int ds = 0;
    while (true) {
        ds += n % 10;
        n /= 10;
        if (n == 0) {
            break;
        }
    }
    return ds;
}

int main() {
    int N, A, B;
    int ans = 0;
    cin >> N >> A >> B;
    for (int i = 1; i <= N; i++) {
        int ds = digsum(i);
        if (A <= ds && ds <= B) {
            ans += i;
        }
    }
    cout << ans << endl;
}