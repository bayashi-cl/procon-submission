import sys
import numpy as np

if sys.argv[-1] == "ONLINE_JUDGE":
    from numba.pycc import CC

    cc = CC("my_module")

    @cc.export("solve", "(i8[:],i8,i8,i8)")
    def solve(a, n, p, q):
        ans = 0
        for i in range(n):
            for j in range(i + 1, n):
                for k in range(j + 1, n):
                    for l in range(k + 1, n):
                        for o in range(l + 1, n):
                            if a[i] * a[j] % p * a[k] % p * a[l] % p * a[o] % p == q:
                                ans += 1
        return ans

    cc.compile()
    exit(0)

from my_module import solve

stdin = np.fromstring(open(0).read(), dtype=np.int64, sep=" ")
n, p, q = stdin[:3]
a = stdin[3:]
print(solve(a, n, p, q))
