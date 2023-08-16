namespace KMP {
	template<typename Ty>
	size_t GetNext(int* next, const Ty* patt, size_t pattlen = 0) {
		ll k = -1; next[0] = -1;
		if (pattlen) {
			for (size_t i = 1; i < pattlen; next[i++] = k) {
				while (~k && patt[k + 1] != patt[i])k = next[k];
				if (patt[k + 1] == patt[i])k++;
			}
			return pattlen;
		}
		for (next[0] = -1, pattlen = 1; patt[pattlen]; next[pattlen++] = k) {
			while (~k && patt[k + 1] != patt[pattlen])k = next[k];
			if (patt[k + 1] == patt[pattlen])k++;
		}
		return pattlen;
	}
	template<typename Ty>
	int kmp_search(const Ty* mainstr, const Ty* patt, size_t mainlen = 0, size_t pattlen = 0) {
		ll j = -1;
		static int kmpnext[N];
		pattlen = GetNext(kmpnext, patt, pattlen);
		if (mainlen) {
			for (size_t i = 0; i < mainlen; i++) {
				while (~j && patt[j + 1] != mainstr[i])j = kmpnext[j];
				if (patt[j + 1] == mainstr[i])j++;
				if (j == pattlen - 1) { std::cout << i - j + 1 << endl; j = kmpnext[j]; }
			}
		}
		else {
			for (size_t i = 0; mainstr[i]; i++) {
				while (~j && patt[j + 1] != mainstr[i])j = kmpnext[j];
				if (patt[j + 1] == mainstr[i])j++;
				if (j == pattlen - 1) { std::cout << i - j + 1 << endl; j = kmpnext[j]; }
			}
		}
		for (int i = 0; i < pattlen; i++) std::cout << kmpnext[i] + 1 << blank;
		return -1;
	}
}

