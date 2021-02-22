n, s, d = map(int, input().split())
j = [tuple(map(int, input().split())) for _ in range(n)]

for x, y in j:
    if x < s and y > d:
        ans = "Yes"
        break
else:
    ans = "No"
print(ans)
