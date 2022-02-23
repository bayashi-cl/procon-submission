import sys

if sys.argv[-1] == "ONLINE_JUDGE":
    from setuptools import setup
    from Cython.Build import cythonize

    code = """\
DEF MOD7 = 1000000007

cdef class modint:
    @staticmethod
    cdef int mod() nogil:
        return MOD7

    @staticmethod
    cdef modint raw(unsigned int v):
        cdef modint ret = modint.__new__(modint)
        ret.__v = v
        return ret


    def __init__(modint self, long long v):
        cdef long long x = v % MOD7
        if x < 0:
            x += MOD7
        self.__v = x


    cpdef unsigned int val(modint self):
        return self.__v


    def __pos__(modint self):
        return self

    def __neg__(modint self):
        cdef modint ret = modint.__new__(modint)
        if self.__v != 0:
            ret.__v = MOD7 - self.__v
        return ret


    cpdef modint pow(modint self, long long n):
        cdef modint ret = modint.__new__(modint)
        ret.__v = modint.__internal_pow(self.__v, n)
        return ret

    cpdef modint inv(modint self):
        cdef modint ret = modint.__new__(modint)
        ret.__v = self.__internal_inv()
        return ret

    def __add__(modint x, modint y):
        cdef modint ret = modint.__new__(modint)
        ret.__v = x.__v + y.__v
        if ret.__v >= MOD7:
            ret.__v -= MOD7
        return ret

    def __sub__(modint x, modint y):
        cdef modint ret = modint.__new__(modint)
        ret.__v = x.__v - y.__v
        if ret.__v >= MOD7:
            ret.__v += MOD7
        return ret

    def __mul__(modint x, modint y):
        cdef modint ret = modint.__new__(modint)
        ret.__v = <unsigned long long> x.__v * y.__v % MOD7
        return ret

    def __truediv__(modint x, modint y):
        cdef modint ret = modint.__new__(modint)
        ret.__v = <unsigned long long> x.__v * y.__internal_inv() % MOD7
        return ret

    def __pow__(modint self, long long n, object):
        cdef modint ret = modint.__new__(modint)
        ret.__v = modint.__internal_pow(self.__v, n)
        return ret

    def __eq__(modint self, modint y):
        return self.__v == y.__v

    def __ne__(modint self, modint y):
        return self.__v != y.__v


    cdef unsigned int __v

    @staticmethod
    cdef unsigned int __internal_pow(unsigned int x, unsigned long long n) nogil:
        cdef unsigned int r = 1
        while n:
            if n & 1:
                r = <unsigned long long> r * x % MOD7
            x = <unsigned long long> x * x % MOD7
            n >>= 1
        return r

    cdef unsigned int __internal_inv(modint self) nogil:
        return modint.__internal_pow(self.__v, MOD7 - 2)

"""
    with open("modint.pyx", "w") as f:
        f.write(code)

    sys.argv.pop()
    sys.argv.append("build_ext")
    sys.argv.append("--inplace")

    setup(ext_modules=cythonize("*.pyx"))
    sys.exit(0)

MOD7 = 1000000007

from modint import modint


def main() -> None:
    l = input()
    n = len(l)
    dp = [[modint(0) for _ in range(n + 1)] for _ in range(2)]
    dp[0][0] = modint(1)
    for i, li in enumerate(l):
        if li == "0":
            dp[0][i + 1] += dp[0][i]
            dp[1][i + 1] += dp[1][i] * modint(3)
        else:
            dp[0][i + 1] += dp[0][i] * modint(2)
            dp[1][i + 1] += dp[0][i]
            dp[1][i + 1] += dp[1][i] * modint(3)

    print((dp[0][n] + dp[1][n]).val())


if __name__ == "__main__":
    sys.setrecursionlimit(10**6)
    main()
