a, b, c = map(int, input().split())


one = a % 10
loop = [one]
n = one
while True:
    n = one * n % 10
    if n not in loop:
        loop.append(n)
    else:
        break
ans = loop[pow(b, c, len(loop)) - 1]
print(ans)