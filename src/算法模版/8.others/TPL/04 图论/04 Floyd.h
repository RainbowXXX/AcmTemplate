FOR(k, 1, n)
FOR(x, 1, n)
FOR(y, 1, n)
f[x][y] = std::min(f[x][y], f[x][k] + f[k][y]);