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


def main() -> None:
    n, k = map(int, sinput().split())
    lr = [tuple(map(int, sinput().split())) for _ in range(k)]
    bit = BinaryIndexedTree(n)
    bit.add(0, 1)
    for i in range(n):
        sm = 0
        for l, r in lr:
            if i - l < 0:
                continue
            left = max(0, i - r)
            right = i - l + 1
            sm += bit.range_sum(left, right)
        sm %= MOD
        bit.add(i, sm)
    print(bit.range_sum(n - 1, n))


if __name__ == "__main__":
    main()
