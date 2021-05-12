# region template
from operator import itemgetter
import sys
from typing import Callable
from itertools import chain
from collections import Counter


sinput: Callable[..., str] = sys.stdin.readline

# endregion


class Bit:
    def __init__(self, size):
        self.size = size
        self.tree = [0] * (size + 1)

    def add(self, i, x):
        while i <= self.size:
            self.tree[i] += x
            i += i & -i

    def cumsum(self, i):
        s = 0
        while i:
            s += self.tree[i]
            i -= i & -i
        return s


def main() -> None:
    n, m = map(int, sinput().split())
    line = [list(map(int, sinput().split())) for _ in range(m)]
    line.sort(key=itemgetter(1, 0))

    ans1 = 0
    v1 = [0] * (n + 1)
    v2 = [0] * (n + 1)
    for l, r in line:
        v1[r] += 1
        v2[l - 1] += 1
    for i in range(1, n + 1):
        v1[i] += v1[i - 1]
        ans1 += v1[i] * v2[i]

    ans2 = 0
    count = Counter(chain.from_iterable(line))
    for c in count.values():
        ans2 += c * (c - 1) // 2

    ans3 = 0
    bit = Bit(n + 1)
    for i in range(m):
        l = line[i][0]
        ans3 += i - bit.cumsum(l)
        bit.add(l, 1)

    whole = m * (m - 1) // 2
    ans = whole - (ans1 + ans2 + ans3)
    print(ans)


if __name__ == "__main__":
    main()
