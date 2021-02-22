from math import ceil


def find_divisor(n):
    divisor = set()
    for i in range(1, ceil(n ** 0.5) + 1):
        if n % i == 0:
            divisor.add(i)
            divisor.add(n // i)
    return divisor


N = int(input())
ans = 0

for d in find_divisor(N):
    if d % 2 == 1:
        ans += 1

for d in find_divisor(2 * N):
    if d % 2 == 0 and (2 * N // d) % 2 == 1:
        ans += 1

print(ans)
