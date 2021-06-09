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
        mid = (ok + ng) >> 1
        if is_ok(mid, *args):
            ok = mid
        else:
            ng = mid
    return ok


def main() -> None:
    x, y, z, k = map(int, sinput().split())
    a = list(map(int, sinput().split()))
    b = list(map(int, sinput().split()))
    c = list(map(int, sinput().split()))

    bc = []
    for bi in b:
        for ci in c:
            bc.append(bi + ci)
    bc.sort(reverse=True)

    ans = []
    for bci in bc[: min(k, len(bc))]:
        for ai in a:
            ans.append(ai + bci)

    ans.sort(reverse=True)
    print("\n".join(map(str, ans[:k])))


if __name__ == "__main__":
    main()
