#include <iostream>
#include <vector>
#include <list>

using namespace std;

class MyHashSet {

private:
	vector<list<int>> hashset;
	static const int base = 797;

	int hash(int num) {
		return num % base;
	}

public:
	MyHashSet():hashset(base) {

	}

	void add(int key) {
		int index = hash(key);
		for (auto it = hashset[index].begin(); it != hashset[index].end(); ++it)
		{
			if (*it == key)
			{
				return;
			}
		}
		hashset[index].emplace_back(key);
	}

	void remove(int key) {
		int index = hash(key);
		for (auto it = hashset[index].begin(); it != hashset[index].end(); ++it)
		{
			if (*it == key)
			{
				hashset[index].remove(key);
				return;
			}
		}
	}

	bool contains(int key) {
		int index = hash(key);
		for (auto it = hashset[index].begin(); it != hashset[index].end(); ++it)
		{
			if (*it == key)
			{
				return true;
			}
		}
		return false;
	}
};