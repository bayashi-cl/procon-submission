from collections import Counter

n = int(input())
d = [int(input()) for _ in range(n)]
c = Counter(d)
print(len(c))
