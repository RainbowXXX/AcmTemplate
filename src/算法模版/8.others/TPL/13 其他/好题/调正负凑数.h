/*
ABC326F
最开始在(0,0) 向右
n次操作 每次操作左转90或右转90然后走A[I]步
问能否走到(X,Y) 如何走到
*/
#include<bits/stdc++.h>
using namespace std;
int A[80],ans[80];
#define pb push_back
map<int,int>ii;
void sol(vector<int>p,int S){
	ii.clear();
	int sz=p.size(),tz=sz/2;
	for(int s=0;s<(1<<tz);s++){
		int su=0;
		for(int i=0;i<tz;i++)if((s>>i)&1)su+=A[p[i]];
		else su-=A[p[i]];
		ii[su]=s;
	}
	for(int s=0;s<(1<<(sz-tz));s++){
		int su=0;
		for(int i=0;i<sz-tz;i++)if((s>>i)&1)su+=A[p[i+tz]];
		else su-=A[p[i+tz]];
		if(ii.find(S-su)!=ii.end()){
			for(int i=0;i<sz-tz;i++)if((s>>i)&1)ans[p[i+tz]]=1;
			for(int i=0;i<tz;i++)if((ii[S-su]>>i)&1)ans[p[i]]=1;
			return;
		}
	}
	puts("No");exit(0);
}
int n,dx[4]={1,0,-1,0},dy[4]={0,1,0,-1};
int main(){
	int X,Y;
	scanf("%d%d%d",&n,&X,&Y);
	for(int i=0;i<n;i++)scanf("%d",&A[i]);
	vector<int>py,px;
	for(int i=0;i<n;i+=2)py.pb(i);
	for(int i=1;i<n;i+=2)px.pb(i);
	sol(px,X),sol(py,Y);puts("Yes");
	int ne=0,nx=0,ny=0;
	for(int i=0;i<n;i++){
		int Z;
		if(i&1)Z=(ans[i]?0:2);
		else Z=(ans[i]?1:3);
		if((ne+1)%4==Z)printf("L");else printf("R");
		ne=Z;
		nx+=dx[Z]*A[i],ny+=dy[Z]*A[i];
	}
	return 0;
}