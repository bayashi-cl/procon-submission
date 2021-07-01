# region template
import sys
import typing
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
    a, b, c, d, e, f = map(int, sinput().split())
    ans = (100 * a, 0)
    mx = 0.0

    for w1 in range(0, f + 1, 100 * a):
        for w2 in range(0, f + 1, 100 * b):
            if (water := w1 + w2) > f:
                break
            weight = f - water
            able = int(water * (e / 100))

            for s1 in range(0, min(weight, able) + 1, d):
                suger = s1 + (min(able, weight) - s1) // c * c
                if suger + water == 0:
                    continue

                sw = 100 * suger / (water + suger)
                if sw > mx:
                    mx = sw
                    ans = (water + suger, suger)
    print(*ans)


if __name__ == "__main__":
    main()
