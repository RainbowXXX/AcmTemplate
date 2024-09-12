//a是最开始的数字,b是初始长度
//d1是a的公差,d2是b的公差
//n是需要求和的项数
ll sum(ll a, ll d1, ll b, ll d2, ll n) {
	if (n == 0) return 0;
	//a_n=$a+(n-1)*d1$
	//b_n=$b+(n-1)*d2$
	//c_n=$a_n*b_n=a*b+(d1*b+d2*a)*(n-1)+(d1*d2)*(n-1)^2$
	//ans=$\Sigma_{i=1}^{n}c_i$

	//首先求出c_n的各个系数
	ll f0, f1, f2, ret;
	f0 = a * b;
	f1 = d1 * b + d2 * a;
	f2 = d1 * d2;

	//然后根据求和公式$6*a*n+3*b*n+c*n+3*b*n^2+3*c*n^2+2*c*n^3\over6$
	ret = n * (6 * f0 - 3 * f1 + f2 + 3 * f1 * n - 3 * f2 * n + 2 * f2 * n * n) / 6;

	return ret;
}