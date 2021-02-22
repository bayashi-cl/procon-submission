from itertools import product

n, m = map(int, input().split())
cond = [list(map(int, input().split())) for _ in range(m)]
k = int(input())
choice = [list(map(int, input().split())) for _ in range(k)]
ans = 0

for ball in product(*choice):
    filled_dish = set(ball)
    cnt = 0
    for c in cond:
        if set(c) <= filled_dish:
            cnt += 1
    if cnt > ans:
        ans = cnt

print(ans)
