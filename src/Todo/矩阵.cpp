struct preClass {
	int inited;
	preClass() { inited = 0; }
};
template <class _Ty>
struct Mat : public preClass {
	using EType = _Ty;
	using Elem = EType;
private:
	Elem* _matdata;
	int _row, _col, _size;

public:
	Mat() {
		if (inited == 0) {
			_row = 2; _col = 2; _size = 4;
			_matdata = new Elem[_row * _col]; assert(_matdata);
			memset(_matdata, 0, _row * _col * sizeof(Elem)); inited = 1;
		}
		else {
			if (_size < 4) {
				delete[] _matdata; _row = 2; _col = 2; _size = 4;
				_matdata = new Elem[_row * _col]; assert(_matdata);
			}
			memset(_matdata, 0, _row * _col * sizeof(Elem));
		}
	}
	~Mat() {
		delete[] _matdata; inited = 0;
	}
	Mat(Mat<Elem>&& v) noexcept {
		if (inited) delete[] _matdata;
		_matdata = v._matdata; v._matdata = nullptr;
		_row = v._row; _col = v._col; _size = v._size;
	}
	Mat(int row, int col) {
		if (inited == 0) {
			_row = row; _col = col; _size = row * col;
			_matdata = new Elem[_row * _col]; assert(_matdata);
			memset(_matdata, 0, _row * _col * sizeof(Elem)); inited = 1;
		}
		else {
			if (_size < row * col) {
				delete[] _matdata; _row = row; _col = col; _size = row * col;
				_matdata = new Elem[_row * _col]; assert(_matdata);
			}
			memset(_matdata, 0, _row * _col * sizeof(Elem));
		}
	}
	Mat(const Mat<Elem>& v) {
		int vrow = v._row, vcol = v._col;
		if (inited == 0) {
			_row = vrow; _col = vcol; _size = _row * _col;
			_matdata = new Elem[_row * _col]; assert(_matdata);
			memset(_matdata, 0, _row * _col * sizeof(Elem)); inited = 1;
		}
		else {
			if (vrow * vcol > _size) {
				delete[] _matdata; _matdata = NULL;
				_matdata = new Elem[vrow * vcol]; assert(_matdata);
			}
			_col = vcol; _row = vrow;
			memset(_matdata, 0, vcol * vrow * sizeof(Elem));
		}
		for (int i = 0; i < _row; i++) for (int j = 0; j < _col; j++) _matdata[i * _col + j] = v._matdata[i * _col + j];
	}

	Elem* operator [] (int x) {
		return &_matdata[x * _col];
	}
	friend ostream& operator << (ostream& io, Mat&& mat) {
		int _row = mat.Row(), _col = mat.Col();
		for (int i = 0; i < _row; i++) {
			cout << mat[i][0];
			for (int j = 1; j < _col; j++) cout << ' ' << mat[i][j];
			cout << '\n';
		}
		return io;
	}
	friend ostream& operator << (ostream& io, Mat& mat) {
		int _row = mat.Row(), _col = mat.Col();
		for (int i = 0; i < _row; i++) {
			cout << mat[i][0];
			for (int j = 1; j < _col; j++) cout << ' ' << mat[i][j];
			cout << '\n';
		}
		return io;
	}
	Mat<EType>& operator + (const Mat<EType>& v) const {
		assert(_col == v._col && _row == v._row);
		Mat<EType> ret(_row, _col);
		for (int i = 0; i < _row; i++) for (int j = 0; j < _col; j++) ret._matdata[i * v._col + j] = _matdata[i * _col + j] + v._matdata[i * _col + j];
		return ret;
	}
	Mat<EType>& operator - (const Mat<EType>& v) const {
		assert(_col == v._col && _row == v._row);
		Mat<EType> ret(_row, _col);
		for (int i = 0; i < _row; i++) for (int j = 0; j < _col; j++) ret._matdata[i * v._col + j] = _matdata[i * _col + j] - v._matdata[i * _col + j];
		return ret;
	}
	Mat<EType> operator * (const Mat<EType>& v) const {
		assert(_col == v._row);
		Mat<EType> ret(_row, v._col);
		for (int i = 0; i < _row; i++) {
			for (int j = 0; j < v._col; j++) {
				EType t = 0;
				for (int k = 0; k < _col; k++)
					t = t + _matdata[i * _col + k] * v._matdata[k * v._col + j];
				ret._matdata[i * v._col + j] = t;
			}
		}
		return ret;
	}
	Mat<EType>& operator * (const ll& v) const {
		Mat<EType> ret(_row, _col);
		for (int i = 0; i < _row; i++) for (int j = 0; j < _col; j++) ret[i][j] = _matdata[i * _col + j] * v;
		return ret;
	}
	void operator *= (const Mat<EType>& v) {
		EType* tem, t = 0;
		assert(_col == v._row);
		tem = new EType[_row * v._col];
		for (int i = 0; i < _row; i++) {
			for (int j = 0; j < v._col; j++) {
				t = 0;
				for (int k = 0; k < _col; k++) t = _matdata[i * _col + k] * v._matdata[k * v._col + j] + t;
				tem[i * v._col + j] = t;
			}
		}
		delete[] _matdata; _matdata = tem;
	}
	Mat<EType>& operator % (ll mod) {
		Mat<EType> ret(_row, _col);
		for (int i = 0; i < _row; i++) for (int j = 0; j < _col; j++) ret._matdata[i * _col + j] = _matdata[i * _col + j] % mod;
		return ret;
	}
	void operator %= (ll mod) {
		for (int i = 0; i < _row; i++) for (int j = 0; j < _col; j++) _matdata[i * _col + j] %= mod;
	}
	void operator = (const EType& v) {
		for (int i = 0; i < _row; i++) for (int j = 0; j < _col; j++) _matdata[i * _col + j] = (i == j) * v;
	}
	void operator = (const Mat<EType>& v) {
		if (inited == 0) {
			inited = 1; _row = v._row, _col = v._col;
			_matdata = new EType[_row * _col]; _size = _row * _col;
		}
		else {
			if (v._row * v._col > _size) {
				if (_matdata != NULL) delete[] _matdata;
				_row = v._row, _col = v._col;
				_matdata = new EType[_row * _col]; _size = _row * _col;
			}
			else _row = v._row, _col = v._col;
		}
		assert(_matdata != NULL);
		for (int i = 0; i < _row; i++) for (int j = 0; j < _col; j++) _matdata[i * _col + j] = v._matdata[i * _col + j];
	}
	Mat<EType> pow(const string n) {
		Mat<EType> ret(_row, _col);
		Mat<EType> nxtkey(_row, _col), tem(_row, _col);
		int _size = n.size();
		nxtkey = *this; ret = 1;
		while (_size > 0) {
			int x = n[_size - 1] - '0';
			for (int i = 0; i < x; i++) ret *= nxtkey;
			nxtkey *= nxtkey;
			tem = nxtkey * nxtkey; tem *= tem;
			nxtkey *= tem;
			_size--;
		}
		return ret;
	}
	Mat<EType> qpow(ll n)
	{
		Mat<EType> tem(_row, _col), ret(_row, _col);
		tem = *this; ret = 1ll;
		while (n) {
			if (n & 0x1) ret *= tem;
			tem *= tem; n >>= 1;
		}
		return ret;
	}
	int Row() { return _row; }
	int Col() { return _col; }
};