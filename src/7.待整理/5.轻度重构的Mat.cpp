struct preClass {
	int inited;
	preClass() { inited = 0; }
};
template <class _Ty>
struct Mat : public preClass {
	using EType = _Ty;
	using Elem = EType;
private:
	struct ElemLine {
		size_t _col;
		Elem* _matdata;
		constexpr ElemLine(ElemLine&& rhs) : _col(rhs._col), _matdata(rhs._matdata) {}
		constexpr ElemLine(const ElemLine& rhs) : _col(rhs._col), _matdata(rhs._matdata) {}
		constexpr ElemLine(size_t col, Elem* matdata) : _col(col), _matdata(matdata) {}
		constexpr void operator = (std::initializer_list<Elem> data) {
			ensure(data.size() == _col);
			std::copy(data.begin(), data.end(), _matdata);
		}
		constexpr Elem& operator [] (size_t pos) {
			ensure(pos < _col);
			return _matdata[pos];
		}
	};

	Elem* _matdata;
	size_t _row, _col, _size;

public:
	Mat() {
		if (inited == 0) {
			_row = 2; _col = 2; _size = 4;
			_matdata = new Elem[_row * _col]; ensure(_matdata);
			memset(_matdata, 0, _row * _col * sizeof(Elem)); inited = 1;
		}
		else {
			if (_size < 4) {
				delete[] _matdata; _row = 2; _col = 2; _size = 4;
				_matdata = new Elem[_row * _col]; ensure(_matdata);
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
	Mat(size_t row, size_t col) {
		if (inited == 0) {
			_row = row; _col = col; _size = row * col;
			_matdata = new Elem[_row * _col]; ensure(_matdata);
			memset(_matdata, 0, _row * _col * sizeof(Elem)); inited = 1;
		}
		else {
			if (_size < row * col) {
				delete[] _matdata; _row = row; _col = col; _size = row * col;
				_matdata = new Elem[_row * _col]; ensure(_matdata);
			}
			memset(_matdata, 0, _row * _col * sizeof(Elem));
		}
	}
	Mat(const Mat<Elem>& v) {
		size_t vrow = v._row, vcol = v._col;
		if (inited == 0) {
			_row = vrow; _col = vcol; _size = _row * _col;
			_matdata = new Elem[_row * _col]; ensure(_matdata);
			memset(_matdata, 0, _row * _col * sizeof(Elem)); inited = 1;
		}
		else {
			if (vrow * vcol > _size) {
				delete[] _matdata; _matdata = NULL;
				_matdata = new Elem[vrow * vcol]; ensure(_matdata);
			}
			_col = vcol; _row = vrow;
			memset(_matdata, 0, vcol * vrow * sizeof(Elem));
		}
		for (size_t i = 0; i < _row; i++) for (size_t j = 0; j < _col; j++) _matdata[i * _col + j] = v._matdata[i * _col + j];
	}

	ElemLine operator [] (size_t x) {
		return ElemLine(_col, &_matdata[x * _col]);
	}
	friend std::istream& operator >> (std::istream& io, Mat& mat) {
		size_t _row = mat.Row(), _col = mat.Col();
		for (size_t i = 0; i < _row; i++) {
			for (size_t j = 0; j < _col; j++) io >> mat[i][j];
		}
		return io;
	}
	friend std::ostream& operator << (std::ostream& io, Mat&& mat) {
		size_t _row = mat.Row(), _col = mat.Col();
		for (size_t i = 0; i < _row; i++) {
			io << mat[i][0];
			for (size_t j = 1; j < _col; j++) io << ' ' << mat[i][j];
			if (i != _row - 1) io << endl;
		}
		return io;
	}
	friend std::ostream& operator << (std::ostream& io, Mat& mat) {
		size_t _row = mat.Row(), _col = mat.Col();
		for (size_t i = 0; i < _row; i++) {
			io << mat[i][0];
			for (size_t j = 1; j < _col; j++) io << ' ' << mat[i][j];
			if (i != _row - 1) io << endl;
		}
		return io;
	}
	Mat<EType>& operator + (const Mat<EType>& v) const {
		ensure(_col == v._col && _row == v._row);
		Mat<EType> ret(_row, _col);
		for (size_t i = 0; i < _row; i++) for (size_t j = 0; j < _col; j++) ret._matdata[i * v._col + j] = _matdata[i * _col + j] + v._matdata[i * _col + j];
		return ret;
	}
	Mat<EType>& operator - (const Mat<EType>& v) const {
		ensure(_col == v._col && _row == v._row);
		Mat<EType> ret(_row, _col);
		for (size_t i = 0; i < _row; i++) for (size_t j = 0; j < _col; j++) ret._matdata[i * v._col + j] = _matdata[i * _col + j] - v._matdata[i * _col + j];
		return ret;
	}
	Mat<EType> operator * (const Mat<EType>& v) const {
		ensure(_col == v._row);
		Mat<EType> ret(_row, v._col);
		for (size_t i = 0; i < _row; i++) {
			for (size_t j = 0; j < v._col; j++) {
				EType t = 0;
				for (size_t k = 0; k < _col; k++)
					t = t + _matdata[i * _col + k] * v._matdata[k * v._col + j];
				ret._matdata[i * v._col + j] = t;
			}
		}
		return ret;
	}
	Mat<EType>& operator * (const ll& v) const {
		Mat<EType> ret(_row, _col);
		for (size_t i = 0; i < _row; i++) for (size_t j = 0; j < _col; j++) ret[i][j] = _matdata[i * _col + j] * v;
		return ret;
	}
	void operator *= (const Mat<EType>& v) {
		EType* tem, t = 0;
		ensure(_col == v._row);
		tem = new EType[_row * v._col];
		for (size_t i = 0; i < _row; i++) {
			for (size_t j = 0; j < v._col; j++) {
				t = 0;
				for (size_t k = 0; k < _col; k++) t = _matdata[i * _col + k] * v._matdata[k * v._col + j] + t;
				tem[i * v._col + j] = t;
			}
		}
		delete[] _matdata; _matdata = tem;
	}
	Mat<EType>& operator % (ll mod) {
		Mat<EType> ret(_row, _col);
		for (size_t i = 0; i < _row; i++) for (size_t j = 0; j < _col; j++) ret._matdata[i * _col + j] = _matdata[i * _col + j] % mod;
		return ret;
	}
	void operator %= (ll mod) {
		for (size_t i = 0; i < _row; i++) for (size_t j = 0; j < _col; j++) _matdata[i * _col + j] %= mod;
	}
	void operator = (const EType& v) {
		for (size_t i = 0; i < _row; i++) for (size_t j = 0; j < _col; j++) _matdata[i * _col + j] = (i == j) * v;
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
		ensure(_matdata != NULL);
		for (size_t i = 0; i < _row; i++) for (size_t j = 0; j < _col; j++) _matdata[i * _col + j] = v._matdata[i * _col + j];
	}
	Mat<EType> T() {
		Mat<EType> ret(_col, _row);
		for (size_t i = 0; i < _row; i++) {
			for (size_t j = 0; j < _col; j++) {
				ret._matdata[j * _row + i] = _matdata[i * _col + j];
			}
		}
		return ret;
	}
	template<typename Ty>
	void operator = (std::initializer_list<std::initializer_list<Ty>> data) {
		ensure(data.size() == _row);
		size_t i = 0;
		for (auto line = data.begin(); line != data.end(); line++, i++) {
			ensure(line->size() == _col);
			std::copy(line->begin(), line->end(), &_matdata[i * _col]);
		}
	}
	Mat<EType> pow(const std::string n) {
		Mat<EType> ret(_row, _col);
		Mat<EType> nxtkey(_row, _col), tem(_row, _col);
		size_t _size = n.size();
		nxtkey = *this; ret = 1;
		while (_size > 0) {
			size_t x = n[_size - 1] - '0';
			for (size_t i = 0; i < x; i++) ret *= nxtkey;
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
	size_t Row() const { return _row; }
	size_t Col() const { return _col; }
};