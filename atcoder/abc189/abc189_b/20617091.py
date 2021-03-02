from decimal import Decimal

n, x = map(Decimal, input().split())

asum = Decimal(0)
for i in range(int(n)):
    v, p = map(Decimal, input().split())
    asum += v * p / 100
    if asum > x:
        print(i + 1)
        break
else:
    print(-1)
