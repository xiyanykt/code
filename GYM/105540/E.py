import sys

input = lambda: sys.stdin.readline().strip()
outs = []


def solve():
    A, B, C, X, Y, D = map(int, input().split())
    res = (D + X - 1) // X * A

    def AB():
        div = D // (X + Y)
        res = div * (A + B * Y)
        mod = D - div * (X + Y)
        if mod < X:
            if mod > 0:
                res += A
                res -= min(X - mod, div * Y) * B
        else:
            res += A + (mod - X) * B
        return res

    def ABC():
        if D <= X + Y:
            return AB()
        res = A + B * Y
        res += (D - X - Y) * C
        return res

    def ABABC():
        if D <= X + Y:
            return AB()
        div = D // (X + Y)
        res = div * (A + B * Y) + (D - div * (X + Y)) * C
        return res

    def A_B():
        div = D // X
        res = A * div
        lef = D - div * X
        if lef > 0:
            res += A
        if div * Y >= lef:
            res = min(res, A * div + lef * B)
        else:
            res = min(res, A * div + div * B * Y + (lef - div * Y) * C)
        return res

    def A_BC():
        div = D // X
        res = A * div
        lef = D - div * X
        if lef > 0:
            res += A
            if lef <= Y:
                res = min(res, A * div + lef * B)
            else:
                res = min(res, A * div + Y * B + (lef - Y) * C)
        return res

    def AB_C():
        if D <= X + Y:
            return AB()
        div = D // (X + Y)
        res = (A + B * Y) * div
        res += (D - div * (X + Y)) * C
        return res

    if D > X:
        res = min(res, AB(), ABC(), ABABC(), A_B(), A_BC(), AB_C())
    outs.append(res)


t = int(input())
while t > 0:
    solve()
    t -= 1
print("\n".join(map(str, outs)))
