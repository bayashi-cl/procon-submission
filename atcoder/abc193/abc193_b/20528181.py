n = int(input())
l = [list(map(int, input().split())) for _ in range(n)]

ls = sorted(l, key=lambda x: x[1])
for s in ls:
    if s[2] > s[0]:
        print(s[1])
        break
else:
    print(-1)
