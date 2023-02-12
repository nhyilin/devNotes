% Define the integrand as an anonymous function
integrand = @(s) exp(1i * (s^5 + Z * s^3 + Y * s^2 + X * s));

% Define the limits of integration as negative and positive infinity
Inf = 20;
lower_limit = -Inf;
upper_limit = Inf;

% Call the integral function to compute the value of the integral
Sw = integral(integrand, lower_limit, upper_limit);
