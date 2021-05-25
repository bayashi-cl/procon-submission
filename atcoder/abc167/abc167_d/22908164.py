# region template
import sys
import typing

sys.setrecursionlimit(10 ** 6)
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

    path = []
    path_set = set()
    now = 1
    while True:
        path.append(now)
        path_set.add(now)
        to = a[now - 1]
        if to in path_set:
            break
        now = to

    entry = path.index(to)
    roop = len(path) - entry

    if k <= entry:
        ans = path[k]
    else:
        ans = path[entry:][(k - entry) % roop]

    print(ans)


if __name__ == "__main__":
    main()
