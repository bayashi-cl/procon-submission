# region template
import sys
import typing
from typing import Callable, Dict, List, Set, Tuple
from collections import Counter
from itertools import chain

sys.setrecursionlimit(10 ** 6)
Vec = List[int]
VecVec = List[Vec]
sinput: Callable[..., str] = sys.stdin.readline
MOD: int = 1000000007
INF: float = float("Inf")
IINF: int = sys.maxsize
# endregion


def factorize_n(n) -> List[List[int]]:
    res: List[List[int]] = [[] for _ in range(n + 1)]
    for i in range(2, n + 1):
        if len(res[i]) != 0:
            continue
        j = i
        while j <= n:
            k = 1
            while j * k <= n:
                res[j * k].append(i)
                k += 1
            j *= i
    return res


def main() -> None:
    n = int(sinput())
    ps = factorize_n(n)
    cnt = Counter(chain.from_iterable(ps))
    ans = 1
    for v in cnt.values():
        ans *= v + 1
        ans %= MOD

    print(ans)


if __name__ == "__main__":
    main()
