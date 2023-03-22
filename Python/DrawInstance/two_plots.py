import matplotlib.pyplot as plt

# First series of points
x1 = [0, 4, 3, 0]
y1 = [3, 4, 1, 0]

# Second series of points
x2 = [0, 1, 2, 4, 0, 1, 3, 3]
y2 = [3, 1, 2, 4, 0, 2, 1, 3, ]

# Plotting the first scatter plot
plt.scatter(x1, y1, color='red')

# Plotting the second scatter plot and connecting the dots
plt.plot(x2, y2, color='blue')

# Adding title and labels
plt.title('Scatter Plots')
plt.xlabel('X-axis')
plt.ylabel('Y-axis')

# Displaying the plot
plt.show()
