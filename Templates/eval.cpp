int eval(const std::string & s) {
    int n = s.size();
    std::vector<int>stk;
    std::vector<char>sig;

    auto f = [&](const char & c) {
        assert(not stk.empty());
        int r = stk.back();
        stk.pop_back();
        assert(not stk.empty());
        int l = stk.back();
        stk.pop_back();
        if (c == '*') {
            stk.emplace_back(l * r);
        } else if (c == '/') {
            stk.emplace_back(l / r);
        } else if (c == '+') {
            stk.emplace_back(l + r);
        } else if (c == '-') {
            stk.emplace_back(l - r);
        } else assert(false);
    };

    auto r = [&](const char & c) {
        if (c == '-' or c == '+') {
            return 1;
        } else if (c == '*' or c == '/') {
            return 2;
        }
        return -1;
    };

    for (int i = 0; i < n; i += 1) {
        char c = s[i];
        if (c == ' ') {
            continue;
        }
        if (c == '(') {
            sig.emplace_back(c);
        } else if (c == ')') {
            while (not sig.empty() and sig.back() != '(') {
                f(sig.back());
                sig.pop_back();
            }
            sig.pop_back();
        } else if (c == '+' or c == '-' or c == '*' or c == '/') {
            while (not sig.empty() and r(sig.back()) >= r(c)) {
                f(sig.back());
                sig.pop_back();
            }
            sig.push_back(c);
        } else {
            int x = 0;
            while (i < n and std::isdigit(s[i])) {
                x = x * 10 + s[i] - '0';
                i += 1;
            }
            i -= 1;
            stk.emplace_back(x);
        }
    }
    while (not sig.empty()) {
        f(sig.back());
        sig.pop_back();
    }
    return stk.back();
}
