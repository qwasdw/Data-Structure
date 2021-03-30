#include <iostream>
#include <queue>

using namespace std;

struct Node
{
	int value;
	Node* left;
	Node* right;

	Node(int _value): value(_value), left(nullptr), right(nullptr) {

	}
};

class BinarySearchTree {
private:
	Node* root;
	int node_nums;

public:
	BinarySearchTree() : root(nullptr), node_nums(0) {

	}

	void insertion(int value) {
		if (root == nullptr) {
			root = new Node(value);
			++node_nums;
			return;
		}
		Node* pre = root;
		Node* cur = root;
		while (cur != nullptr) {
			pre = cur;
			if (cur->value > value) {
				cur = cur->left;
			}
			else if (cur->value < value) {
				cur = cur->right;
			}
			else {
				cout << "Exist a node's value equals to " << value << "!" << endl;
				return;
			}
		}
		Node* node = new Node(value);
		if (pre->value > value) {
			pre->left = node;
		}
		else {
			pre->right = node;
		}
		++node_nums;
	}

	void deletion(int value) {
		bool exist = false;
		Node* pre = root;
		Node* node = root;
		while (node != nullptr) {
			if (node->value > value) {
				pre = node;
				node = node->left;
			}
			else if (node->value < value) {
				pre = node;
				node = node->right;
			}
			else {
				exist = true;
				break;
			}
		}
		if (!exist) {
			cout << "Not exist a node's value equals to " << value << "!" << endl;
			return;
		}
		--node_nums;
		while (node->left != nullptr) {
			pre = node;
			Node* predecessor = node->left;
			while (predecessor->right != nullptr) {
				pre = predecessor;
				predecessor = predecessor->right;
			}
			node->value = predecessor->value;
			node = predecessor;
		}
		while (node->right != nullptr) {
			pre = node;
			Node* successor = node->right;
			while (successor->left != nullptr) {
				pre = successor;
				successor = successor->left;
			}
			node->value = successor->value;
			node = successor;
		}
		if (node == root) {
			root = nullptr;
		}
		else if (pre->left == node) {
			pre->left = nullptr;
		}
		else {
			pre->right = nullptr;
		}
		delete node;
	}

	void print() {
		if (root == nullptr) {
			cout << "Tree is empty!" << endl;
			return;
		}
		queue<Node*> q;
		q.push(root);
		while (!q.empty()) {
			queue<Node*> temp;
			Node* node;
			while (!q.empty()) {
				node = q.front();
				q.pop();
				if (node == nullptr) {
					cout << "null ";
					continue;
				}
				cout << node->value << " ";
				temp.push(node->left);
				temp.push(node->right);
			}
			q = temp;
			cout << endl;
		}
		cout << "Print done!" << endl;
	}

};

int main() {

	BinarySearchTree tree;
	int a[] = {4, 2, 6, 1, 3, 5, 7};
	for (int i = 0; i < 7; ++i) {
		tree.insertion(a[i]);
		tree.print();
	}
	cout << "----------------------------" << endl;
	for (int i = 0; i < 7; ++i) {
		tree.deletion(a[i]);
		tree.print();
	}

	return 0;
}