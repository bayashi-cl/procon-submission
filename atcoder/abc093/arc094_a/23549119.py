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
    a, b, c = map(int, sinput().split())
    ans = 0
    if a % 2 == b % 2 and b % 2 == c % 2:
        pass
    else:
        ans += 1
        if a % 2 == b % 2:
            a += 1
            b += 1
        elif b % 2 == c % 2:
            b += 1
            c += 1
        elif a % 2 == c % 2:
            a += 1
            c += 1
        else:
            raise ValueError

    ma = max(a, b, c)
    for i in (a, b, c):
        ans += (ma - i) // 2

    print(ans)


if __name__ == "__main__":
    main()
