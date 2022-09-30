n, m = map(int, input().split())
a = set(map(int, input().split()))
b = map(int, input().split())


ans = list(filter(lambda bi: bi not in a, b))
print(len(ans))
print(*ans, sep="\n")
