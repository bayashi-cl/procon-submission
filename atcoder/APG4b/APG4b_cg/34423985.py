a = list(map(int, input().split()))

for i, j in zip(a[:-1], a[1:]):
    if i == j:
        print("YES")
        break
else:
    print("NO")