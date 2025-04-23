std::istream &operator>>(std::istream &is, i128 &n) {
	std::string s;
	is >> s;
	n = 0;
	for (int i = (s[0] == '-'); i < s.size(); i += 1) {
		n = n * 10 + s[i] - '0';
	}
	if (s[0] == '-') {
		n *= -1;
	}
	return is;
}

std::ostream &operator<<(std::ostream &os, i128 n) {
	std::string s;
	if (n == 0) {
		return os << 0;
	}
	bool sign = false;
	if (n < 0) {
		sign = true;
		n = -n;
	}
	while (n > 0) {
		s += '0' + n % 10;
		n /= 10;
	}
	if (sign) {
		s += '-';
	}
	std::reverse(s.begin(), s.end());
	return os << s;
}