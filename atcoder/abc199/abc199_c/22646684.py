# region template
import sys
import typing

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
    s = list(sinput().strip())
    q = int(sinput())
    rev = False
    for _ in range(q):
        t, a, b = map(int, sinput().split())
        if t == 1:
            a -= 1
            b -= 1
            if rev:
                a = (a + n) % (2 * n)
                b = (b + n) % (2 * n)

            s[a], s[b] = s[b], s[a]

        elif t == 2:
            rev = not rev

    if rev:
        s = s[n:] + s[:n]

    print("".join(s))


if __name__ == "__main__":
    main()
