function f(func)
a = [inf, -inf, nan, pi, pi/2, pi/4, -pi, -pi/2, -pi/4, 0];
format long e
z = func(a);
disp(a)
disp(z)