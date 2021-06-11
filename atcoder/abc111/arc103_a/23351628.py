# region template
import sys
import typing
from collections import Counter

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
    v = list(map(int, sinput().split()))
    up = v[::2]
    down = v[1::2]
    cnt_up = Counter(up)
    cnt_up[0] = 0
    cnt_down = Counter(down)
    cnt_down[0] = 0
    ans = INF
    for u_v, u_n in cnt_up.most_common(2):
        for d_v, d_n in cnt_down.most_common(2):
            if u_v == d_v:
                continue
            ans = min(ans, n - u_n - d_n)

    print(ans)


if __name__ == "__main__":
    main()
