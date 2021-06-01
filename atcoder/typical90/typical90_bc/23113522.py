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
    n, p, q = map(int, sinput().split())
    a = list(map(int, sinput().split()))

    ans = 0
    for i in range(n):
        for j in range(i + 1, n):
            for k in range(j + 1, n):
                for l in range(k + 1, n):
                    for m in range(l + 1, n):
                        if a[i] * a[j] % p * a[k] % p * a[l] % p * a[m] % p == q:
                            ans += 1
    print(ans)


if __name__ == "__main__":
    main()
