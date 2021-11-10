import strutils

var s = stdin.readLine
var flg = true
# var left = s.len
var suffix = ["dreamer", "dream", "eraser", "erase"]

while flg and s.len != 0:
  # if s.continuesWith("dreamer", max(left - 7, 0)):
  #   left -= 7
  # elif s.continuesWith("eraser", max(left - 6, 0)):
  #   left -= 6
  # elif s.continuesWith("dream", max(left - 5, 0)):
  #   left -= 5
  # elif s.continuesWith("erase", max(left - 5, 0)):
  #   left -= 5

  flg = false
  for su in suffix:
    if s.endsWith(su):
      s.removeSuffix(su)
      flg = true

if flg:
  echo "YES"
else:
  echo "NO"
