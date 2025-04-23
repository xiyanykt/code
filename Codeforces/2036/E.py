from collections import defaultdict

inf = int(1e9)
Kn = int(1e5) + 1


class Node:
    def __init__(self):
        self.lsh = None
        self.rsh = None
        self.s = [0] * Kn


def add(t, l, r, x, v):
    if t is None:
        t = Node()
    t.s[v] = 1
    if l == r:
        return t
    mid = (l + r) // 2
    if x <= mid:
        t.lsh = add(t.lsh, l, mid, x, v)
    else:
        t.rsh = add(t.rsh, mid + 1, r, x, v)
    return t


def query(t, l, r, L, R):
    if t is None or l > R or r < L:
        return [0] * Kn
    if L <= l and r <= R:
        return t.s
    mid = (l + r) // 2
    left_query = query(t.lsh, l, mid, L, R)
    right_query = query(t.rsh, mid + 1, r, L, R)
    return [left | right for left, right in zip(left_query, right_query)]


def chmax(x, y):
    return max(x, y)


def chmin(x, y):
    return min(x, y)


def main():
    n, k, q = map(int, input().split())

    # Initialize a with correct dimensions
    a = [[0] * (k + 1) for _ in range(n + 1)]

    # Read input for a
    for i in range(1, n + 1):
        a[i] = list(map(int, input().split()))

    # Initialize b with the same dimensions as a
    b = [[0] * (k + 1) for _ in range(n + 1)]

    # Fill in b with the cumulative values
    for i in range(1, n + 1):
        for j in range(1, k + 1):
            b[i][j] = a[i][j]
            if i > 1:
                b[i][j] |= b[i - 1][j]

    t = [None] * (k + 1)
    for i in range(1, n + 1):
        for j in range(1, k + 1):
            t[j] = add(t[j], 1, inf, b[i][j], i)

    for _ in range(q):
        m = int(input())
        rec = defaultdict(lambda: [0, inf])

        for _ in range(m):
            r, o, c = input().split()
            r = int(r)
            c = int(c)
            if o == ">":
                rec[r][0] = chmax(rec[r][0], c)
            else:
                rec[r][1] = chmin(rec[r][1], c)

        res = [1] * Kn
        for x, v in rec.items():
            lo, hi = v
            u = query(t[x], 1, inf, lo + 1, hi - 1)
            res = [r & u_val for r, u_val in zip(res, u)]

        if not any(res):
            print(-1)
        else:
            print(res.index(1))


if __name__ == "__main__":
    main()
