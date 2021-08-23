n = int(input())
a = list(map(int, input().split()))
ans = 0
for i, ai in enumerate(a):
  if i % 2 == 0 and ai % 2 == 1:
    ans += 1
print(ans)
