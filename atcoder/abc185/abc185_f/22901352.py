# region template
import sys
import typing
import operator

sys.setrecursionlimit(10 ** 6)
Vec = typing.List[int]
VecVec = typing.List[Vec]
sinput: typing.Callable[..., str] = sys.stdin.readline
MOD: int = 1000000007
INF: float = float("Inf")
IINF: int = sys.maxsize
# endregion


class SegmentTree:
    """非再帰セグメント木"""

    def __init__(
        self,
        val: typing.Union[typing.List[int], typing.List[float]],
        func: typing.Callable,
        indent: float = 0,
    ) -> None:
        import operator

        self.n = len(val)
        self.n_leaf = 1 << (self.n - 1).bit_length()

        assert self.n > 0
        self.inf = float("inf")

        self.func = func
        if self.func == max:
            self.ident = -self.inf
        elif self.func == min:
            self.ident = self.inf
        elif self.func == operator.add:
            self.ident = 0
        elif self.func == operator.mul:
            self.ident = 1
        else:
            self.ident = indent

        self.tree = [self.ident] * (2 * self.n_leaf)
        self.tree[self.n_leaf : self.n_leaf + self.n] = val
        for i in range(self.n_leaf - 1, 0, -1):
            self.tree[i] = self.func(self.tree[i * 2], self.tree[i * 2 + 1])

    def query(self, l: int, r: int) -> float:
        l += self.n_leaf
        r += self.n_leaf
        res = self.ident
        while l < r:
            if l & 1:
                res = self.func(res, self.tree[l])
                l += 1
            if r & 1:
                r -= 1
                res = self.func(res, self.tree[r])
            l >>= 1
            r >>= 1
        return res

    def add(self, i: int, val: float) -> None:
        i += self.n_leaf
        self.tree[i] = self.func(self.tree[i], val)
        while i > 0:
            i >>= 1
            self.tree[i] = self.func(self.tree[i * 2], self.tree[i * 2 + 1])

    def update(self, i: int, val: float) -> None:
        i += self.n_leaf
        self.tree[i] = val
        while i > 0:
            i >>= 1
            self.tree[i] = self.func(self.tree[i * 2], self.tree[i * 2 + 1])


def main() -> None:
    n, q = map(int, sinput().split())

    a = list(map(int, sinput().split()))

    st = SegmentTree(a, operator.xor, 0)

    for _ in [None] * q:
        t, x, y = map(int, sinput().split())
        if t == 1:
            st.add(x - 1, y)
        else:
            print(st.query(x - 1, y))


if __name__ == "__main__":
    main()
