from statistics import mode

input()
a = list(map(int, input().split()))
m = mode(a)
print(m, a.count(m))
