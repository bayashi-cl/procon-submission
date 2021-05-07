# region template
import sys
from typing import Any, Callable
import math
from bisect import bisect_left

sys.setrecursionlimit(10 ** 9)
sinput: Callable[..., str] = sys.stdin.readline
INF: float = float("inf")
MOD: int = 10 ** 9 + 7
# endregion


def main() -> None:
    n = int(sinput())
    point = [list(map(int, sinput().split())) for _ in range(n)]
    ans = 0.0

    for i in range(n):
        o0 = point[i][0]
        o1 = point[i][1]
        dec = [math.degrees(math.atan2(p[1] - o1, p[0] - o0)) for p in point]
        del dec[i]

        for d in dec:
            if d < 0:
                d += 360
        dec.sort()

        for d in dec:
            opp = (d + 180) % 360
            idx = bisect_left(dec, opp)
            max_dec0 = abs(dec[idx - 1] - d)
            if max_dec0 > 180:
                max_dec0 = 360 - max_dec0

            if idx == n - 1:
                max_dec1 = abs(dec[0] - d)
            else:
                max_dec1 = abs(dec[idx] - d)

            if max_dec1 > 180:
                max_dec1 = 360 - max_dec1
            ans = max(max_dec0, max_dec1, ans)

    print(ans)


if __name__ == "__main__":
    main()
