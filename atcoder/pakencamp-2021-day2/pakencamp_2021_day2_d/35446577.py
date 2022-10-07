from collections import Counter

n, m = map(int, input().split())
cnt = Counter(map(int, input().split()))

common = cnt.most_common()
maxi = common[0][1]
mini = common[-1][1]

for i in range(1, min(m, n + 1) + 1):
    if i not in cnt:
        mini = 0

print(mini, maxi)
