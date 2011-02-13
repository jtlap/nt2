csch(function g
x = linspace(0,0.01,100);
f = @(z)(asech(1-x.*x)-sqrt(2).*x-z(1).*x.*x.*x);
h = @(z)(sum(f(z).^2));
f([0,0])
zz = lsqnonlin(f,[0.71])