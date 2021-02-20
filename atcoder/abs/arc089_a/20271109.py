n = int(input())
d_list = [list(map(int, input().split())) for _ in range(n)]
t = 0
p = [0, 0]
for d in d_list:
    dist = abs(sum(p) - sum(d[1:]))
    limit = d[0] - t
    if dist > limit or dist % 2 != limit % 2:
        print("No")
        break
    t = d[0]
    p = d[1:]
else:
    print("Yes")
