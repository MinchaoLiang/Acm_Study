const int inf=0x3f3f3f3f,M=1000005;
int n,m,k,s,t,tot=1,ans,mx;
int f[100],p[100],g[100][100],num[100];//这里不开这么大第二个点会RE，不知道为什么
int ne[M],to[M],h[M],flow[M],lev[M],q[M];
void add(int x,int y,int z) {
    to[++tot]=y,ne[tot]=h[x],h[x]=tot,flow[tot]=z;
    to[++tot]=x,ne[tot]=h[y],h[y]=tot,flow[tot]=0;
}
int dfs(int x,int liu) {
    if(x==t) return liu;
    int kl,sum=0;
    for(int i=h[x];i;i=ne[i])
        if(flow[i]>0&&lev[to[i]]==lev[x]+1) {
        kl=dfs(to[i],min(flow[i],liu-sum));
        sum+=kl,flow[i]-=kl,flow[i^1]+=kl;
        if(sum==liu) return sum;
    }
    return sum;
}
int bfs() {
    for(int i=1;i<=ans*(n+1);++i) lev[i]=0;
    int he=1,ta=1,x;lev[t]=0,q[1]=s;
    while(he<=ta) {
        x=q[he],++he;
        if(x==t) return 1;
        for(int i=h[x];i;i=ne[i])
            if(flow[i]>0&&!lev[to[i]])
            lev[to[i]]=lev[x]+1,q[++ta]=to[i];
    }
    return 0;
}
int main()
{
    int x,y;
    scanf("%d%d%d",&n,&m,&k);
    s=0,t=M-2;
    for(int i=1;i<=m;++i) {
        scanf("%d%d",&p[i],&num[i]);
        for(int j=0;j<num[i];++j) {
            scanf("%d",&g[i][j]);
        }
    }
    for(ans=1;;++ans) {//枚举答案
        add(s,(ans-1)*(n+1)+n+1,inf);//n+1是地球，汇点是月球。向地球连inf的边
        for(int i=1;i<=m;++i) {
            x=(ans-1)%num[i],y=ans%num[i];
            if(g[i][x]==n+2) x=t;
            else x=(ans-1)*(n+1)+g[i][x];
            if(g[i][y]==n+2) y=t;
            else y=ans*(n+1)+g[i][y];
            add(x,y,p[i]);
        }
        while(bfs()) mx+=dfs(s,inf);//dinic网络流
      }
    }
    return 0;
}