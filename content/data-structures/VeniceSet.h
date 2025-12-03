/**
 * Author: Shahjalal Shohag
 * Description: supports add, remove, getMin and updateAll
 * which decreases all elements by x
 * Time: O(\log N)
 * Source: https://codeforces.com/blog/entry/58316
*/

struct VeniceSet {
	multiset<int> s; int lvl = 0;
	void add(int v) {s.insert(v + lvl);}
	void remove(int v) {s.erase(s.find(v + lvl));}
	void updateAll(int v) {lvl += v;}
	int getMin() {return *s.begin() - lvl;}
	int size() {return s.size();}
};
