namespace MTT {
    const double Pi = acos(-1.0);
    typedef std::complex<double> comp;
    const comp I(0, 1);
    int rev[N], Mod, coe;
    comp wn[N], p[N], q[N], a0[N], a1[N], b0[N], b1[N];
    ll ans[N];

    inline ll num(comp x) {
        double d = x.real();
        return d < 0 ? ll(d - 0.5) % Mod : ll(d + 0.5) % Mod;
    }

    void FFT(comp *tmp, int n, int mode) {
        for (int i = 1; mode == -1 && i < n; i++) {
            if (i < (n - i))
                swap(tmp[i], tmp[n - i]);
        }
        for (int i = 0; i < n; i++) {
            if (i < rev[i])
                swap(tmp[i], tmp[rev[i]]);
        }
        for (int mid = 1; mid < n; mid <<= 1) {
            for (int R = mid << 1, i = 0; i < n; i += R) {
                for (int k = 0; k < mid; k++) {
                    comp w = wn[1LL * k * n / mid];
                    comp x = tmp[i + k], y = w * tmp[i + k + mid];
                    tmp[i + k] = x + y;
                    tmp[i + k + mid] = x - y;
                }
            }
        }
        for (int i = 0; mode == -1 && i < n; i++) {
            tmp[i] /= n;
        }
    }

    void MTT(comp *a, comp *b, int len, int mode) {
        for (int i = 0; i < len; i++)
            a[i] = a[i] + I * b[i];
        FFT(a, len, mode);
        for (int i = 0; i < len; i++)
            b[i] = conj(a[i ? len - i : 0]);
        for (int i = 0; i < len; i++) {
            comp x = a[i], y = b[i];
            a[i] = (x + y) * 0.5;
            b[i] = (y - x) * 0.5 * I;
        }
    }

    void init(const int *a, const int *b, int n, int m) {
        coe = int(sqrt(Mod) + 1);
        for (int i = 0; i <= n; i++) {
            int x = a[i];
            x %= Mod;
            a0[i] = x / coe;
            a1[i] = x % coe;
        }
        for (int i = 0; i <= m; i++) {
            int x = b[i];
            x %= Mod;
            b0[i] = x / coe;
            b1[i] = x % coe;
        }
        int len = 1, bit = 0;
        while (len <= (n + m))
            len <<= 1, bit++;
        for (int i = 0; i < len; i++) {
            rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (bit - 1));
            wn[i] = comp(cos(Pi / len * i), sin(Pi / len * i));
        }
        MTT(a0, a1, len, 1);
        MTT(b0, b1, len, 1);
        for (int i = 0; i < len; i++) {
            p[i] = a0[i] * b0[i] + I * a1[i] * b0[i];
            q[i] = a0[i] * b1[i] + I * a1[i] * b1[i];
        }
        FFT(p, len, -1);
        FFT(q, len, -1);
        for (int i = 0; i <= n + m; i++) {
            ll t = (coe * coe * num(p[i].real()) % Mod + coe * (num(p[i].imag()) + num(q[i].real())) % Mod +
                    num(q[i].imag())) % Mod;
            ans[i] = t;
        }
    }
}