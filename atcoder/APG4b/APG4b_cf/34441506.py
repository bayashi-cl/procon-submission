from itertools import product

n, s = map(int, input().split())
a = map(int, input().split())
p = map(int, input().split())

print(sum(ai + pi == s for ai, pi in product(a, p)))
