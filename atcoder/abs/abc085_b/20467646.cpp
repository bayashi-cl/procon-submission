#define _GLIBCXX_DEBUG
#include <bits/stdc++.h>

using namespace std;

int main() {
    int N;
    cin >> N;
    int count[110];
    for(int i = 0; i < 110; i++) {
        count[i] = 0;
    }
    int ans = 0;
    for (int i = 0; i < N; i++) {
        int d;
        cin >> d;
        count[d]++;
    }
    for (auto&& i : count) {
        if (i) {
            ans++;
        }
    }
    cout << ans << endl;
}