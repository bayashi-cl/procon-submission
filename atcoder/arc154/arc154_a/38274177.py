n = int(input())
a = list(input())
b = list(input())

for i in range(n):
    if int(a[i]) > int(b[i]):
        a[i], b[i] = b[i], a[i]

print(int("".join(a)) * int("".join(b)) % 998244353)
