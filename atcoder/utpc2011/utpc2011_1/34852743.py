n, _ = map(int, input().split())
a = [list(map(int, input().split())) for _ in range(n)]
print(max(sum(ai) for ai in a))
