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
    a.sort()
    small = a[:n]
    big = a[n:]
    ans = []

    for s, b in zip(small, big):
        ans.append(s)
        ans.append(b)

    print(" ".join(map(str, ans)))


if __name__ == "__main__":
    case = int(sinput())
    for i in range(case):
        main()
