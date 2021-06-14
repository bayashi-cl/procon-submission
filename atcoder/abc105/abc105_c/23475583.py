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
    if n == 0:
        print(0)
        return

    ans = []

    i = 0
    while n:
        if n % (1 << (i + 1)) == 0:
            ans.append(0)
        else:
            ans.append(1)
            n -= (-2) ** i
        i += 1

    print("".join(map(str, reversed(ans))))


if __name__ == "__main__":
    main()
