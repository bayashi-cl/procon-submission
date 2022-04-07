# from byslib.core.config import procon_setup
from types import ModuleType

byslib = ModuleType("byslib")
byslib.core = ModuleType("byslib.core")
byslib.core.config = ModuleType("byslib.core.config")

_code_byslib = """
\"""
procon library by bayashi-cl
github repository: https://github.com/bayashi-cl/byslib-python

This library can be expanded with expander.
 - https://github.com/bayashi-cl/expander
\"""

__version__ = "0.0.2"
"""
exec(_code_byslib, byslib.__dict__)

_code_byslib_core = """

"""
exec(_code_byslib_core, byslib.core.__dict__)

_code_byslib_core_config = """
import sys
from typing import Callable


def procon_setup(main: Callable[..., None]) -> Callable[..., None]:
    sys.setrecursionlimit(10**7)

    def wrapper(case: int = 1) -> None:
        for i in range(case):
            main(case=i + 1)

    return wrapper
"""
exec(_code_byslib_core_config, byslib.core.config.__dict__)

procon_setup = byslib.core.config.procon_setup
# from byslib.core.fastio import int1, readline, sinput
byslib.core.fastio = ModuleType("byslib.core.fastio")

_code_byslib_core_fastio = """
import io
import os
import sys
from functools import partial
from typing import Union

readline = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline
debug = partial(print, file=sys.stderr)


def sinput() -> str:
    return readline().decode().rstrip()


def int1(s: Union[str, bytes]) -> int:
    return int(s) - 1
"""
exec(_code_byslib_core_fastio, byslib.core.fastio.__dict__)

int1 = byslib.core.fastio.int1
readline = byslib.core.fastio.readline
sinput = byslib.core.fastio.sinput
# from byslib.data.segment_tree import SegmentTree
byslib.data = ModuleType("byslib.data")
byslib.data.segment_tree = ModuleType("byslib.data.segment_tree")

_code_byslib_data = """
# data-structure
"""
exec(_code_byslib_data, byslib.data.__dict__)

_code_byslib_data_segment_tree = """
# @title Segment Tree
from typing import Callable, Generic, List, TypeVar

T = TypeVar("T")


class SegmentTree(Generic[T]):
    r\"""Segment Tree

    Parameters
    ----------
    Generic[T]
        Set type of Monoid

    Notes
    -----
    Time complexity

    * build : :math:`O(N)`
    * Point set : :math:`O(\\log(N))`
    * Range fold : :math:`O(\\log(N))`

    References
    ----------
    ..[1] 🐜 p.153
    ..[2] https://scrapbox.io/data-structures/Segment_Tree
    ..[3] https://ikatakos.com/pot/programming_algorithm/data_structure/segment_tree

    Examples
    --------
    >>> seg = SegmentTree(max, 0, [1] * 10)
    >>> seg.set(3, 4)
    >>> seg.set(8, 9)
    >>> print(seg.fold(0,5))
    4
    >>> len(seg)
    10
    >>> print(seg.fold_all())
    9
    >>> print(seg[3])
    4
    \"""

    def __init__(
        self, operation: Callable[[T, T], T], identity: T, array: List[T]
    ) -> None:
        \"""build

        Parameters
        ----------
        operation
            Binary operation of Monoid
        identity
            Identity of Monoid
        array
            Init array
        \"""
        self.__operation = operation
        self.__identity = identity
        self.__n = len(array)
        self.__n_leaf = 1 << (self.__n - 1).bit_length()
        self.__data = [self.__identity] * (self.__n_leaf * 2)
        self.__data[self.__n_leaf : self.__n_leaf + self.__n] = array
        for i in range(self.__n_leaf - 1, 0, -1):
            self.__data[i] = self.__operation(
                self.__data[i * 2], self.__data[i * 2 + 1]
            )

    def set(self, index: int, value: T) -> None:
        index += self.__n_leaf
        self.__data[index] = value
        index >>= 1
        while index > 0:
            self.__data[index] = self.__operation(
                self.__data[index * 2], self.__data[index * 2 + 1]
            )
            index >>= 1

    def fold(self, left: int, right: int) -> T:
        left_fold = self.__identity
        right_fold = self.__identity
        left += self.__n_leaf
        right += self.__n_leaf
        while left < right:
            if left & 1:
                left_fold = self.__operation(left_fold, self.__data[left])
                left += 1
            if right & 1:
                right -= 1
                right_fold = self.__operation(self.__data[right], right_fold)
            left >>= 1
            right >>= 1
        return self.__operation(left_fold, right_fold)

    def fold_all(self) -> T:
        return self.__data[1]

    def __getitem__(self, key: int) -> T:
        return self.__data[key + self.__n_leaf]

    def __len__(self) -> int:
        return self.__n

    @classmethod
    def zeros(cls, op: Callable[[T, T], T], ident: T, n: int) -> "SegmentTree":
        return cls(op, ident, [ident] * n)
"""
exec(_code_byslib_data_segment_tree, byslib.data.segment_tree.__dict__)

SegmentTree = byslib.data.segment_tree.SegmentTree


@procon_setup
def main(**kwargs) -> None:
    _ = int(readline())
    a = ord("a")
    s = [1 << (ord(si) - a) for si in sinput()]
    seg = SegmentTree(lambda a, b: a | b, 0, s)
    q = int(readline())
    for _ in range(q):
        type, *body = sinput().split()
        if type == "1":
            _i, _c = body
            i = int1(_i)
            c = ord(_c) - a
            seg.set(i, 1 << c)
        else:
            l, r = map(int, body)
            print(bin(seg.fold(l - 1, r)).count("1"))


if __name__ == "__main__":
    t = 1
    # t = int(readline())
    main(t)


# package infomations
# --------------------------------------------------------------------------
# byslib-python
#   Version  : 0.0.2
#   Author   : bayashi-cl
#   Home-page: https://bayashi-cl.github.io/byslib-python/
#   License  : CC0
# --------------------------------------------------------------------------
