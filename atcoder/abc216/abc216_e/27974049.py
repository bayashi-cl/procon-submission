# region template
import sys
import typing
from typing import Callable, Dict, List, Set, Tuple

sys.setrecursionlimit(10 ** 6)
Vec = List[int]
VecVec = List[Vec]
sinput: Callable[..., str] = sys.stdin.readline
MOD: int = 998244353
INF: float = float("Inf")
IINF: int = sys.maxsize // 2
# endregion


def meguru_bisect(ok: int, ng: int, is_ok: Callable[..., bool], *args) -> int:
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
        mid = (ok + ng) >> 1
        if is_ok(mid, *args):
            ok = mid
        else:
            ng = mid
    return ok


def main() -> None:
    n, k = map(int, sinput().split())
    a = tuple(map(int, sinput().split()))

    def ok(th: int) -> bool:
        if th < 0:
            return False
        cnt = 0
        for ai in a:
            if ai < th:
                continue
            cnt += ai - th + 1
        return cnt <= k

    th = meguru_bisect(max(a) + 1, -1, ok)

    ans = 0
    for ai in a:
        if ai < th:
            continue
        t = ai - th + 1
        k -= t
        ans += (th + ai) * t // 2
    ans += max(th - 1, 0) * k
    print(ans)


if __name__ == "__main__":
    main()
