from statistics import mean

input()
a = list(map(int, input().split()))
mu = int(mean(a))
print(*map(lambda ai: abs(ai - mu), a), sep="\n")
