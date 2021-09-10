n = int(input())

max_ab = (0, 0)
for _ in range(n):
  ab = tuple(map(int, input().split()))
  if ab > max_ab:
    max_ab = ab

print(sum(max_ab))
  