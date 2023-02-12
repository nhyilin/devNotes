import pandas as pd
import csv
import numpy as np
import matplotlib.pyplot as plt
from sklearn.cluster import KMeans
from datetime import datetime, timedelta
import matplotlib.dates as mdates
import os
import julian
from collections import Counter
from astropy.time import Time
from sklearn.mixture import GaussianMixture

data = pd.read_csv('./data/Clustering_gmm.csv')


# plt.figure(figsize=(7, 7))
# plt.scatter(data["Weight"], data["Height"])
# plt.xlabel('Weight')
# plt.ylabel('Height')
# plt.title('Data Distribution')
# plt.show()
#
# # training k-means model
# from sklearn.cluster import KMeans
#
# kmeans = KMeans(n_clusters=4)
# kmeans.fit(data)
#
# # predictions from kmeans
# pred = kmeans.predict(data)
# frame = pd.DataFrame(data)
# frame['cluster'] = pred
# frame.columns = ['Weight', 'Height', 'cluster']
#
# # plotting results
# color = ['blue', 'green', 'cyan', 'black']
# for k in range(0, 4):
#     data = frame[frame["cluster"] == k]
#     plt.scatter(data["Weight"], data["Height"], c=color[k])
# plt.show()

# training gaussian mixture model

def alg_GaussianMixture(data):
    gmm = GaussianMixture(n_components=4)
    gmm.fit(data)

    # predictions from gmm
    labels = gmm.predict(data)
    frame = pd.DataFrame(data)
    frame['cluster'] = labels
    frame.columns = ['Weight', 'Height', 'cluster']

    color = ['blue', 'green', 'cyan', 'black']
    for k in range(0, 4):
        data = frame[frame["cluster"] == k]
        plt.scatter(data["Weight"], data["Height"], c=color[k])
    plt.show()


def main():
    alg_GaussianMixture(data)


if __name__ == "__main__":
    main()
