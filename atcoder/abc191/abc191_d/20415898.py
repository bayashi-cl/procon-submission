import math
from decimal import Decimal

a, b, r = map(Decimal, input().split())
ans = 0
for x in range(math.ceil(a - r), math.floor(a + r) + 1):
    y_b = (r ** 2 - (x - a) ** 2).sqrt()
    ans += math.floor(b + y_b) - math.ceil(b - y_b) + 1

print(ans)
