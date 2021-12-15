# region template
import sys
import typing
from typing import Callable, Dict, List, Set, Tuple

sys.setrecursionlimit(10 ** 6)
Vec = List[int]
VecVec = List[Vec]
sinput: Callable[..., str] = sys.stdin.readline
MOD: int = 998244353
INF: float = float("Inf")
IINF: int = sys.maxsize // 2
# endregion


def check(bx: str, by: str) -> bool:
    s = by.find(bx)
    if s != -1:
        if "0" not in by[:s] and "0" not in by[s + len(bx) :]:
            return True
    return False


def main() -> None:
    x, y = map(int, sinput().split())
    if x == y:
        print("YES")
        return
    bx = bin(x)[2:]
    by = bin(y)[2:]
    if by[-1] == "0":
        print("NO")
        return
    if check(bx, by) or check(bx[::-1], by):
        print("YES")
        print(1, file=sys.stderr)
        return

    if bx[-1] == "0":
        print(bx, file=sys.stderr)
        last_z = bx.rfind("1")
        bx = bx[: last_z + 1]
        if check(bx, by) or check(bx[::-1], by):
            print(bx, bx[::-1], by, file=sys.stderr)
            print("YES")
            return

    print("NO")


if __name__ == "__main__":
    main()
