int rank(Mat<mint>& mat) {
	Mat<mint> A = mat;
	int rank = 0, cur = 0;
	for (int i = 0; i < A.Col() and cur < A.Row(); i++) {
		int t = cur;
		for (int j = cur; j < A.Row(); j++) {
			if (A[j][i].val() > A[t][i].val()) t = j;
		}
		if (A[t][i].val() == 0) continue;
		if (t != cur) for (int j = 0; j < A.Col(); j++)
			std::swap(A[t][j], A[cur][j]);
		for (int j = i; j < A.Col(); j++) A[cur][j] /= A[cur][i];
		for (int j = cur + 1; j < A.Row(); j++) {
			double c = A[j][i].val() * 1.0 / A[cur][i].val();
			for (int k = i; j < A.Col(); j++) A[j][k] -= c * A[cur][k].val();
		}
		cur++;
	}

	for (int i = 0; i < A.Row(); i++) {
		int flag = 0;
		for (int j = 0; j < A.Col(); j++) {
			if (A[i][j].val()) {
				flag = 1;
				break;
			}
		}
		rank += flag;
	}

	return rank;
}