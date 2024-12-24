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
    map<int, pair<int, int>> compress;
    // add log2(Q) is storage needed after some update query
    int L[LN * N], R[LN * N], S[LN * N];
    long long KS[LN * N];
    int NEXT_FREE_INDEX = 1;
    int roots[N];
    int MX;
 
    PersistentSegTree(int v[], int n) : MX(n)
    {
        int tl = 0, tr = n;
        pair<int, int> sort_v[n];
        for (int i = 0; i < n; i++)
            sort_v[i] = {v[i], i};
        sort(sort_v, sort_v + n, greater<pair<int, int>>());
        int idx[n];
        for (int i = 0; i < n; i++)
            compress[i] = sort_v[i], idx[sort_v[i].second] = i;
        roots[0] = build(tl, tr);
        for (int i = 0; i < n; i++)
            roots[i + 1] = update(roots[i], tl, tr, idx[i]);
    }
    int new_vertex(int s, int ks, int l, int r)
    {
        S[NEXT_FREE_INDEX] = s;
        KS[NEXT_FREE_INDEX] = ks;
        L[NEXT_FREE_INDEX] = l;
        R[NEXT_FREE_INDEX] = r;
        return NEXT_FREE_INDEX++;
    }
 
    int new_vertex(int l, int r)
    {
        S[NEXT_FREE_INDEX] = S[l] + S[r];
        KS[NEXT_FREE_INDEX] = KS[l] + KS[r];
        L[NEXT_FREE_INDEX] = l;
        R[NEXT_FREE_INDEX] = r;
        return NEXT_FREE_INDEX++;
    }
 
    int build(int tl, int tr)
    {
        if (tl == tr)
            return new_vertex(0, 0, -1, -1);
        int tm = (tl + tr) / 2;
        return new_vertex(build(tl, tm), build(tm + 1, tr));
    }
    int update(int idx, int tl, int tr, int pos)
    {
        if (tl == tr)
            return new_vertex(S[idx] + 1, KS[idx] + compress[pos].first, -1, -1);
        int tm = (tl + tr) / 2;
        if (pos <= tm)
            return new_vertex(update(L[idx], tl, tm, pos), R[idx]);
        else
            return new_vertex(L[idx], update(R[idx], tm + 1, tr, pos));
    }
 
    long long find_kth(int vl, int vr, int tl, int tr, int k)
    {
        if (tl == tr)
            return KS[vr] - KS[vl];
        int tm = (tl + tr) / 2;
        int left_count = S[L[vr]] - S[L[vl]];
        if (left_count >= k)
            return find_kth(L[vl], L[vr], tl, tm, k);
        return KS[L[vr]] - KS[L[vl]] + find_kth(R[vl], R[vr], tm + 1, tr, k - left_count);
    }
 
    long long find_kth(int l, int r, int k)
    {
        return find_kth(roots[l], roots[r], 0, MX, k);
    }
};
