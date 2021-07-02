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
    n, l, t, x = map(int, sinput().split())
    time = 0
    cost = 0
    for _ in range(n):
        a, b = map(int, sinput().split())
        if b >= l:
            cost_flg = True
        else:
            cost_flg = False
            cost = 0

        for p in range(a):
            time += 1
            if cost_flg:
                cost += 1

            if cost == t:
                time += x
                cost = 0
                if p == a - 1:
                    break
                for pp in range(a):
                    time += 1
                    cost += 1
                    if cost == t:
                        if pp == a - 1:
                            time += x
                            break
                        else:
                            print("forever")
                            return
                break

    print(time)


if __name__ == "__main__":
    main()
