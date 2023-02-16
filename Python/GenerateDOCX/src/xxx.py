import matplotlib.pyplot as plt
import numpy as np

x = np.arange(10)
y = x ** 2

fig, ax = plt.subplots()
ax.plot(x, y)
ax.axhline(y=50, color='red', linestyle='--')

plt.show()
