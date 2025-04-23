import math

class Fenwick:
    def __init__(self, n):
        self.n = n
        self.a = [0] * (n + 1)

    def add(self, p, x):
        if 1 <= p <= self.n:
            i = p
            while i <= self.n:
                self.a[i] += x
                i += i & -i

    def sum(self, p):
        ans = 0
        if 1 <= p <= self.n:
            i = p
            while i > 0:
                ans += self.a[i]
                i -= i & -i
        return ans

    def range_query(self, l, r):
        return self.sum(r) - self.sum(l - 1)

    def select(self, k):
        x = 0
        cur = 0
        for i in range(math.floor(math.log2(self.n)), -1, -1):
            x += 1 << i
            if x >= self.n or cur + self.a[x] >= k:
                x -= 1 << i
            else:
                cur += self.a[x]
        return x + 1

def main():
    n, k = map(int, input().split())
    x = [None] * (n + 1)

    for i in range(1, n + 1):
        p, v = map(int, input().split())
        x[i] = (p, v)
   
    def work(t):
        c = 0
        d = []

        for i in range(1, n + 1):
            p, v = x[i]
            d.append((p + t * v, i * v))

        d.sort()
        f = 0
        fen = Fenwick(n + 1)
        
        for p, i in d:
            if i >= 1:
                c += fen.range_query(i + 1, n + 1)
            else:
                fen.add(-i, 1)

        return c >= k

    lo, hi = 0, 1e9
    for _ in range(55):
        mid = (lo + hi) / 2
        if work(mid):
            hi = mid
        else:
            lo = mid

    if work(hi):
        print("Yes")
        print(f"{hi:.9f}")
    else:
        print("No")

if __name__ == "__main__":
    main()
