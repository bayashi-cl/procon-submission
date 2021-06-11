# region template
import sys
import typing
from operator import itemgetter

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
    pos = [list(map(int, sinput().split())) for _ in range(n)]
    pos.sort(reverse=True, key=itemgetter(2))

    for i in range(101):
        for j in range(101):
            hight_cand = -1
            for x, y, h in pos:
                if h == 0:
                    if hight_cand == -1:
                        raise ValueError
                    if max(hight_cand - abs(i - x) - abs(j - y), 0) > 0:
                        break
                else:
                    hight = h + abs(i - x) + abs(j - y)
                    if hight != hight_cand and hight_cand != -1:
                        break
                    hight_cand = hight
            else:
                print(i, j, hight_cand)
                return


if __name__ == "__main__":
    main()
