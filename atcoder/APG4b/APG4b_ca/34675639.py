from operator import itemgetter

n = int(input())
p = [tuple(map(int, input().split())) for _ in range(n)]
p.sort(key=itemgetter(1))

for ai, bi in p:
    print(ai, bi)
