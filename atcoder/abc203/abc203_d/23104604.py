# region template
import sys
import typing

import numpy as np

sys.setrecursionlimit(10 ** 6)
Vec = typing.List[int]
VecVec = typing.List[Vec]
sinput: typing.Callable[..., str] = sys.stdin.readline
MOD: int = 1000000007
INF: float = float("Inf")
IINF: int = sys.maxsize
# endregion


def meguru_bisect(ok: int, ng: int, is_ok: typing.Callable[..., bool], *args) -> int:
    """二分探索法
    Args:
        ok (int): is_okを満たす初期値
        ng (int): is_okを満たさない初期値
        is_ok (typing.Callable[..., bool]): 判定用関数
        *args (object): is_okに渡される引数

    Returns:
        int: is_okを満たす最大/小の整数
    """
    assert is_ok(ok, *args)
    assert not is_ok(ng, *args)

    while abs(ok - ng) > 1:
        mid = (ok + ng) // 2
        if is_ok(mid, *args):
            ok = mid
        else:
            ng = mid
    return ok


def main() -> None:
    n, k = map(int, sinput().split())
    arr = np.array([list(map(int, sinput().split())) for _ in range(n)], dtype=np.int64)

    lim = k ** 2 // 2 + 1
    ok = int(arr.max())
    ng = -1

    def is_ok(mid) -> bool:
        cs = np.zeros((n + 1, n + 1), dtype=np.int64)
        cs[1:, 1:] = np.where(arr > mid, 1, 0)
        cs[1:, 1:] = np.cumsum(cs[1:, 1:], axis=0)
        cs[1:, 1:] = np.cumsum(cs[1:, 1:], axis=1)
        res = cs[:-k, :-k] + cs[k:, k:] - cs[k:, :-k] - cs[:-k, k:]
        return res.min() < lim

    ans = meguru_bisect(ok, ng, is_ok)
    print(ans)


if __name__ == "__main__":
    main()
