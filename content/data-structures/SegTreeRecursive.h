/**
 * Author: Lucian Bicsi
 * Description: 1D point update and range query where \texttt{cmb} is
 	* any associative operation. \texttt{seg[1]==query(0,N-1)}.
 * Time: O(\log N)
 * Source: 
	* http://codeforces.com/blog/entry/18051
	* KACTL
 */

template<typename T, int SZ> struct SegTree {
	vector<T> seg; T id;
	T (*cmb) (T, T);
	SegTree(T _id, T _cmb(T, T)):id(_id),seg(2*SZ,id),cmb(_cmb){}
	void build() {for (int i=SZ-1; i >= 0; i--) seg[i]=cmb(seg[2*i],seg[2*i+1]);}
	T query(int l, int r, int s=0, int e=SZ-1, int c=1) {
		if (l > e || r < s) return id;
		if (l <= s && r >= e) return seg[c];
		int mid = (s + e) / 2;
		return cmb(query(l,r, s, mid, 2*c),
			query(l, r, mid + 1, e, 2*c+1));
	}
	void update(int i, T x, int s=0, int e=SZ-1, int c=1) {
		if (s > i || e < i) return;
		if (s == e) {seg[c] = x; return;}
		int mid = (s + e) / 2;
		update(i, x, s, mid, 2*c);
		update(i, x, mid + 1, e, 2*c+1);
		seg[c] = cmb(seg[2*c], seg[2*c+1]);
	}
};
