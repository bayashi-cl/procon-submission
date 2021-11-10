import strutils

var s = stdin.readLine
var flg = true

while flg and s != "":
  if s.endsWith("dreamer"):
    s = s[0..s.high-7]
  elif s.endsWith("eraser"):
    s = s[0..s.high-6]
  elif s.endsWith("dream"):
    s = s[0..s.high-5]
  elif s.endsWith("erase"):
    s = s[0..s.high-5]
  else:
    flg = false

if flg:
  echo "YES"
else:
  echo "NO"
