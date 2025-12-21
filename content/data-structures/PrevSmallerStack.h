/**
 * Author: Subham Pan
 * Date: 2025-12-21
 * Description: pre stores the nearest prev index that had a strictly smaller element
 * suf stores the nearest next index that has a strictly smaller element.
 * Time: O(N)
 */

#pragma once

auto prev_smaller = [&](vector<ll>& b) -> vector<ll> {
    ll N = sz(b);vi ans(N, 0);vector<array<ll, 2>> Stk;
    for(ll i = 0; i < N; i++) {
        while(!Stk.empty() && Stk.back()[1] >= b[i]) {
            Stk.pop_back();
        }
        if(Stk.empty()) {ans[i] = 0;} 
        else {ans[i] = Stk.back()[0];}
        Stk.push_back({i+1, b[i]});
    }
    return ans;
};
auto pre = prev_smaller(a);
auto ac = a; reverse(all(ac)); auto suf = prev_smaller(ac);
reverse(all(suf));for(auto &x : suf) {x = n + 1 - x;}
