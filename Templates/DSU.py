class DSU:
    def __init__(self, n):
        self.par = [x for x in range(0, n + 1)]
        self.siz = [1] * (n + 1)

    def find(self, x):
        while x != self.par[x]:
            x = self.par[x] = self.par[self.par[x]]
        return x

    def same(self, x, y):
        return self.find(x) == self.find(y)

    def merge(self, x, y):
        x, y = self.find(x), self.find(y)
        if x == y:
            return False
        if self.siz[x] < self.siz[y]:
            x, y = y, x
        self.par[y] = x
        self.siz[x] += self.siz[y]
        return True

    def size(self, x):
        return self.siz[self.find(x)]
