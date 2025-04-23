struct RevocableDSU {
    std::vector<int>par, siz;
    std::vector<std::pair<int, int>>stk;

    RevocableDSU() = default;
    RevocableDSU(int n) {
        par.resize(n + 1);
        siz.assign(n + 1, 1);
        std::iota(par.begin(), par.end(), 0);
        stk.clear();
    } 

    int find(int x) {
        while (x != par[x]) {
            x = par[x];
        }
        return x;
    }

    bool same(int x, int y) {
        return find(x) == find(y);
    }

    bool merge(int x, int y) {
        x = find(x), y = find(y);
        if (x == y) {
            return false;
        }
        if (siz[x] < siz[y]) {
            std::swap(x, y);
        }
        siz[x] += siz[y];
        par[y] = x;
        stk.emplace_back(x, y);
        return true;
    }

    int size(int x) {
        return siz[find(x)];
    }

    int version() {
        return stk.size();
    }

    void rollback(int v) {
        while (stk.size() > v) {
            auto [x, y] = stk.back();
            stk.pop_back();
            siz[x] -= siz[y];
            par[y] = y;
        }
    }
};