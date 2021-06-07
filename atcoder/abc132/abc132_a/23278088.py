# region template
import sys
import typing
from collections import Counter

sys.setrecursionlimit(10 ** 6)
Vec = typing.List[int]
VecVec = typing.List[Vec]
sinput: typing.Callable[..., str] = sys.stdin.readline
MOD: int = 1000000007
INF: float = float("Inf")
IINF: int = sys.maxsize
# endregion


def main() -> None:
    s = list(sinput().strip())
    cnt = Counter(s)
    if len(cnt) != 2:
        print("No")
        return

    for v in cnt.values():
        if v != 2:
            print("No")
            break
    else:
        print("Yes")


if __name__ == "__main__":
    main()
