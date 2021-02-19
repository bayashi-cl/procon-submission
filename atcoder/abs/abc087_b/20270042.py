from itertools import product

a = int(input())
b = int(input())
c = int(input())
x = int(input())

ans = 0

al = [500 * i for i in range(a + 1)]
bl = [100 * i for i in range(b + 1)]
cl = [50 * i for i in range(c + 1)]

p = product(al, bl, cl)
for pi in p:
    if sum(pi) == x:
        ans += 1
print(ans)