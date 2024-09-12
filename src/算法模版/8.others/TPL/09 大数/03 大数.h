struct BigInt
{
	VE<ll> v;
	ll carry = 1e10;

	void Read(STR s)
	{
		for (ll i = s.size() - 1; i >= 0;)
		{
			ll len = min(10LL, i + 1);
			STR t = s.substr(i - len + 1, len);
			i -= len;
			v.push_back(stoll(t));
		}
		return;
	}
	void Read(VE<ll> b) { v = b; }
	void Read(ll b)
	{
		VE<ll> B;
		B.push_back(b);
		Read(B);
		return;
	}

	VE<ll> Add(VE<ll> &B) // 加一个大数
	{
		ll t = 0;
		VE<ll> res;
		for (ll i = 0; i < v.size() or i < B.size(); ++i)
		{
			if (i < v.size())
				t += v[i];
			if (i < B.size())
				t += B[i];
			res.push_back(t % carry);
			t /= carry;
		}
		if (t)
			res.push_back(1);
		v = res;
		return res;
	}
	VE<ll> Add(ll b) // 加一个小数
	{
		ll t = 0;
		VE<ll> res;
		VE<ll> B;
		B.push_back(b);
		for (ll i = 0; i < v.size() or i < B.size(); ++i)
		{
			if (i < v.size())
				t += v[i];
			if (i < B.size())
				t += B[i];
			res.push_back(t % carry);
			t /= carry;
		}
		if (t)
			res.push_back(1);
		v = res;
		return res;
	}

	VE<ll> Sub(VE<ll> &B) // 减一个大数
	{
		ll t = 0;
		VE<ll> res;
		for (ll i = 0; i < v.size(); ++i)
		{
			t = v[i] - t;
			if (i < B.size())
				t -= B[i];
			res.push_back((t + carry) % carry);
			if (t < 0)
				t = 1;
			else
				t = 0;
		}
		while (res.size() > 1 and res.back() == 0)
			res.pop_back();
		v = res;
		return res;
	}
	VE<ll> Sub(ll b) // 减一个小数
	{
		ll t = 0;
		VE<ll> B;
		B.push_back(b);
		VE<ll> res;
		for (ll i = 0; i < v.size(); ++i)
		{
			t = v[i] - t;
			if (i < B.size())
				t -= B[i];
			res.push_back((t + carry) % carry);
			if (t < 0)
				t = 1;
			else
				t = 0;
		}
		while (res.size() > 1 and res.back() == 0)
			res.pop_back();
		v = res;
		return res;
	}

	VE<ll> Mul(ll b) // 乘一个小数
	{
		ll t = 0;
		VE<ll> res;
		for (ll i = 0; i < v.size() or t; ++i)
		{
			if (i < v.size())
				t += v[i] * b;
			res.push_back(t % carry);
			t /= carry;
		}
		while (res.size() > 1 and res.back() == 0)
			res.pop_back();
		v = res;
		return res;
	}
	VE<ll> Mul(VE<ll> &B) // 乘一个大数，可以用fft
	{
		VE<ll> res(v.size() + B.size() + 5, 0);
		for (ll i = 0; i < v.size(); ++i)
		{
			for (ll j = 0; j < B.size(); ++j)
			{
				res[i + j] += v[i] * B[j];
				res[i + j + 1] += res[i + j] / carry;
				res[i + j] %= carry;
			}
		}
		while (res.size() > 1 and res.back() == 0)
			res.pop_back();
		v = res;
		return res;
	}

	VE<ll> Div(ll b) // 除一个小数，不要余数
	{
		VE<ll> res;
		ll r = 0;
		for (ll i = v.size() - 1; i >= 0; --i)
		{
			r = r * carry + v[i];
			res.push_back(r / b);
			r %= b;
		}
		reverse(res.begin(), res.end());
		while (res.size() > 1 and res.back() == 0)
			res.pop_back();
		v = res;
		return res;
	}
	VE<ll> Div(ll b, ll &r) // 除一个小数，要余数
	{
		VE<ll> res;
		r = 0;
		for (ll i = v.size() - 1; i >= 0; --i)
		{
			r = r * carry + v[i];
			res.push_back(r / b);
			r %= b;
		}
		reverse(res.begin(), res.end());
		while (res.size() > 1 and res.back() == 0)
			res.pop_back();
		v = res;
		return res;
	}

	bool CMP(VE<ll> &B) // 比较大小
	{
		if (v.size() != B.size())
			return v.size() > B.size();
		for (int i = v.size() - 1; i >= 0; i--)
			if (v[i] != B[i])
				return v[i] > B[i];
		return true;
	}

	void Write(void)
	{
		cout << v[v.size() - 1];
		for (int i = v.size() - 2; i >= 0; i--)
			cout << setw(10) << setfill('0') << v[i];
		return;
	}
};