/**
 * Author: Subham Pan
 * Description: 1D point update and range query where \texttt{cmb} is
 	* any associative operation. \texttt{seg[1]==query(0,N-1)}.
 * Time: O(\log N)
 */

template<typename T> struct SegTreeRecursive {
    vector<T> seg; T id; T (*cmb) (T, T); int SZ;
    SegTreeRecursive(int _n, T _id, T _cmb(T, T)):SZ(_n),id(_id),cmb(_cmb){seg.assign(4*SZ+1, id);}
    void build() {for (int i=SZ-1; i >= 0; i--) seg[i]=cmb(seg[2*i],seg[2*i+1]);}
    T query(int l, int r) {return query(l,r,0,SZ-1,1);}
    T query(int l, int r, int s, int e, int c) {
        if (l > e || r < s) return id;
        if (l <= s && r >= e) return seg[c];
        int mid = (s + e) / 2;
        return cmb(query(l,r, s, mid, 2*c),
        query(l, r, mid + 1, e, 2*c+1));
    }
    void upd(int i, T x) {upd(i,x,0,SZ-1,1);}
    void upd(int i, T x, int s, int e, int c) {
        if (s > i || e < i) return;
        if (s == e) {seg[c] = x; return;}
        int mid = (s + e) / 2;
        upd(i, x, s, mid, 2*c);
        upd(i, x, mid + 1, e, 2*c+1);
        seg[c] = cmb(seg[2*c], seg[2*c+1]);
    }
    T kth_one_end(int k) {return kth_one_end(k,0,SZ-1,1);}
    T kth_one_end(int k, int s, int e, int c) {
        if(seg[c] < k) { return -1; }      
        if(s == e) { return s; }
        int mid = (s+e)/2;
        if(seg[2*c] >= k) {// descend into right subtree
            return kth_one_end(k, s, mid, 2*c);} 
        else {return kth_one_end(k - seg[2*c], mid+1, e, 2*c+1);}
    }
};
