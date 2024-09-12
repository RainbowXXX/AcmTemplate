#include<bits/stdc++.h>
#define rint register int
#define deb(x) cerr<<#x<<" = "<<(x)<<'\n';
using namespace std;
typedef long long ll;
typedef pair <int,int> pii;
const int maxn = 5e4 + 10;
int n, q, tot;
int t[maxn*30], root[maxn];
int ls[maxn*30], rs[maxn*30]; 
map <int, int> mp; 

void update(int &rt, int pre, int pos, int c, int l, int r){
	if(l>pos || r<pos) return ;
	t[rt = ++tot] = t[pre];
	ls[rt] = ls[pre], rs[rt] = rs[pre];
	if(l == r){
		t[rt] += c;
		return;
	}
	int m = l + r >> 1;
	update(ls[rt], ls[pre], pos, c, l, m);
	update(rs[rt], rs[pre], pos, c, m+1, r);
	t[rt] = t[ls[rt]] + t[rs[rt]];
}

int query(int rt, int pre, int l, int r){
	if(l >= pre) return t[rt];
	int m = l + r >> 1;
	if(m >= pre) return query(ls[rt], pre, l, m) + t[rs[rt]];
	else return query(rs[rt], pre, m+1, r);
}

int main() {
	scanf("%d", &n);
	for(int i=1, tmp, k; i<=n; i++){
		scanf("%d", &tmp);
		if(mp.count(tmp)){
			k = 0;
			update(k, root[i-1], mp[tmp], -1, 1, n);
			update(root[i], k, i, 1, 1, n);
		}
		else update(root[i], root[i-1], i, 1, 1, n);
		mp[tmp] = i;
	}
	scanf("%d", &q);
	while(q--){
		int l, r;
		scanf("%d%d", &l, &r);
		printf("%d\n", query(root[r], l, 1, n));
	}
}