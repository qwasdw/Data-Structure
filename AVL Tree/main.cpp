#include <iostream>
#include <stack>
#include <queue>

using namespace std;

struct Node {
	int value;
	int height;
	Node* left;
	Node* right;

	Node(int _value) : value(_value), height(1), left(nullptr), right(nullptr) {

	}
};

class AVLTree {
private:
	Node* root;
	int node_nums;

public:
	AVLTree() : node_nums(0), root(nullptr) {

	}

	void inertion(int value) {
		if (root == nullptr) {
			root = new Node(value);
			++node_nums;
			return;
		}
		stack<Node**> st;
		Node** node = &root;
		while (*node != nullptr) {
			st.push(node);
			if ((*node)->value > value) {
				node = &(*node)->left;
			}
			else if ((*node)->value < value) {
				node = &(*node)->right;
			}
			else {
				cout << "Exist a node's value equals to " << value << "." << endl;
				return;
			}
		}
		++node_nums;
		*node = new Node(value);
		while (!st.empty()) {
			Node** p = st.top();
			st.pop();
			(*p)->height = max(getHeight((*p)->left), getHeight((*p)->right)) + 1;
			rebalance(*p);
		}
	}

	void deletion(int value) {
		if (root == nullptr) {
			cout << "Tree is empty!" << endl;
			return;
		}
		bool exist = false;
		stack<Node**> st;
		Node** node = &root;
		while ((*node) != nullptr) {
			if ((*node)->value > value) {
				st.push(node);
				node = &(*node)->left;
			}
			else if ((*node)->value < value) {
				st.push(node);
				node = &(*node)->right;
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
		if ((*node)->left != nullptr) {
			st.push(node);
			while ((*node)->left != nullptr) {
				Node* predsor = (*node)->left;
				while (predsor->right != nullptr) {
					st.push(&predsor);
					predsor = predsor->right;
				}
				(*node)->value = predsor->value;
				node = &predsor;
			}
		}
		else if ((*node)->right != nullptr) {
			st.push(node);
			while ((*node)->right != nullptr) {
				Node* sucsor = (*node)->right;
				while (sucsor->left != nullptr) {
					st.push(&sucsor);
					sucsor = sucsor->left;
				}
				(*node)->value = sucsor->value;
				node = &sucsor;
			}
		}
		if (st.empty()) {
			delete (*node);
			root = nullptr;
			return;
		}
		Node* t = *(st.top());
		if (t->left == (*node)) {
			t->left = nullptr;
		}
		else {
			t->right = nullptr;
		}
		delete (*node);
		--node_nums;
		while (!st.empty()) {
			Node** p = st.top();
			st.pop();
			(*p)->height = max(getHeight((*p)->left), getHeight((*p)->right)) + 1;
			rebalance(*p);
		}
	}

	int getHeight(Node* node) {
		return node == nullptr ? 0 : node->height;
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

private:

	void leftRotation(Node*& node) {
		Node* right_child = node->right;
		node->right = right_child->left;
		right_child->left = node;
		node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
		right_child->height = max(node->height, getHeight(right_child->right)) + 1;
		node = right_child;
	}

	void rightRotation(Node*& node) {
		Node* left_child = node->left;
		node->left = left_child->right;
		left_child->right = node;
		node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
		left_child->height = max(getHeight(left_child->left), node->height) + 1;
		node = left_child;
	}

	void rebalance(Node*& node) {
		int diff = getHeight(node->left) - getHeight(node->right);
		if (diff > 1) {
			if (getHeight(node->left->left) < getHeight(node->left->right)) {
				leftRotation(node->left);
			}
			rightRotation(node);
		}
		else if (diff < -1) {
			if (getHeight(node->right->left) > getHeight(node->right->right)) {
				rightRotation(node->right);
			}
			leftRotation(node);
		}
	}

};

int main() {

	AVLTree tree;
	for (int i = 0; i < 10; ++i) {
		tree.inertion(i);
		tree.print();
	}
	cout << "--------------------------" << endl;
	for (int i = 0; i < 10; ++i) {
		tree.deletion(i);
		tree.print();
	}
	return 0;
}