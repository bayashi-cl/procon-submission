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


N = int(input())
A = list(map(int, input().split()))

bit = Bit(N)
inv = 0
for a in A[::-1]:
    a += 1
    inv += bit.cumsum(a)
    bit.add(a, 1)

for c in A:
    print(inv)
    inv -= 2 * c - N + 1
