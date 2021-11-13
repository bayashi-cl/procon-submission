# region template
import sys
import typing
from collections import deque
from typing import Callable, Dict, List, Set, Tuple

sys.setrecursionlimit(10 ** 6)
Vec = List[int]
VecVec = List[Vec]
# sinput: Callable[..., str] = sys.stdin.readline
MOD: int = 998244353
INF: float = float("Inf")
IINF: int = sys.maxsize // 2
# endregion


class TaskManager:
    depend: VecVec
    deg_cnt: Vec
    wait: Set[int]

    def __init__(self, depend: VecVec, deg_cnt: Vec) -> None:
        self.depend = depend
        self.deg_cnt = deg_cnt
        self.wait = set()
        for i, di in enumerate(self.deg_cnt):
            if di == 0:
                self.wait.add(i)

    def send(self, task: int) -> None:
        self.wait.remove(task)

    def done(self, task: int) -> None:
        assert self.deg_cnt[task] == 0

        for nxt in self.depend[task]:
            self.deg_cnt[nxt] -= 1
            if self.deg_cnt[nxt] == 0:
                self.wait.add(nxt)

    def startable(self) -> List[int]:
        return list(self.wait)


def main() -> None:
    n, m, k, r = map(int, input().split())
    _ = [list(map(int, input().split())) for _ in range(n)]
    depend: VecVec = [list() for _ in range(n)]
    deg_cnt = [0] * n
    for _ in range(r):
        u, v = map(lambda x: int(x) - 1, input().split())
        depend[u].append(v)
        deg_cnt[v] += 1

    tm = TaskManager(depend, deg_cnt)
    member = deque(range(m))
    doing = [-1] * m

    for _ in range(2000):
        able = tm.startable()
        sz = min(len(able), len(member))
        send = []
        for i in range(sz):
            mi = member.popleft()
            ti = able[i]
            doing[mi] = ti
            tm.send(ti)
            send.append(mi + 1)
            send.append(ti + 1)
        print(sz, *send, flush=True)

        res = list(map(int, input().split()))
        if res[0] == -1:
            return
        done = [di - 1 for di in res[1:]]
        for di in done:
            tm.done(doing[di])
            doing[di] -= 1
            member.append(di)


if __name__ == "__main__":
    main()
