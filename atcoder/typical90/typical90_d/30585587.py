import sys

readline = sys.stdin.readline


def main(**kwargs) -> None:
    h, w = map(int, readline().split())
    a = [list(map(int, readline().split())) for _ in range(h)]

    col = [0] * w

    row = [sum(r) for r in a]
    col = [sum(c) for c in zip(*a)]

    ans = [[0] * w for _ in range(h)]
    for i in range(h):
        for j in range(w):
            ans[i][j] = row[i] + col[j] - a[i][j]

    for e in ans:
        print(*e)


if __name__ == "__main__":
    main()
