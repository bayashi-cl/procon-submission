# region template
import sys
import typing

# from bisect import bisect_right as bisect
# from itertools import combinations
# import math

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
    n, k = map(int, sinput().split())
    a = map(int, sinput().split())
    negative = []
    positive = []
    n_zero = 0
    for ai in a:
        if ai < 0:
            negative.append(ai)
        elif ai == 0:
            n_zero += 1
        else:
            positive.append(ai)
    negative.sort()
    positive.sort()

    n_neg = len(negative)
    n_pos = len(positive)
    mul_neg = n_neg * n_pos
    mul_pos = n_neg * (n_neg - 1) // 2 + n_pos * (n_pos - 1) // 2
    mul_zero = n_zero * (n_neg + n_pos) + n_zero * (n_zero - 1) // 2

    if k <= mul_neg:

        ok = 0
        ng = -(10 ** 18 + 1)

        def is_ok(mid):
            cnt = 0
            pos = 0
            for neg in range(n_neg):
                while pos < n_pos and negative[neg] * positive[pos] > mid:
                    pos += 1
                cnt += n_pos - pos

            return cnt >= k

        ans = meguru_bisect(ok, ng, is_ok)

    elif k <= mul_neg + mul_zero:
        ans = 0

    else:
        k -= mul_neg + mul_zero
        ok = 10 ** 18 + 1
        ng = 0

        def is_ok(mid):
            cnt = 0

            r = n_pos - 1
            for l in range(n_pos):
                while r < n_pos and positive[l] * positive[r] > mid and l < r:
                    r -= 1

                cnt += max(0, r - l)

            l = 0
            for r in reversed(range(n_neg)):
                while (l < n_neg) and negative[l] * negative[r] > mid and l < r:
                    l += 1
                cnt += max(0, r - l)

            return cnt >= k

        ans = meguru_bisect(ok, ng, is_ok)

    print(ans)


if __name__ == "__main__":
    main()
