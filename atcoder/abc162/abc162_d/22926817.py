# region template
import sys
import typing
from itertools import combinations, accumulate

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
    s_ = sinput().strip()

    s = [0] * n
    r = [0] * n
    g = [0] * n
    b = [0] * n

    for i in range(n):
        if s_[i] == "R":
            s[i] = 1
            r[i] = 1
        if s_[i] == "G":
            s[i] = 2
            g[i] = 1
        if s_[i] == "B":
            s[i] = 4
            b[i] = 1

    r = list(accumulate(r))
    g = list(accumulate(g))
    b = list(accumulate(b))

    ans = 0
    for i, j in combinations(range(n - 1), 2):
        if s[i] == s[j]:
            continue
        rgb = 7
        rgb -= s[i] + s[j]

        if rgb == 1:
            k_ok = r[-1] - r[j]
            if j + (j - i) < n:
                if s[j + (j - i)] == 1:
                    k_ok -= 1
        elif rgb == 2:
            k_ok = g[-1] - g[j]
            if j + (j - i) < n:
                if s[j + (j - i)] == 2:
                    k_ok -= 1
        elif rgb == 4:
            k_ok = b[-1] - b[j]
            if j + (j - i) < n:
                if s[j + (j - i)] == 4:
                    k_ok -= 1
        else:
            raise ValueError
        ans += k_ok

    print(ans)


if __name__ == "__main__":
    main()
