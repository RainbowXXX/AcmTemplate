/*<ignore>
摘自《统计的力量——线段树全接触 - 张昆玮》
</ignore>*/
ll query(){
    for (s=s+M-1,t=t+M+1;s^t^1;s>>=1,t>>=1) {
        if (~s&1) Ans+=T[s^1];
        if ( t&1) Ans+=T[t^1];
    }
}

void modify(){
    for(T[n+=M]=V, n>>=1;n;n>>=1)
        T[n]=T[n+n]+T[n+n+1];
}