#define _GLIBCXX_DEBUG
#include <bits/stdc++.h>

using namespace std;

int main() {
    int N, Y;
    cin >> N >> Y;
    Y /= 1000;
    for (int i = 0; i <= N; i++) {
        for (int j = 0; j <= N - i; j++) {
            int k = N - i - j;
            if (10 * i + 5 * j + k == Y) {
                cout << i << " " << j << " " << k << endl;
                return 0;
            }
        }
    }
    cout << "-1 -1 -1" << endl;
}