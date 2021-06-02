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
    len_n = len(str(n))

    num = [[0] * 10 for _ in range(10)]
    for i in range(10):
        if i <= n:
            num[i][i] += 1

    for top in range(1, 10):
        for end in range(1, 10):
            t = 0
            for l in range(len_n - 1):
                for mid in range(10 ** l):
                    if top * 10 ** (l + 1) + mid * 10 + end <= n:
                        t += 1
            num[top][end] += t

    ans = 0
    for top in range(1, 10):
        for end in range(1, 10):
            ans += num[top][end] * num[end][top]

    print(ans)


if __name__ == "__main__":
    main()
