# region template
import sys
import typing
from typing import Callable, Dict, List, Set, Tuple

sys.setrecursionlimit(10 ** 6)
Vec = List[int]
VecVec = List[Vec]
sinput: Callable[..., str] = sys.stdin.readline
MOD: int = 1000000007
INF: float = float("Inf")
IINF: int = sys.maxsize
# endregion


def main() -> None:
    n, k = map(int, sinput().split())
    kk = k * 2
    black = [[0] * (4 * k + 1) for _ in range(4 * k + 1)]
    # white = [[0] * (4 * k + 1) for _ in range(4 * k + 1)]
    for _ in range(n):
        x_, y_, c = sinput().split()
        x = int(x_)
        y = int(y_)
        if c == "W":
            x -= k
        black[x % kk + 1][y % kk + 1] += 1
        black[x % kk + kk + 1][y % kk + 1] += 1
        black[x % kk + 1][y % kk + kk + 1] += 1
        black[x % kk + kk + 1][y % kk + kk + 1] += 1

        # if c == "B":
        #     black[x % kk + 1][y % kk + 1] += 1
        #     black[x % kk + kk + 1][y % kk + 1] += 1
        #     black[x % kk + 1][y % kk + kk + 1] += 1
        #     black[x % kk + kk + 1][y % kk + kk + 1] += 1
        # else:
        #     white[x % kk + 1][y % kk + 1] += 1
        #     white[x % kk + kk + 1][y % kk + 1] += 1
        #     white[x % kk + 1][y % kk + kk + 1] += 1
        #     white[x % kk + kk + 1][y % kk + kk + 1] += 1

    for i in range(1, 4 * k + 1):
        for j in range(1, 4 * k + 1):
            black[i][j] += black[i][j - 1]
            # white[i][j] += white[i][j - 1]

    for i in range(1, 4 * k + 1):
        for j in range(1, 4 * k + 1):
            black[i][j] += black[i - 1][j]
            # white[i][j] += white[i - 1][j]

    ans = 0
    for i in range(kk):
        for j in range(kk):
            b1 = black[i + k][j + k] + black[i][j] - black[i + k][j] - black[i][j + k]
            b2 = (
                black[i + kk][j + kk]
                + black[i + k][j + k]
                - black[i + k][j + kk]
                - black[i + kk][j + k]
            )

            # w1 = (
            #     white[i + kk][j + k]
            #     + white[i + k][j]
            #     - white[i + kk][j]
            #     - white[i + k][j + k]
            # )
            # w2 = (
            #     white[i + k][j + kk]
            #     + white[i][j + k]
            #     - white[i][j + kk]
            #     - white[i + k][j + k]
            # )

            # ans = max(ans, b1 + b2 + w1 + w2)
            ans = max(ans, b1 + b2)

    print(ans)


if __name__ == "__main__":
    main()
