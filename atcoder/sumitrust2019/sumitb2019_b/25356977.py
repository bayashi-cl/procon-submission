n = int(input())
for x in range(1, 50000):
  if int(x * 1.08) == n:
    print(x)
    break
else:
  print(":(")