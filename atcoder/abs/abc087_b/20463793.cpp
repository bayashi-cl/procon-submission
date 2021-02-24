#define _GLIBCXX_DEBUG
#include <bits/stdc++.h>

using namespace std;

int main() {
    int ans = 0;
    int A, B, C, X;
    cin >> A;
    cin >> B;
    cin >> C;
    cin >> X;
    for (int a = 0; a <= A; a++) {
        for (int b = 0; b <= B; b++) {
            for (int c = 0; c <= C; c++) {
                if (10 * a + 2 * b + c == X / 50) {
                    ans++;
                }
            }
        }
    }
    cout << ans << endl;
}