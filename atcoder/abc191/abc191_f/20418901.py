from math import gcd, ceil
from collections import defaultdict

n = int(input())
a = list(map(int, input().split()))
min_a = min(a)
ans = 0


def find_divisor(n):
    divisor = list()
    for i in range(1, ceil(n ** 0.5) + 1):
        if n % i == 0:
            divisor.append(i)
            divisor.append(n // i)
    return divisor


d = defaultdict(int)
for ai in a:
    for div in find_divisor(ai):
        d[div] = gcd(d[div], ai)

for k, v in d.items():
    if k == v and v <= min_a:
        ans += 1

print(ans)
