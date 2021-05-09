# region template
import sys
from typing import Callable


sys.setrecursionlimit(10 ** 9)
sinput: Callable[..., str] = sys.stdin.readline
INF: float = float("inf")
MOD: int = 10 ** 9 + 7
# endregion


def main() -> None:
    n = int(sinput())
    a, b, c = sorted(list(map(int, sinput().split())))
    ans = INF

    for k in range(n // c, -1, -1):
        r = n - c * k
        for j in range(r // b, -1, -1):
            s = r - j * b
            if s % a == 0:
                ans = min(ans, k + j + s // a)
                break
    print(ans)


if __name__ == "__main__":
    main()
