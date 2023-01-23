n = int(input())
a = list(input())
b = list(input())


for i in range(n):
    if int(a[i]) > int(b[i]):
        a[i], b[i] = b[i], a[i]

c = int("".join(a)) % 998244353
d = int("".join(b)) % 998244353

print(c * d % 998244353)
