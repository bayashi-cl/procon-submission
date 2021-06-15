# region template
import sys
import typing
from itertools import accumulate

sys.setrecursionlimit(10 ** 6)
Vec = typing.List[int]
VecVec = typing.List[Vec]
sinput: typing.Callable[..., str] = sys.stdin.readline
MOD: int = 1000000007
INF: float = float("Inf")
IINF: int = sys.maxsize
# endregion


class BinaryIndexedTree:
    """フェニック木
    **0-index**
    """

    def __init__(self, size: int) -> None:
        self.size = size
        self.tree = [0] * (size + 1)

    def add(self, i: int, x: int) -> None:
        i += 1
        while i <= self.size:
            self.tree[i] += x
            i += i & -i

    def cumsum(self, r: int) -> int:
        """累積和
        [0, r)の和を求める。
        """
        s = 0
        while r:
            s += self.tree[r]
            r -= r & -r
        return s

    def range_sum(self, l: int, r: int) -> int:
        """部分和
        [l, r)の和を求める。
        """
        return self.cumsum(r) - self.cumsum(l)

    @classmethod
    def construct(cls, array: typing.List[int]) -> "BinaryIndexedTree":
        res = cls(len(array))
        for ele in enumerate(array):
            res.add(*ele)

        return res


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
    n = int(sinput())
    a = list(map(int, sinput().split()))
    if n == 1:
        print(a[0])
        return
    ok = 0
    ng = 10 ** 9 + 10

    med = ((n + 1) * n // 2 + 1) // 2

    def check(x: int) -> bool:
        comp = [1 if ai >= x else -1 for ai in a]
        cs = [0] + list(accumulate(comp))
        bit = BinaryIndexedTree(2 * n + 10)
        cnt = 0
        for c in cs:
            c += n + 1
            bit.add(c, 1)
            cnt += bit.range_sum(c + 1, 2 * n + 10)

        return cnt <= med

    ans = meguru_bisect(ok, ng, check)
    print(ans)


if __name__ == "__main__":
    main()
