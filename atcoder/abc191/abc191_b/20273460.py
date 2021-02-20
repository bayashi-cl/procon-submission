n, x = map(int, input().split())
a_list = list(map(int, input().split()))
ans = []
for a in a_list:
    if a != x:
        ans.append(a)
print(*ans)
