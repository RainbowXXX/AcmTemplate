auto& in() { return (std::cin); }
template <class T, class ...Args>
auto& in(T& first, Args&... args) { in() >> first; return in(args...); }

auto& out() { return (std::cout); }
template <class T>
auto& out(T first) { return (out() << first); }
template <class T, class ...Args>
auto& out(T first, Args... args) { out() << first << blank; return out(args...); }