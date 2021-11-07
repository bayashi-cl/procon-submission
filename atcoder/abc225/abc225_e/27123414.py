# region template
import sys
import typing
from typing import Callable, Dict, List, Set, Tuple

sys.setrecursionlimit(10 ** 6)
Vec = List[int]
VecVec = List[Vec]
sinput: Callable[..., str] = sys.stdin.readline
MOD: int = 998244353
INF: float = float("Inf")
IINF: int = sys.maxsize // 2
# endregion


class Point:
    x: int
    y: int

    def __init__(self, x: int, y: int) -> None:
        self.x = x
        self.y = y

    def det(self, other: "Point") -> int:
        return self.x * other.y - self.y * other.x

    def __lt__(self, other: "Point") -> bool:
        return self.det(other) > 0

    def __le__(self, other: "Point") -> bool:
        return self.det(other) >= 0

    def __repr__(self) -> str:
        return f"[{self.x}, {self.y}]"


def main() -> None:
    n = int(sinput())
    hu: List[Tuple[Point, Point]] = []
    for _ in range(n):
        x, y = map(int, sinput().split())
        hu.append((Point(x - 1, y), Point(x, y - 1)))

    hu.sort()
    ans = 0
    now = Point(1, 0)
    for end, start in hu:
        if start >= now:
            ans += 1
            now = end
    print(ans)


if __name__ == "__main__":
    main()
