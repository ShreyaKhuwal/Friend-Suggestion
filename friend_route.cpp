#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
#define pq vector<priority_queue<pair<ll, ll>,vector<pair<ll,ll> >,greater<pair<ll,ll> > > > 
ll vertex,edges,start,end;
vector<ll>e;
vector<vector<ll> >f;
vector<vector<ll> >b;
vector<vector<ll> >cf;
vector<vector<ll> >cb;
vector<bool>vis0;
vector<bool>vis1;
vector<ll>inqueue;
vector<ll>forward;
vector<ll>backward;
vector<vector<ll> >distance_;
void clear1() {
        for (ll i = 0; i < inqueue.size(); ++i) {
            ll v = inqueue[i];
            distance_[0][v] =INT_MAX;
			 distance_[1][v] = INT_MAX;
            vis0[v] = false;
            vis1[v]=false;
        }
        inqueue.clear();
    }
ll ShortestPath() {
		ll dist = INT_MAX,p;
		for(ll i=0;i<inqueue.size();i++) {
			ll u=inqueue[i];
			if (distance_[0][u] + distance_[1][u] < dist) {
				dist = distance_[0][u] + distance_[1][u];
				p=u;
			}
		}
		if (dist == INT_MAX)
			return -1;
		ll r=p;
		while(r!=start)
		{
			e.push_back(r);
			r=forward[r];
			}
			e.push_back(r);
			reverse(e.begin(),e.end());
			r=p;
			while(r!=end)
			{
				r=backward[r];
				e.push_back(r);
				}	
		return dist;
}
void visit(pq& q, ll side, ll v, ll dist,ll u) {
		if ( distance_[side][v] > dist) {
			distance_[side][v] = dist;
			if(side)backward[v]=u;
			else forward[v]=u;
			q[side].push({distance_[side][v], v});
			inqueue.push_back(v);
		}
    }
void Process(pq& q, ll side, ll u, vector<vector<ll> > &adj) {
		for (ll i = 0; i < adj[u].size(); ++i) {
				ll v = adj[u][i];
				visit(q, side, v, distance_[side][u] + 1,u);
		}	
}
ll extractMin(pq& q, ll side) {
		pair<ll,ll> p = q[side].top();
		q[side].pop();
		return p.second;
	}
ll query(ll s, ll t) {
        clear1();
        forward.clear();
        backward.clear();
        forward.resize(vertex);
        backward.resize(vertex);
        pq q(2);
        visit(q, 0, s, 0,s);
        visit(q, 1, t, 0,s);
		while (!q[0].empty() && !q[1].empty()) {
				ll v = extractMin(q, 0);
				Process(q, 0, v, f);
				if (vis1[v] == true)
                    return ShortestPath();
				vis0[v] = true;
				
				ll v_r = extractMin(q, 1);
				Process(q, 1, v_r, b);
				if (vis0[v_r] == true)
                    return ShortestPath();
				vis1[v_r] = true;
			}
        return -1;
    }
int main()
{
	cin>>vertex>>edges;
	ll u,v;
	vis0.resize(vertex,0);
	forward.resize(vertex);
	backward.resize(vertex);
	vis1.resize(vertex,0);
	distance_.resize(2,vector<ll>(vertex,INT_MAX));
	f.resize(vertex,vector<ll>());
	b.resize(vertex,vector<ll>());
	for(ll i=0;i<edges;i++)
	{
		cin>>u>>v;
		f[u-1].pb(v-1);
		b[v-1].pb(u-1);
	}
	ll t;
	cin>>t;
	for(ll i=0;i<t;i++)
	{
		cin>>u>>v;
		start=u-1,end=v-1;
		e.clear();
		cout<<query(u-1,v-1)<<"\n";
		for(ll j=0;j<e.size();j++)cout<<e[j]+1<<" ";
		//e.clear();
		cout<<"\n";
	}
	return 0;
}
