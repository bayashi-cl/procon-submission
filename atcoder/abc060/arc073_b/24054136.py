# region template
import sys
import typing
from itertools import accumulate
from operator import add
from typing import Callable, Dict, List, Set, Tuple

sys.setrecursionlimit(10 ** 6)
Vec = List[int]
VecVec = List[Vec]
sinput: Callable[..., str] = sys.stdin.readline
MOD: int = 1000000007
INF: float = float("Inf")
IINF: int = sys.maxsize
# endregion


def main() -> None:
    n, w = map(int, sinput().split())

    goods: Dict[int, List[int]] = dict()
    base, v0 = map(int, sinput().split())
    for i in range(base, base + 4):
        goods[i] = []
    goods[base].append(v0)

    for _ in range(n - 1):
        wi, vi = map(int, sinput().split())
        goods[wi].append(vi)

    for k in goods.keys():
        goods[k].sort(reverse=True)
        goods[k] = list(accumulate(goods[k], add, initial=0))
    ans = 0

    for i in range(len(goods[base])):
        if base * i > w:
            break
        for j in range(len(goods[base + 1])):
            if base * i + (base + 1) * j > w:
                break
            for k in range(len(goods[base + 2])):
                if base * i + (base + 1) * j + (base + 2) * k > w:
                    break

                l = (w - (base * i + (base + 1) * j + (base + 2) * k)) // (base + 3)
                l = min(l, len(goods[base + 3]) - 1)

                # val = (
                #     goods[base][i]
                #     + goods[base + 1][j]
                #     + goods[base + 2][k]
                #     + goods[base + 3][l]
                # )
                val = sum(goods[base + d][num] for d, num in enumerate((i, j, k, l)))

                ans = max(ans, val)

    print(ans)


if __name__ == "__main__":
    main()
