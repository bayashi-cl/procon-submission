a, b, c, d = map(int, input().split())
if a <= c <= b or c <= a <= d:
    print("Yes")
else:
    print("No")
