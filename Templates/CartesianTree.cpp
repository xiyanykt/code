template <class T>
struct CartesianTree {
    std::vector<int>lsh, rsh, stk;

    CartesianTree(const std::vector<T>& w) {
        int n = w.size() - 1;
        lsh.assign(n + 1, 0);
        rsh.assign(n + 1, 0);
        stk.assign(n + 1, 0);
        int top = 0;
        for (int i = 1; i <= n; i += 1) {
            int k = top;
            while (k > 0 and w[i] <= w[stk[k]]) {
                k -= 1;
            }
            if (k > 0) {
                rsh[stk[k]] = i;
            }
            if (k < top) {
                lsh[i] = stk[k + 1];
            }
            stk[top = (k += 1)] = i;
        }
    }
};