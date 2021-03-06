from operator import itemgetter

N = int(input())
e = [tuple(map(int, input().split())) for _ in range(N)]
fast_a = min(e)
e.remove(fast_a)
e.append((0, sum(fast_a)))
fast_b = min(e, key=itemgetter(1))
print(max(fast_a[0], fast_b[1]))
