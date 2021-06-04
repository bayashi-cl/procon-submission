# region template
import sys
import typing

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
    a, b, x = map(int, sinput().split())

    def is_ok(n: int) -> bool:
        return x >= a * n + b * len(str(n))

    if not is_ok(1):
        print(0)
        return
    if is_ok(10 ** 9):
        print(10 ** 9)
        return

    ans = meguru_bisect(1, 10 ** 9 + 1, is_ok)
    print(ans)


if __name__ == "__main__":
    main()
