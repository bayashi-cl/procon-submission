# region template
import sys
import typing
from math import sin, cos, radians, dist

sys.setrecursionlimit(10 ** 6)
Vec = typing.List[int]
VecVec = typing.List[Vec]
sinput: typing.Callable[..., str] = sys.stdin.readline
MOD: int = 1000000007
INF: float = float("Inf")
IINF: int = sys.maxsize
# endregion


def main() -> None:
    a, b, h, m = map(int, sinput().split())

    h_theta = radians(((60 * h) + m) / 2)
    m_theta = radians(6 * m)

    h_pos = (a * sin(h_theta), a * cos(h_theta))
    m_pos = (b * sin(m_theta), b * cos(m_theta))

    print(dist(h_pos, m_pos))


if __name__ == "__main__":
    main()
