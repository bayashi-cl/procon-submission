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
    box = [0] * (n + 1)

    for i in reversed(range(1, n + 1)):
        ball = 0
        k = 2
        while i * k <= n:
            ball += box[i * k]
            k += 1

        if ball % 2 != a[i - 1]:
            box[i] = 1

    ans = []
    for i in range(1, n + 1):
        if box[i] == 1:
            ans.append(i)

    print(len(ans))
    print(" ".join(map(str, ans)))


if __name__ == "__main__":
    main()
