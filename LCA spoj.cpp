#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define fastIO ios_base::sync_with_stdio(false);cin.tie(NULL);
#define pb push_back
#define pl pair<ll, ll>
#define vl vector<ll>
#define mod 1000000007
#define N 40002
#define inf 1e18

void dfs(ll node, ll parent, vector<vl> &G, vector<vl> &LCA, vl &lvl, vl &vis)
{
    vis[node] = 1;
    LCA[node][0] = parent;
    if(parent == -1) lvl[node] = 0;
    else lvl[node] = lvl[parent] + 1;
    for(auto i: G[node])
    {
        if(!vis[i]) dfs(i, node, G, LCA, lvl, vis);
    }
}

int main()
{
	fastIO
	ll t; cin>>t;
	for(int test = 1; test <= t; test++)
	{
        cout<<"Case "<<test<<":\n";
        ll n; cin>>n;
        ll sz = log2(n);
        if(pow(2, sz) != n) sz += 1;
        vector<vl> G(n+1);
        vector<vl> LCA(n+1, vl(sz+1, -1));
        vl lvl(n+1, 0);
        vl vis(n+1, 0);
        for(int i = 0; i < n; i++)
        {
            ll x; cin>>x;
            for(int j = 0; j < x; j++)
            {
                ll node; cin>>node;
                G[i+1].push_back(node); 
                G[node].push_back(i+1);
            }
        }
        // find first par, lvl of each node
        dfs(1, -1, G, LCA, lvl, vis);

        //find 2^k parent of each node
        for(int i = 1; i <= sz; i++)
        {
            for(int j = 1; j <= n; j++)
            {
                ll prevpar = LCA[j][i-1];
                if(prevpar != -1)
                {
                    ll newpar = LCA[prevpar][i-1];            //2^5 = 2^4+2^4;
                    LCA[j][i] = newpar;
                }
            }
        }
        ll q; cin>>q;
        while(q--)
        {
            ll u, v; cin>>u>>v;
            if(lvl[u] > lvl[v]) swap(u, v);
            ll d = lvl[v]-lvl[u];

            //making lvls equal
            while(d)
            {
                ll p = log2(d);
                v = LCA[v][p];
                d -= (1<<p);
            }
            if(u == v) cout<<u<<"\n";
            else 
            {
                //moving upward of both nodes
                for(int i = sz; i >= 0; i--)
                {
                    if(LCA[u][i] != -1 && LCA[u][i] != LCA[v][i])
                    {
                        u = LCA[u][i];
                        v = LCA[v][i];
                    }
                }
                cout<<LCA[u][0]<<"\n";
            }
        }
    }
}