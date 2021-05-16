# region template
import sys
import typing
from collections import defaultdict

sys.setrecursionlimit(10 ** 9)
Vec = typing.List[int]
VecVec = typing.List[Vec]
sinput: typing.Callable[..., str] = sys.stdin.readline
MOD: int = 1000000007
INF: float = float("Inf")
IINF: int = sys.maxsize
# endregion


def main() -> None:
    n = int(sinput())
    d = defaultdict(set)
    for _ in range(n):
        s = sinput().strip()
        if s[0] == "!":
            d[s[1:]].add(1)
        else:
            d[s].add(0)

    for i, v in d.items():
        if v == {0, 1}:
            print(i)
            break
    else:
        print("satisfiable")


if __name__ == "__main__":
    main()
