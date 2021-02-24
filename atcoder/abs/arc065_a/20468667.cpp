#define _GLIBCXX_DEBUG
#include <bits/stdc++.h>

using namespace std;

int main() {
    string S;
    cin >> S;
    int end = S.length();
    while (true) {
        if (S.substr(end - 5, 5) == "dream") {
            end -= 5;
        } else if (S.substr(end - 5, 5) == "erase") {
            end -= 5;
        } else if (S.substr(end - 6, 6) == "eraser") {
            end -= 6;
        } else if (S.substr(end - 7, 7) == "dreamer") {
            end -= 7;
        } else {
            cout << "NO" << endl;
            break;
        }
        if (end <= 0) {
            cout << "YES" << endl;
            break;
        }
    }
}