# region template
from __future__ import annotations

import sys
from typing import Any, Callable, Final
import numpy as np
import numpy.linalg as LA


def plog(*obj: Any) -> None:
    print(*obj, file=sys.stderr)


sys.setrecursionlimit(10 ** 9)
sinput: Callable[[], str] = sys.stdin.readline
INF: Final[float] = float("inf")
MOD: Final[int] = 10 ** 9 + 7
# endregion


def main() -> None:
    N, K = map(int, sinput().split())
    adj = np.array([list(map(int, sinput().split())) for _ in range(N)], "object")

    def mat_pow(k: int) -> np.ndarray:
        if k == 0:
            return np.identity(N, dtype="object")
        res = mat_pow(k // 2)
        res = (res @ res) % MOD
        if k % 2 == 1:
            res = res @ adj
        return res % MOD

    ans = mat_pow(K)
    print(int(np.sum(ans)) % MOD)


if __name__ == "__main__":
    main()
