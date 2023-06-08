# Description: This script converts kepler elements to j2000 inertial coordinates

import math


# Define a function to convert kepler elements to j2000
def kepler_to_j2000(a, e, i, Ω, w, M):
    # Step 1: Calculate satellite position in orbital frame (r_x, r_y, r_z)
    # Solve Kepler's equation for eccentric anomaly E using Newton's method
    E = M  # Initial guess
    tol = 1e-6  # Tolerance for convergence
    max_iter = 100  # Maximum number of iterations
    iter = 0  # Iteration counter
    while True:
        f = E - e * math.sin(E) - M  # Function value
        fp = 1 - e * math.cos(E)  # Function derivative
        E = E - f / fp  # Update E using Newton's method
        iter += 1  # Increment iteration counter
        if abs(f) < tol or iter > max_iter:  # Check convergence or termination criteria
            break
    # Calculate satellite position in orbital frame (r_x, r_y, r_z)
    r_x = a * (math.cos(E) - e)
    r_y = a * math.sqrt(1 - e ** 2) * math.sin(E)
    r_z = 0

    # Step 2: Convert satellite position to j2000 inertial frame (X, Y, Z)
    # Use Euler angles to rotate from orbital frame to j2000 inertial frame
    # The rotation sequence is z-x-z with angles w, i, Ω respectively
    X = (math.cos(w) * math.cos(Ω) - math.sin(w) * math.cos(i) * math.sin(Ω)) * r_x - (
            math.sin(w) * math.cos(Ω) + math.cos(w) * math.cos(i) * math.sin(Ω)) * r_y
    Y = (math.cos(w) * math.sin(Ω) + math.sin(w) * math.cos(i) * math.cos(Ω)) * r_x + (
            math.cos(w) * math.cos(i) * math.cos(Ω) - math.sin(w) * math.sin(Ω)) * r_y
    Z = (math.sin(w) * math.sin(i)) * r_x + (math.cos(w) * math.sin(i)) * r_y

    return X, Y, Z


# Test the function with an example satellite
# Sat20000109
a = 8371  # Semi-major axis in km
e = 0.000  # Eccentricity
i = math.radians(87)  # Inclination in rad
Ω = math.radians(0)  # Right ascension of ascending node in rad
w = math.radians(0)  # Argument of perigee in rad
M = math.radians(28.8)  # Mean anomaly in rad

X, Y, Z = kepler_to_j2000(a, e, i, Ω, w, M)
print('X =', X, 'km')
print('Y =', Y, 'km')
print('Z =', Z, 'km')
print('R =', math.sqrt(X ** 2 + Y ** 2 + Z ** 2), 'km')
