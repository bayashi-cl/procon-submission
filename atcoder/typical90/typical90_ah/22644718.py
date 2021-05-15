# region template
import sys
import typing
from collections import deque, defaultdict

sys.setrecursionlimit(10 ** 9)
Vec = typing.List[int]
VecVec = typing.List[Vec]
sinput: typing.Callable[..., str] = sys.stdin.readline
MOD: int = 1000000007
INF: float = float("Inf")
IINF: int = sys.maxsize
# endregion


def main() -> None:
    n, k = map(int, sinput().split())
    a = list(map(int, sinput().split()))
    l = 0
    r = 0
    d = defaultdict(int)
    ans = 0
    length = 0
    for l in range(n):
        d[a[l]] += 1
        length += 1
        if len(d) > k:
            while len(d) > k:
                d[a[r]] -= 1
                if d[a[r]] == 0:
                    del d[a[r]]
                r += 1
                length -= 1
        ans = max(length, ans)

    print(ans)


if __name__ == "__main__":
    main()
