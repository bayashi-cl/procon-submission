#define _GLIBCXX_DEBUG
#include <bits/stdc++.h>

using namespace std;

int main() {
    int N;
    cin >> N;
    int ti_1 = 0;
    int xi_1 = 0;
    int yi_1 = 0;
    for (int i = 0; i < N; i++) {
        int ti, xi, yi;
        cin >> ti >> xi >> yi;
        int limit = ti - ti_1;
        int dist = abs((xi+yi)-(xi_1+yi_1));
        if ((limit+ dist)%2==0 && limit >= dist){
            ti_1 = ti;
            xi_1 = xi;
            yi_1 = yi;
        } else {
            cout << "No" << endl;
            return 0;
        }
    }
    cout << "Yes" << endl;
}