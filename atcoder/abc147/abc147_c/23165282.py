# region template
import sys
import typing

sys.setrecursionlimit(10 ** 6)
Vec = typing.List[int]
VecVec = typing.List[Vec]
sinput: typing.Callable[..., str] = sys.stdin.readline
MOD: int = 1000000007
INF: float = float("Inf")
IINF: int = sys.maxsize
# endregion


def bit2set(s: int) -> set:
    res = set()
    for i in range(s.bit_length()):
        if s & (1 << i) == 0:
            continue
        res.add(i)
    return res


def main() -> None:
    n = int(sinput())

    remark = []
    for _ in range(n):
        a = int(sinput())
        re = []
        for _ in range(a):
            r = tuple(map(int, sinput().split()))
            re.append(r)
        remark.append(re)

    ans = 0

    for s in range(1 << n):
        honest = bit2set(s)
        people = [False] * n
        for h in honest:
            people[h] = True

        for h in honest:
            for say in remark[h]:
                if say[1] == 1:  # 正直
                    if people[say[0] - 1] is False:
                        break

                else:
                    if people[say[0] - 1] is True:
                        break

            else:
                continue
            break
        else:
            ans = max(ans, len(honest))

    print(ans)


if __name__ == "__main__":
    main()
