import sys
from array import array

readline = sys.stdin.readline


def main(**kwargs) -> None:
    h, w = map(int, readline().split())
    a = [array("i", map(int, readline().split())) for _ in range(h)]

    row = array("i", [sum(r) for r in a])
    col = array("i", [sum(c) for c in zip(*a)])

    ans = [array("i", [0] * w) for _ in range(h)]
    for i in range(h):
        for j in range(w):
            ans[i][j] = row[i] + col[j] - a[i][j]

    for e in ans:
        print(*e)


if __name__ == "__main__":
    main()
