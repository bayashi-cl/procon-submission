from collections import Counter

n = int(input())
cnt = Counter(input() for _ in range(n))
print(cnt.most_common()[0][0])
