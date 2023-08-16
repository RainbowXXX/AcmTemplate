auto& in() { return (std::cin); }
template <class T, class ...Args>
auto& in(T& first, Args&... args) { std::cin >> first; return in(args...); }