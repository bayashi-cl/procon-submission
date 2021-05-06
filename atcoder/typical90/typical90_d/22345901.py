# region template
import sys
from typing import Any, Callable


sys.setrecursionlimit(10 ** 9)
sinput: Callable[..., str] = sys.stdin.readline
INF: float = float("inf")
MOD: int = 10 ** 9 + 7
# endregion


def main() -> None:
    h, w = map(int, sinput().split())

    arr = [list(map(int, sinput().split())) for _ in range(h)]

    row = [0] * h
    col = [0] * w

    for i, line in enumerate(arr):
        row[i] = sum(line)
        for j, cj in enumerate(line):
            col[j] += cj

    for i in range(h):
        for j in range(w):
            ans = row[i] + col[j] - arr[i][j]
            print(ans, end=" ")
        print()


if __name__ == "__main__":
    main()
