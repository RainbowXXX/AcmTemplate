/*
a[i] = a1+(i-1)*d
b[i] = b1*(q^(i-1))
c[i] = a[i]*b[i] = (A*n+B)*(q^(n-1))
A = b1*d
B = a1*b1-b1*d = a1*b1-A
Sn = Sum(c[1]~c[n])
(1-q)*Sn=(A+B)+(A/(1-q))*q-(A*n+B+A/(1-q))*Pow(q,n)
*/
ll Sn(ll A, ll B, ll q, ll n) { return ((A + B) + (A * q / (1LL - q)) - (A * n + B + A / (1 - q)) * Pow(q, n)) / (1LL - q); }