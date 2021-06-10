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
    n = int(sinput())
    a = list(map(int, sinput().split()))
    prev = a[:]
    mi = min(a)
    while True:
        a = [0] * n
        for i in range(n):
            a[i] = prev[i] % mi
            if a[i] == 0:
                a[i] = mi
        if a == prev:
            break
        prev = a[:]
        mi = min(prev)
    print(min(a))


if __name__ == "__main__":
    main()
