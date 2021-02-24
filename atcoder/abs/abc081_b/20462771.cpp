#define _GLIBCXX_DEBUG
#include <bits/stdc++.h>

using namespace std;

int main() {
    int N;
    int A[210];
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> A[i];
    }
    int ans = 0;
    bool odd_flag = false;

    while (!odd_flag) {
        for (int i = 0; i < N; i++) {
            if (A[i] % 2 == 0) {
                A[i] /= 2;
            }else{
                odd_flag = true;
                break;
            }
        }
        if (!odd_flag) {
            ans++;
        }
    }
    cout << ans << endl;
}