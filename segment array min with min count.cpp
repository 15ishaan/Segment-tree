#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define fastIO ios_base::sync_with_stdio(false);cin.tie(NULL);
#define pb push_back
#define pl pair<ll, ll>
#define vl vector<ll>
#define mod 1000000007
#define N 300003
#define inf 1e18
vector<pl> mins(N);

pl merge(pl a, pl b)
{
    if(a.first > b.first) return b;
    else if(a.first < b.first) return a;
    else return {a.first, a.second+b.second}; 
}

void build(vl &a, ll x, ll lx, ll rx)
{
    if(rx-lx == 1)
    {
        if(lx < (ll)a.size())
        {
            mins[x] = {a[lx], (ll)1};
        }
        return;
    }
    ll m = (lx+rx)/2;
    build(a, 2*x+1, lx, m);
    build(a, 2*x+2, m, rx);
    mins[x] = merge(mins[2*x+1], mins[2*x+2]);
}

void fill(ll i, ll v, ll x, ll lx, ll rx)
{
    if(rx-lx == 1) 
    {
        mins[x] = {v, (ll)1};
        return;
    }
    ll m = (lx+rx)/2;
    if(i < m) fill(i, v, 2*x+1, lx, m);
    else fill(i, v, 2*x+2, m, rx);
    mins[x] = merge(mins[2*x+1], mins[2*x+2]);
}

pl minimum(ll l, ll r, ll x, ll lx, ll rx)
{
    if(lx >= r || rx <= l) return {inf, inf};
    if(lx >= l && rx <= r) 
    {
        //cout<<sums[x]<<" ";
        return mins[x];
    }
    ll m = (lx+rx)/2;
    pl s1 = minimum(l, r, 2*x+1, lx, m);
    pl s2 = minimum(l, r, 2*x+2, m, rx);
    return (merge(s1, s2));
}

int main()
{
    fastIO
    ll n, m; cin>>n>>m;
    ll sz = 1;
    while(sz < n) sz *= 2;
    vl a(n);
    for(ll i = 0; i < n; i++) 
    {
        cin>>a[i];
    }
    build(a, 0, 0, sz);
    while(m--)
    {
        ll y; cin>>y;
        if(y == 1)
        {
            ll i, v; cin>>i>>v;
            fill(i, v, 0, 0, sz);
            // for(ll i = 0; i < 2*n-1; i++) cout<<sums[i]<<" ";
        }
        else
        {
            ll l, r; cin>>l>>r;
            pl ans = minimum(l, r, 0, 0, sz);
            cout<<ans.first<<" "<<ans.second<<"\n";
        }
    }
}