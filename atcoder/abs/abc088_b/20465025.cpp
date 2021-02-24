#define _GLIBCXX_DEBUG
#include <bits/stdc++.h>

using namespace std;

int main() {
    int N;
    cin >> N;
    int a[110];
    int alice = 0;
    int bob = 0;
    for (int i = 0; i < N; i++) {
        cin >> a[i];
    }
    sort(a, a + N, greater<int>());
    for (int i = 0; i < N; i++) {
        if (i % 2 == 0) {
            alice += a[i];
        } else {
            bob += a[i];
        }
    }
    cout << alice - bob << endl;
}