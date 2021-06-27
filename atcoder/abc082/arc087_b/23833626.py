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
    s = sinput().strip()
    x, y = map(int, sinput().split())
    lr = []
    ud = []
    is_lr = True
    cnt = 0
    for si in s:
        if si == "F":
            cnt += 1
        else:
            if is_lr:
                lr.append(cnt)
            else:
                ud.append(cnt)
            is_lr = not is_lr
            cnt = 0
    else:
        if is_lr:
            lr.append(cnt)
        else:
            ud.append(cnt)

    dp_lr = set()
    dp_lr.add(lr[0])
    for f in lr[1:]:
        dp_lr1 = set()
        for dep in dp_lr:
            dp_lr1.add(dep + f)
            dp_lr1.add(dep - f)

        dp_lr = dp_lr1

    dp_ud = set()
    dp_ud.add(0)
    for f in ud:
        dp_ud1 = set()
        for dep in dp_ud:
            dp_ud1.add(dep + f)
            dp_ud1.add(dep - f)
        dp_ud = dp_ud1

    if x in dp_lr and y in dp_ud:
        print("Yes")
    else:
        print("No")


if __name__ == "__main__":
    main()
