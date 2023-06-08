import math

# Define some constants
R = 6378  # Earth radius in km
ω = 7.2921159e-5  # Earth rotation rate in rad/s
t = 0  # Observation time in s
GST = 0  # Greenwich sidereal time in rad


# Define a function to convert kepler elements to blh
def kepler_to_blh(a, e, i, Ω, w, M):
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

    # Step 2: Convert satellite position to inertial frame (X, Y, Z)
    # Use Euler angles to rotate from orbital frame to inertial frame
    # The rotation sequence is z-x-z with angles w, i, Ω respectively
    X = (math.cos(w) * math.cos(Ω) - math.sin(w) * math.cos(i) * math.sin(Ω)) * r_x - (
            math.sin(w) * math.cos(Ω) + math.cos(w) * math.cos(i) * math.sin(Ω)) * r_y
    Y = (math.cos(w) * math.sin(Ω) + math.sin(w) * math.cos(i) * math.cos(Ω)) * r_x + (
            math.cos(w) * math.cos(i) * math.cos(Ω) - math.sin(w) * math.sin(Ω)) * r_y
    Z = (math.sin(w) * math.sin(i)) * r_x + (math.cos(w) * math.sin(i)) * r_y

    # Step 3: Convert satellite position to fixed frame (x, y, z)
    # Use Earth rotation angle to rotate from inertial frame to fixed frame
    # The rotation is about z axis with angle ω t
    θ = ω * t  # Earth rotation angle in rad
    x = math.cos(θ) * X + math.sin(θ) * Y
    y = -math.sin(θ) * X + math.cos(θ) * Y
    z = Z

    # Step 4: Convert satellite position to blh (B, L, H)
    # Use trigonometric functions or inverse trigonometric functions to convert from fixed frame to blh
    B = math.atan2(z, math.sqrt(x ** 2 + y ** 2))  # Latitude in rad
    L = math.atan2(y, x) - GST  # Longitude in rad
    H = math.sqrt(x ** 2 + y ** 2 + z ** 2) - R  # Height in km

    return B, L, H


# Test the function with an example satellite
a = 26560  # Semi-major axis in km
e = 0.001  # Eccentricity
i = math.radians(55)  # Inclination in rad
Ω = math.radians(120)  # Right ascension of ascending node in rad
w = math.radians(30)  # Argument of perigee in rad
M = math.radians(45)  # Mean anomaly in rad

B, L, H = kepler_to_blh(a, e, i, Ω, w, M)
print('B =', math.degrees(B), 'deg')  # degrees function converts rad to deg
print('L =', math.degrees(L), 'deg')
print('H =', H, 'km')
