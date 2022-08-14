input()
dp = {0}
for pi in map(int, input().split()):
    dq = list(dp)
    for e in dq:
        dp.add(e + pi)
print(len(dp))
