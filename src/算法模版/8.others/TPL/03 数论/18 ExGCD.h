// a * x + b * y == gcd(a, b) == g
ll ExGCD(ll a, ll b, ll &x, ll &y)
{
	if (b == 0)
	{
		x = 1;
		y = 0;
		return a;
	}
	ll tmp_x, tmp_y;
	ll g = ExGCD(b, a % b, tmp_x, tmp_y);
	x = tmp_y;
	y = tmp_x - a / b * tmp_y;
	return g;
}

// a * x + b * y == c
// x = x0 + k * z, k∈Z
using i4 = __int128_t;
bool LiEu(ll a, ll b, ll c, ll &x0, ll &z)
{
	ll x, y;
	ll g = ExGCD(a, b, x, y);
	if (c % g != 0)
		return false;
	z = abs(b / g);
	x0 = (i4)x * (c / g) % z;
	x0 = (x0 + z) % z;
	// 非负解的范围
	// ll w = abs(a / g);
	// y = (i128)y * (c / g) % w;
	// y = (y + w) % w;
	// ll x_l = x0;
	// ll y_l = y;
	// ll x_r = (c - (i128)b * y_l) / a;
	// ll y_r = (c - (i128)a * x_l) / b;
	return true;
}

// 由贝祖定理得：任意两个整数a,b,最大公约数为g=gcd(a,b),
// 那么对于任意的整数x,y，ax+by=c,构成的c一定是g的整数倍(即c%g==0)

// a * x + b * y == c
bool LiEu(ll a, ll b, ll c, ll &x, ll &y)
{
	ll g = ExGCD(a, b, x, y);
	if (c % g != 0)
		return false;
	ll k = c / g;
	x *= k;
	y *= k;
	return true;
}

// 1.ax==b%n 0
// 已知a b n求x
// if(gcd(a,n)==1) 同乘a的逆元
// 改写成2.ax+nk==b (1.==2.)(x,k为未知数)
// 有整数解的充要条件是gcd(a,n)|b
// 1)用ExGCD解出一组(x[0],k[0])
// a*x[0]+n*k[0]==gcd(a,n)
// 两边同除gcd(a,n)再乘b 得到一个解
// 2)若gcd(a,n)==1 且x[0],k[0]是方程2.的一组解
// x=x[0]+n*t k=k[0]-a*t
// 对于任意整数t成立
// 最小整数特解：
// x=(x%t+t)%t
// t=n/gcd(a,n)