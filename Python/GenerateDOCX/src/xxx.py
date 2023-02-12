import numpy as np
import matplotlib.pyplot as plt
from sklearn.cluster import KMeans

# Generate sample data
np.random.seed(0)
data = np.concatenate([np.random.normal(0, 1, (100, 2)),
                      np.random.normal(5, 1, (100, 2))])

# Fit k-means clustering model
kmeans = KMeans(n_clusters=2)
kmeans.fit(data)

# Plot the data and the k-means clustering model
x = np.linspace(-5, 10, 500)
y = np.linspace(-5, 10, 500)
X, Y = np.meshgrid(x, y)
Z = kmeans.predict(np.c_[X.ravel(), Y.ravel()])
Z = Z.reshape(X.shape)

plt.pcolormesh(X, Y, Z, cmap='viridis')
plt.scatter(data[:, 0], data[:, 1], s=5, color='r')
plt.show()
