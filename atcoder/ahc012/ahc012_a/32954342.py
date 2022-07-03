from math import cos, pi, sin

n, k = map(int, input().split())
for _ in range(n):
    input()
print(k)
for i in range(k):
    x = int(cos(pi * i / k) * 1000)
    y = int(sin(pi * i / k) * 1000)
    print(0, 0, x, y)
