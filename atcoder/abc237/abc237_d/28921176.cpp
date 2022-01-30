#include <bits/stdc++.h>
using namespace std;
int main() {
    int n;
    string s;
    cin >> n >> s;
    std::list<int> a = {0};
    auto itr = a.begin();
    for (int i = 0; i < n; ++i) {
        if (s[i] == 'L') {
            itr = a.insert(itr, i + 1);
        } else {
            itr = a.insert(std::next(itr), i + 1);
        }
    }
    vector ans(a.begin(), a.end());
    for (int i = 0; i < n; ++i) cout << ans[i] << " ";
    cout << ans[n] << endl;
}
