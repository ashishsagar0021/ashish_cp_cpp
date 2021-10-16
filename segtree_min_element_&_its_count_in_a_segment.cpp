#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

template<class T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
//*s.find_by_order();
//s.order_of_key();

#define int                 		long long
#define double              		long double
#define endl                		"\n"
#define pb                  		push_back
#define PI                  		3.1415926535897932384626433832795l
#define F                   		first
#define S                   		second
#define f(i,n)              		for(int i=0;i<n;++i)
#define loop(i,a,b)         		for (int i=a ; i<b ;++i)
#define fastio              		ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define all(v)              		(v).begin(),(v).end()
#define rall(v)             		(v).rbegin(),(v).rend()
#define gcd(a,b)            		__gcd((a),(b))
#define fill(a,value)       		memset(a,value,sizeof(a));
#define print(x)            		cout<<(x)<<endl;
typedef pair<int, int>      		pii;
typedef vector<int>         		vi;
const int mod = 1e9 + 7;
const int MOD = 998244353;
const int inf = 1e9;
const int N = 5005;


struct segtree {

	int size;
	vector<int>mins;
	vector<int>cnt;
	void init(int n) {
		size = 1;
		while (size < n) {
			size *= 2;
		}
		mins.assign(2 * size, 0);
		cnt.assign(2 * size, 0);
	}

	void build(vector<int> &a, int x, int lx, int rx) {
		if (rx - lx == 1) {
			if (lx < (int)a.size()) {
				mins[x] = a[lx];
				cnt[x] = 1;
			}
			return;
		}
		int m = (lx + rx) / 2;
		build(a, 2 * x + 1, lx , m);
		build(a, 2 * x + 2, m, rx);
		if (mins[2 * x + 1] == mins[2 * x + 2]) {
			mins[x] = mins[2 * x + 1];
			cnt[x] = cnt[2 * x + 1] + cnt[2 * x + 2];
		}
		else if (mins[2 * x + 1] < mins[2 * x + 2]) {
			mins[x] = mins[2 * x + 1];
			cnt[x] = cnt[2 * x + 1];
		}
		else {
			mins[x] = mins[2 * x + 2];
			cnt[x] = cnt[2 * x + 2];
		}

	}

	void build(vector<int> &a) {
		build(a, 0, 0, size);

	}

	void set(int i, int v, int x, int lx, int rx) {
		if (rx - lx == 1) {
			mins[x] = v;
			cnt[x] = 1;
			return;
		}
		int m = (lx + rx) / 2;
		if (i < m) {
			set(i, v, 2 * x + 1, lx , m);
		}
		else {
			set(i, v, 2 * x + 2, m, rx);
		}
		if (mins[2 * x + 1] == mins[2 * x + 2]) {
			mins[x] = mins[2 * x + 1];
			cnt[x] = cnt[2 * x + 1] + cnt[2 * x + 2];
		}
		else if (mins[2 * x + 1] < mins[2 * x + 2]) {
			mins[x] = mins[2 * x + 1];
			cnt[x] = cnt[2 * x + 1];
		}
		else {
			mins[x] = mins[2 * x + 2];
			cnt[x] = cnt[2 * x + 2];
		}
	}
	void set(int i, int v) {
		set(i, v, 0, 0, size);
	}
	pair<int, int> minn(int l, int r, int x, int lx, int rx) {
		if (lx >= r || l >= rx) {
			return {INT_MAX, 0};
		}
		if (lx >= l && rx <= r) {
			return {mins[x], cnt[x]};
		}
		int m = (lx + rx) / 2;
		pair<int, int> s1 = minn(l, r, 2 * x + 1, lx, m);
		pair<int, int> s2 = minn(l, r, 2 * x + 2, m , rx);
		if (s1.first == s2.first) {
			return {s1.first, s1.second + s2.second};
		}
		else if (s1.first < s2.first) {
			return {s1.first, s1.second};
		}
		else {
			return {s2.first, s2.second};
		}
	}

	pair<int, int> minn(int l, int r) {
		return minn(l, r, 0, 0, size);
	}

};



void solve()
{
	int n, m;
	cin >> n >> m;

	segtree st;
	st.init(n);
	vector<int>a(n);
	for (int i = 0; i < n; ++i) {
		cin >> a[i];
	}
	st.build(a);
	while (m--) {
		int op;
		cin >> op;
		if (op == 1) {
			int i, v;
			cin >> i >> v;
			st.set(i, v);
		}
		else {
			int l, r;
			cin >> l >> r;
			cout << st.minn(l, r).first << " " << st.minn(l, r).second << "\n";
		}
	}
}


signed main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif

	fastio;
	cout << fixed << setprecision(12);

	int T = 1;
	// cin >> T;

	f(tc, T)
	{
		// cout << "Case #" << tc + 1 << ": ";
		solve();
	}
	return 0;
}
