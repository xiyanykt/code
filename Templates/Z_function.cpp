std::vector<int> ZFunc(const std::string& s) {
    int n = s.size();
    std::vector<int>z(n);
    z[0] = n;
    for (int i = 1, j = 1; i < n; i += 1) {
        z[i] = std::max(0, std::min(j + z[j] - i, z[i - j]));
        while (i + z[i] < n and s[z[i]] == s[i + z[i]]) {
            z[i] += 1;
        }
        if (i + z[i] > j + z[j]) {
            j = i;
        }
    }
    return z;
}