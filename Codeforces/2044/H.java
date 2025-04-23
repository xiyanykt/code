import java.util.*;

public class H extends U {
	long ask(long[][] M, int x1, int y1, int x2, int y2) {
		return M[x2][y2] - M[x2][y1 - 1] - M[x1 - 1][y2] + M[x1 - 1][y1 - 1];
	}

	void solve() {
		int n = sc.nextInt();
		int q = sc.nextInt();

		int[][] a = new int[n + 1][n + 1];
		for (int i = 1; i <= n; i += 1) {
			for (int j = 1; j <= n; j += 1) {
				a[i][j] = sc.nextInt();
			}
		}

		long[][] s1 = new long[n + 1][n + 1];
		long[][] s2 = new long[n + 1][n + 1];
		long[][] s3 = new long[n + 1][n + 1];
		for (int i = 1; i <= n; i += 1) {
			for (int j = 1; j <= n; j += 1) {
				s1[i][j] += s1[i - 1][j] + s1[i][j - 1] - s1[i - 1][j - 1] + a[i][j];
				s2[i][j] += s2[i - 1][j] + s2[i][j - 1] - s2[i - 1][j - 1] + a[i][j] * i;
				s3[i][j] += s3[i - 1][j] + s3[i][j - 1] - s3[i - 1][j - 1] + a[i][j] * j;
			}
		}

		while (q-- > 0) {
			int x1 = sc.nextInt();
			int y1 = sc.nextInt();
			int x2 = sc.nextInt();
			int y2 = sc.nextInt();

			int len = y2 - y1 + 1;
			long res = 0;
			res -= ask(s1, x1, y1, x2, y2) * len * x1;
			res += ask(s2, x1, y1, x2, y2) * len;
			res += ask(s3, x1, y1, x2, y2) - ask(s1, x1, y1, x2, y2) * (y1 - 1);
			out.print(res);
			out.print(' ');
		}
		out.writeln();
	}

	public static void main(String[] args) {
		H xoxo = new H();
		int t = xoxo.sc.nextInt();

		while (t-- > 0) {
			xoxo.solve();
		}
		xoxo.out.flush();
	}
}

class U {
	FastReader sc = new FastReader();
	FastWriter out = new FastWriter();

	class FastReader {
		private java.io.InputStream is = System.in;
		private byte[] inbuf = new byte[1024];
		private char[] str = new char[16];
		private int lenbuf, ptrbuf, b;

		int readByte() {
			if (ptrbuf == lenbuf) {
				ptrbuf = 0;
				try {
					lenbuf = is.read(inbuf);
				} catch (Exception e) {
				}
				if (lenbuf <= 0) return -1;
			}
			return inbuf[ptrbuf++];
		}

		String next() {
			while ((b = readByte()) < 33) ;
			int i = 0;
			while (b > 32) {
				if (i == str.length) str = Arrays.copyOf(str, str.length << 1);
				str[i++] = (char) b;
				b = readByte();
			}
			return new String(str, 0, i);
		}

		int nextInt() {
			return (int) nextLong();
		}

		long nextLong() {
			while ((b = readByte()) < 33) ;
			boolean minus = b == '-';
			long num = minus ? 0 : b - '0';
			while ((b = readByte()) > 32) num = num * 10 + (b - '0');
			return minus ? -num : num;
		}

		double nextDouble() {
			return Double.parseDouble(next());
		}
	}

	class FastWriter {
		private java.io.OutputStream out = System.out;
		private int tr = 0, BUF_SIZE = 8192;
		private byte[] buf = new byte[BUF_SIZE];

		private int countDigits(int v) {
			return v >= 100000 ? v >= 10000000 ? v >= 100000000 ? v >= 1000000000 ? 10 : 9 : 8 : v >= 1000000 ? 7 : 6 : v >= 1000 ? v >= 10000 ? 5 : 4 : v >= 100 ? 3 : v >= 10 ? 2 : 1;
		}

		private int countDigits(long v) {
			return v >= 10000000000L ? 10 + countDigits((int) (v / 10000000000L)) : v >= 1000000000 ? 10 : countDigits((int) v);
		}

		private FastWriter write(byte b) {
			buf[tr++] = b;
			if (tr == BUF_SIZE) innerflush();
			return this;
		}

		private FastWriter write(char c) {
			return write((byte) c);
		}

		private FastWriter write(int x) {
			if (x == Integer.MIN_VALUE) {
				return write((long) x);
			}
			if (tr + 12 >= BUF_SIZE) innerflush();
			if (x < 0) {
				write((byte) '-');
				x = -x;
			}
			int d = countDigits(x);
			for (int i = tr + d - 1; i >= tr; i--) {
				buf[i] = (byte) ('0' + x % 10);
				x /= 10;
			}
			tr += d;
			return this;
		}

		private FastWriter write(long x) {
			if (x == Long.MIN_VALUE) {
				return write("" + x);
			}
			if (tr + 21 >= BUF_SIZE) innerflush();
			if (x < 0) {
				write((byte) '-');
				x = -x;
			}
			int d = countDigits(x);
			for (int i = tr + d - 1; i >= tr; i--) {
				buf[i] = (byte) ('0' + x % 10);
				x /= 10;
			}
			tr += d;
			return this;
		}

		private FastWriter write(double x, int precision) {
			if (x < 0) {
				write('-');
				x = -x;
			}
			x += Math.pow(10, -precision) / 2;
			write((long) x).write(".");
			x -= (long) x;
			for (int i = 0; i < precision; i++) {
				x *= 10;
				write((char) ('0' + (int) x));
				x -= (int) x;
			}
			return this;
		}

		private FastWriter write(String s) {
			for (int i = 0; i < s.length(); i++) {
				buf[tr++] = (byte) s.charAt(i);
				if (tr == BUF_SIZE) innerflush();
			}
			return this;
		}

		void print(char c) {
			write(c);
		}

		void print(String s) {
			write(s);
		}

		void print(int x) {
			write(x);
		}

		void print(long x) {
			write(x);
		}

		void print(double x, int precision) {
			write(x, precision);
		}

		void writeln() {
			write((byte) '\n');
		}

		void println(char c) {
			write(c).writeln();
		}

		void println(int x) {
			write(x).writeln();
		}

		void println(long x) {
			write(x).writeln();
		}

		void println(double x, int precision) {
			write(x, precision).writeln();
		}

		void println(String s) {
			write(s).writeln();
		}

		void println(Object o) {
			deepPrint(o, true);
		}

		private void deepPrint(Object o, boolean f) {
			if (o == null) {
				write(f ? "null\n" : "null");
				return;
			}
			Class<?> c = o.getClass();
			if (c.isArray()) {
				if (o instanceof Object[]) {
					Object[] t = (Object[]) o;
					int n = t.length;
					boolean b = f && n > 0 && t[0] != null && (t[0].getClass().isArray() || t[0] instanceof Collection || t[0] instanceof Map);
					write(b ? "[\n" : "[");
					for (int i = 0; i < n; i++) {
						deepPrint(t[i], false);
						if (i < n - 1) write(b ? ", \n" : ", ");
						else if (b) writeln();
					}
					write("]");
				} else {
					write(o instanceof byte[] ? Arrays.toString((byte[]) o) : o instanceof short[] ? Arrays.toString((short[]) o) : o instanceof int[] ? Arrays.toString((int[]) o) : o instanceof long[] ? Arrays.toString((long[]) o) : o instanceof char[] ? Arrays.toString((char[]) o) : o instanceof float[] ? Arrays.toString((float[]) o) : o instanceof double[] ? Arrays.toString((double[]) o) : Arrays.toString((boolean[]) o));
				}
			} else if (o instanceof Collection) {
				Collection<?> t = (Collection<?>) o;
				write("[");
				int i = 0;
				for (Object v : t) {
					deepPrint(v, false);
					if (i < t.size() - 1) write(", ");
					i++;
				}
				write("]");
			} else if (o instanceof Map) {
				Map<?, ?> t = (Map<?, ?>) o;
				write(!t.isEmpty() && f ? "{\n" : "{");
				int i = 0;
				for (Map.Entry<?, ?> v : t.entrySet()) {
					deepPrint(v.getKey(), false);
					write(" = ");
					deepPrint(v.getValue(), false);
					if (++i < t.size()) write(f ? ", \n" : ", ");
					else if (f) writeln();
				}
				write("}");
			} else {
				write(o.toString());
			}
			if (f) writeln();
		}

		private void innerflush() {
			try {
				out.write(buf, 0, tr);
				tr = 0;
			} catch (Exception e) {
			}
		}

		void flush() {
			innerflush();
			try {
				out.flush();
			} catch (Exception e) {
			}
		}
	}

	int min(int a, int b) {
		return a > b ? b : a;
	}

	int min(int... args) {
		int ans = Integer.MAX_VALUE;
		for (int v : args) if (ans > v) ans = v;
		return ans;
	}

	long min(long a, long b) {
		return a > b ? b : a;
	}

	long min(long... args) {
		long ans = Long.MAX_VALUE;
		for (long v : args) if (ans > v) ans = v;
		return ans;
	}

	double min(double a, double b) {
		return a > b ? b : a;
	}

	double min(double... args) {
		double ans = Double.MAX_VALUE;
		for (double v : args) if (ans > v) ans = v;
		return ans;
	}

	int max(int a, int b) {
		return a < b ? b : a;
	}

	int max(int... args) {
		int ans = Integer.MIN_VALUE;
		for (int v : args) if (ans < v) ans = v;
		return ans;
	}

	long max(long a, long b) {
		return a < b ? b : a;
	}

	long max(long... args) {
		long ans = Long.MIN_VALUE;
		for (long v : args) if (ans < v) ans = v;
		return ans;
	}

	double max(double a, double b) {
		return a < b ? b : a;
	}

	double max(double... args) {
		double ans = Double.MIN_VALUE;
		for (double v : args) if (ans < v) ans = v;
		return ans;
	}

	int abs(int a) {
		return a < 0 ? -a : a;
	}

	long abs(long a) {
		return a < 0 ? -a : a;
	}

	double abs(double a) {
		return a < 0 ? -a : a;
	}
}