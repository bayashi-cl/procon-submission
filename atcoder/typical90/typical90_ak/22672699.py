# region template
import sys
import typing

sys.setrecursionlimit(10 ** 9)
Vec = typing.List[int]
VecVec = typing.List[Vec]
sinput: typing.Callable[..., str] = sys.stdin.readline
MOD: int = 1000000007
INF: float = float("Inf")
IINF: int = sys.maxsize
# endregion

T = typing.TypeVar("T", int, float)


class SegmentTree(typing.Generic[T]):

    inf: T
    ident: T
    tree: typing.List[typing.Optional[T]]

    def __init__(self, val: typing.List[T], func: typing.Callable) -> None:
        import sys
        import operator

        self.n = len(val)
        self.n_leaf = 1 << (self.n - 1).bit_length()

        assert self.n > 0
        if isinstance(val[0], int):
            self.inf = sys.maxsize
        else:
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
            raise ValueError

        self.tree = [self.ident] * (2 * self.n_leaf)
        self.tree[self.n_leaf : self.n_leaf + self.n] = val
        for i in range(self.n_leaf - 1, 0, -1):
            self.tree[i] = self.func(self.tree[i * 2], self.tree[i * 2 + 1])

    def query(self, l: int, r: int) -> T:
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

    def update(self, i: int, val: T) -> None:
        i += self.n_leaf
        self.tree[i] = val
        while i > 0:
            i >>= 1
            self.tree[i] = self.func(self.tree[i * 2], self.tree[i * 2 + 1])


def main() -> None:
    w, n = map(int, sinput().split())
    dish = [list(map(int, sinput().split())) for _ in range(n)]
    dp = [[-INF] * (w + 1) for _ in range(n + 1)]
    dp[0][0] = 0
    for i in range(1, n + 1):
        st = SegmentTree(dp[i - 1], max)
        for j in range(w + 1):
            dp[i][j] = dp[i - 1][j]

            l = max(0, j - dish[i - 1][1])
            r = max(0, j - dish[i - 1][0] + 1)
            dp[i][j] = max(dp[i][j], st.query(l, r) + dish[i - 1][2])

    ans = dp[n][w]
    if ans <= 0:
        print(-1)
    else:
        print(ans)


if __name__ == "__main__":
    main()
