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
vl sums(N);

//sum of (r-1 to l)
void build(vl &a, ll x, ll lx, ll rx)
{
    if(rx-lx == 1)
    {
        if(lx < (ll)a.size())
        {
            sums[x] = a[lx];;
        }
        return;
    }
    ll m = (lx+rx)/2;
    build(a, 2*x+1, lx, m);
    build(a, 2*x+2, m, rx);
    sums[x] = sums[2*x+1] + sums[2*x+2];
}

void fill(ll i, ll v, ll x, ll lx, ll rx)
{
    if(rx-lx == 1) 
    {
        sums[x] = v;
        return;
    }
    ll m = (lx+rx)/2;
    if(i < m) fill(i, v, 2*x+1, lx, m);
    else fill(i, v, 2*x+2, m, rx);
    sums[x] = sums[2*x+1] + sums[2*x+2];
}

ll sum(ll l, ll r, ll x, ll lx, ll rx)
{
    if(lx >= r || rx <= l) return 0;
    if(lx >= l && rx <= r) 
    {
        //cout<<sums[x]<<" ";
        return sums[x];
    }
    ll m = (lx+rx)/2;
    ll s1 = sum(l, r, 2*x+1, lx, m);
    ll s2 = sum(l, r, 2*x+2, m, rx);
    return s1+s2;
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
            ll ans = sum(l, r, 0, 0, sz);
            cout<<ans<<"\n";
        }
    }
}
