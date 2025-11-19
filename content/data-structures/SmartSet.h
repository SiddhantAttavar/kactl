/**
 * Author: Subham Pan
 * Description: supports insert, erase (just like a normal multiset)
 * but you can also ask for the [sum] of the [smallest / biggest] 'k' elements in the multiset
 * Time: O(\log N)
 * Source: 
	* https://codeforces.com/contest/1936/submission/248919814
*/

template<typename T> struct SmartSet {
	multiset<T> big, small; T sumBig, sumSmall;
	SmartSet() : big(), small(), sumBig(), sumSmall() {}
	int size() const {return sz(small) + sz(big);}
	void normalizeSmall(int k) {
		k = max(0, min(k, size()));
		while(sz(small) > k) {
			auto it = prev(small.end());
			sumSmall -= *it;
			sumBig += *it;
			big.insert(*it);
			small.erase(it);
		}
		while(sz(small) < k) {
			auto it = big.begin();
			sumBig -= *it;
			sumSmall += *it;
			small.insert(*it);
			big.erase(it);
		}
	}
	void insert(T x) {
		if (big.empty() || x < *big.begin()) {
			small.insert(x);
			sumSmall += x;
		} else {
			big.insert(x);
			sumBig += x;
		}
	}
	void erase(T x) {
		if (big.find(x) != big.end()) {
			big.erase(big.find(x));
			sumBig -= x;
		} else if (small.find(x) != small.end()) {
			small.erase(small.find(x));
			sumSmall -= x;
		} else assert(false);
	}
	T getSumSmall(int k) {
		normalizeSmall(k);
		assert(sz(small) == k);
		return sumSmall;
	}
	T getSumBig(int k) {
		normalizeSmall(size() - k);
		assert(sz(big) == k);
		return sumBig;
	}
};
