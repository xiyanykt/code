import numpy as np
from matplotlib import pyplot

N = 100
n = np.arange(1, N + 1)
z = np.exp(1j * n)
partial_sums = np.cumsum(z)

pyplot.figure(figsize=(8, 8))
pyplot.plot(partial_sums.real, partial_sums.imag, marker='o', linestyle='-', color='blue', label='Partial sums path')
pyplot.scatter(partial_sums.real[-1], partial_sums.imag[-1], color='red', label='Last point')
pyplot.title(r"Partial sums of $\sum e^{in}$ in the complex plane")
pyplot.xlabel("Real part")
pyplot.ylabel("Imaginary part")
pyplot.axhline(0, color='gray', linewidth=0.5)
pyplot.axvline(0, color='gray', linewidth=0.5)
pyplot.legend()
pyplot.grid(True)
pyplot.axis("equal")
pyplot.show()
