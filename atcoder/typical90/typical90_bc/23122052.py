import numpy as np
from numba import njit


@njit("(i8[:],)", cache=True)
def solve(stdin: np.ndarray):
    n, p, q = stdin[:3]
    a = stdin[3:]
    ans = 0
    for i in range(n):
        for j in range(i + 1, n):
            for k in range(j + 1, n):
                for l in range(k + 1, n):
                    for o in range(l + 1, n):
                        if a[i] * a[j] % p * a[k] % p * a[l] % p * a[o] % p == q:
                            ans += 1
    return ans


if __name__ == "__main__":
    stdin = np.fromstring(open(0).read(), dtype=np.int64, sep=" ")
    print(solve(stdin))
