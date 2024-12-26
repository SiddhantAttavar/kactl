/**
 * Author: Lucian Bicsi
 * Date: 2017-10-31
 * License: CC0
 * Source: folklore
 * Description: Persistent SegTree
 * Time: O(\log N)
 * Status: stress-tested
 */
#pragma once

struct PersistentSegTree
{ // Returns the sum of K largest elements in [l, r)
    map<int,pii> cp;
    // add log2(Q) is storage needed after some update query
    int L[LN*N],R[LN*N],S[LN*N]; long long KS[LN*N];
    int SZ = 1, roots[N], MX;
    PersistentSegTree(int v[], int n) : MX(n) {
        int tl = 0, tr = n, idx[n];pii sort_v[n];
        rep(i, 0, n) sort_v[i] = {v[i], i};
        sort(sort_v, sort_v+n, greater<pii>());
        rep(i,0,n)cp[i]=sort_v[i],idx[sort_v[i].second]=i;
        roots[0] = build(tl, tr);
        rep(i,0,n)roots[i+1]=update(roots[i],tl,tr,idx[i]);
    }
    int ver(int s, int ks, int l, int r) {
        S[SZ]=s;KS[SZ]=ks;L[SZ]=l;R[SZ]=r;return SZ++;
    }
    int ver(int l, int r) {
        S[SZ]=S[l]+S[r];KS[SZ]=KS[l]+KS[r];
        L[SZ]=l;R[SZ]=r;return SZ++;
    }
    int build(int tl, int tr){
        if (tl == tr) return ver(0, 0, -1, -1);
        int tm = (tl+tr)/2;
        return ver(build(tl, tm),build(tm + 1, tr));
    }
    int update(int idx, int tl, int tr, int pos){
        if (tl == tr)
            return ver(S[idx]+1,KS[idx]+cp[pos].first,-1,-1);
        int tm = (tl + tr) / 2;
        if (pos <= tm)
        return ver(update(L[idx],tl,tm,pos),R[idx]);
        return ver(L[idx],update(R[idx],tm+1,tr,pos));
    }
    long long kth(int vl, int vr, int tl, int tr, int k) {
        if (tl == tr) return KS[vr]-KS[vl];
        int tm = (tl+tr)/2,lc=S[L[vr]]-S[L[vl]];
        if (lc >= k)return kth(L[vl], L[vr], tl, tm, k);
        return KS[L[vr]]-KS[L[vl]]+kth(R[vl], 
            R[vr],tm+1,tr,k-lc);
    }
    long long kth(int l, int r, int k) {
        return kth(roots[l], roots[r], 0, MX, k);
    }
};
