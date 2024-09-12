template<typename _Ty, typename T2>
std::istream& operator>>(std::istream& in, std::pair<_Ty, T2>& b) {
	in >> b.first >> b.second;
	return in;
}