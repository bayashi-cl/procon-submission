# region template
import sys
import typing
from bisect import bisect

sys.setrecursionlimit(10 ** 6)
Vec = typing.List[int]
VecVec = typing.List[Vec]
sinput: typing.Callable[..., str] = sys.stdin.readline
MOD: int = 1000000007
INF: float = float("Inf")
IINF: int = sys.maxsize
# endregion


def main() -> None:
    a, b, q = map(int, sinput().split())
    shrine = [-IINF, -IINF + 1] + [int(sinput()) for _ in range(a)] + [IINF - 1, IINF]
    temple = [-IINF, -IINF + 1] + [int(sinput()) for _ in range(b)] + [IINF - 1, IINF]

    for _ in range(q):
        ans = INF
        que = int(sinput())

        # shrine -> temple
        i = bisect(shrine, que)
        cand_pos = (shrine[i - 1], shrine[i])
        cand_dist = (abs(que - shrine[i - 1]), abs(que - shrine[i]))

        for dist, pos in zip(cand_dist, cand_pos):
            j = bisect(temple, pos)
            dist += min(abs(pos - temple[j - 1]), abs(pos - temple[j]))
            ans = min(ans, dist)

        # temple -> shrine
        i = bisect(temple, que)
        cand_pos = (temple[i - 1], temple[i])
        cand_dist = (abs(que - temple[i - 1]), abs(que - temple[i]))

        for dist, pos in zip(cand_dist, cand_pos):
            j = bisect(shrine, pos)
            dist += min(abs(pos - shrine[j - 1]), abs(pos - shrine[j]))
            ans = min(ans, dist)

        print(ans)


if __name__ == "__main__":
    main()
