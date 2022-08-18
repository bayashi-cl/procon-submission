#include <bits/stdc++.h>
using namespace std;
 
int main() {
  int x, a, b;
  cin >> x >> a >> b;
 
  cout << ++x << endl;
  cout << (x *= a + b) << endl;
  cout << (x *= x) << endl;
  cout << --x << endl;
}