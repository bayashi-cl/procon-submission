# region template
import sys
import typing
from itertools import permutations

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
    a = [list(map(int, sinput().split())) for _ in range(n)]
    m = int(sinput())
    ban = [set() for _ in range(n)]

    for _ in range(m):
        x, y = map(int, sinput().split())
        ban[x - 1].add(y - 1)
        ban[y - 1].add(x - 1)

    ans = IINF
    for per in permutations(range(n)):
        for i in range(n - 1):
            if per[i + 1] in ban[per[i]]:
                break
        else:
            time = 0
            for i, p in enumerate(per):
                time += a[p][i]
            ans = min(ans, time)
    if ans == IINF:
        print(-1)
    else:
        print(ans)


if __name__ == "__main__":
    main()
