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
    inp = sinput().strip()
    a = int(inp[0])
    bcd = tuple(map(int, inp[1:]))

    for s in range(1 << 3):
        sm = a
        ans = [str(a)]
        for d in range(3):
            if 1 << d & s == 0:
                sm += bcd[d]
                ans.append(f"+{bcd[d]}")
            else:
                sm -= bcd[d]
                ans.append(f"-{bcd[d]}")
        if sm == 7:
            print("".join(ans) + "=7")
            break
    else:
        raise ValueError


if __name__ == "__main__":
    main()
