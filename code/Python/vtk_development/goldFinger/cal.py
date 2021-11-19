import numpy as np
a = 0.45923592
b = 0.76031396

degree = a/b
inv = np.arctan(degree)
print ("inv = ", np.degrees(inv))
