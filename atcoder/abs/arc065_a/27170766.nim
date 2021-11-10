import strutils

var s = stdin.readLine
var flg = true
var left = s.len

while flg and left > 0:
  if s.continuesWith("dreamer", max(left - 7, 0)):
    left -= 7
  elif s.continuesWith("eraser", max(left - 6, 0)):
    left -= 6
  elif s.continuesWith("dream", max(left - 5, 0)):
    left -= 5
  elif s.continuesWith("erase", max(left - 5, 0)):
    left -= 5

  # if s.endsWith("dreamer"):
  #   s = s[0..s.high-7]
  # elif s.endsWith("eraser"):
  #   s = s[0..s.high-6]
  # elif s.endsWith("dream"):
  #   s = s[0..s.high-5]
  # elif s.endsWith("erase"):
  #   s = s[0..s.high-5]
  else:
    flg = false

if flg:
  echo "YES"
else:
  echo "NO"
