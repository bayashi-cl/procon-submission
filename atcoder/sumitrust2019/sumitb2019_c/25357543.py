import sys
from functools import lru_cache
 
sys.setrecursionlimit(10 ** 6)
 
x = int(input())
 
@lru_cache(maxsize = None)
def dp(n):
  if n < 100:
    return False
  if 100 <= n <= 105:
    return True
  res = False
  for d in range(100, 106):
    if dp(n - d):
      res = True
  return res
 
if dp(x):
  print(1)
else:
  print(0)