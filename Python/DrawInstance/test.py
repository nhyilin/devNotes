import matplotlib.pyplot as plt

all_points = []
with open('data/all_points.txt', 'r') as f:
    for line in f:
        x1, y1 = line.strip()[1:-1].split(',')
        all_points.append((float(x1), float(y1)))
x1, y1 = zip(*all_points)
plt.scatter(x1, y1, color='blue', label='All Points')

result = []
with open('data/result_file.txt', 'r') as f:
    for line in f:
        x2, y2 = line.strip()[1:-1].split(',')
        result.append((float(x2), float(y2)))

x2, y2 = zip(*result)
plt.scatter(x2, y2, color='red', label='Bounding Box')
plt.legend()
plt.show()
