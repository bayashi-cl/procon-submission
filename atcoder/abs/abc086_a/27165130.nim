import strutils
import sequtils

var
  a, b: int
(a, b) = readLine(stdin).split().map(parseInt)

if a * b mod 2 == 1:
  echo "Odd"
else:
  echo "Even"
