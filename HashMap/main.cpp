#include <iostream>
#include <vector>
#include <list>

using namespace std;

class MyHashMap {
private:
	vector<list<pair<int, int>>> hashmap;
	static const int base = 797;

	int hash(int key) {
		return key % base;
	}

public:
	MyHashMap() : hashmap(base) {

	}

	void put(int key, int value) {
		int index = hash(key);
		for (auto it = hashmap[index].begin(); it != hashmap[index].end(); ++it)
		{
			if ((*it).first == key)
			{
				(*it).second = value;
				return;
			}
		}
		hashmap[index].emplace_back(key, value);
	}

	int get(int key) {
		int index = hash(key);
		for (auto it = hashmap[index].begin(); it != hashmap[index].end(); ++it)
		{
			if ((*it).first == key)
			{
				return (*it).second;
			}
		}
		return -1;
	}

	void remove(int key) {
		int index = hash(key);
		for (auto it = hashmap[index].begin(); it != hashmap[index].end(); ++it)
		{
			if ((*it).first == key)
			{
				hashmap[index].remove(*it);
				return;
			}
		}
	}
};