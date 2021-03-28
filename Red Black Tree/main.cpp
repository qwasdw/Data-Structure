#include <iostream>
#include <set>
#include <queue>

using namespace std;

struct Node {
	int color;	// 0 Red 1 Black
	int value;
	Node* parent;
	Node* left;
	Node* right;

	Node(int _value): value(_value), color(0), parent(nullptr), left(nullptr), right(nullptr) {

	}
};

class RedBlackTree {
private:
	Node* root;
	int node_nums;

public:
	RedBlackTree() : root(nullptr), node_nums(0) {

	}

	void insertion(int value) {					// Insert a node to Red Black Tree
		Node* parent = nullptr;					// Insert node's color is Red
		Node* next = root;
		Node* node = new Node(value);
		while (next != nullptr) {				// Find the place to insert the node
			parent = next;
			if (next->value > value) {
				next = next->left;
			}
			else if (next->value < value){
				next = next->right;
			}
			else {
				return;
			}
		}
		++node_nums;

		node->parent = parent;
		if (parent == nullptr) {				// Red Black Tree is empty
			root = node;
			root->color = 1;
			return;
		}
		else if (parent->value > value) {	
			parent->left = node;
		}
		else if (parent->value < value) {
			parent->right = node;
		}
		insertFixUp(node);						// Re-balancing the tree
	}

	void deletion(int value) {
		Node* node = find(value);
		if (node == nullptr) {
			cout << "Not exist a node which value equals to " << value << "." << endl;
			return;
		}
		while (node->left != nullptr || node->right != nullptr) {		// Find deleted node's successor and switch the value
			Node* sucsor = successor(node);								// Let successor node become the deleted node
			node->value = sucsor->value;								// Until node is a leaf node
			node = sucsor;
		}
		Node* parent = node->parent;
		if (node != root) {												// Deleted node is not root
			if (node->color == 1) {										// Deleted node's color is black
				deleteFixUp(node, parent);								// Re-balancing the tree
			}
			else {														// Deleted node's color is red, direct delete it
				if (node == parent->left) {
					parent->left = nullptr;
				}
				else {
					parent->right = nullptr;
				}
			}
		}
		else {
			root = nullptr;												// Deleted node is root
		}

		--node_nums;
		delete node;
	}

	Node* find(int value) {			// Find the node which value equals to value
		Node* node = root;
		while (node != nullptr && node->value != value) {
			if (node->value > value) {
				node = node->left;
			}
			else {
				node = node->right;
			}
		}
		return node;
	}

	void print() {					// Print the tree
		queue<Node*> q;
		if (root == nullptr) {
			cout << "Red Black Tree is empty!" << endl;
			return;
		}
		q.push(root);
		while (!q.empty()) {
			queue<Node*> temp;
			int count = 0;
			while (!q.empty()) {
				Node* node = q.front();
				q.pop();
				if (node == nullptr) {
					cout << " null ";
					continue;
				}
				++count;
				cout << node->value << "-" << node->color << "  ";
				temp.push(node->left);
				temp.push(node->right);
			}
			q = temp;
			cout << endl;
			if (count == 0) {
				break;
			}
		}
		cout << "Print done!" << endl;
		cout << endl;
	}

private:
	Node* predecessor(Node* _node) {							// Find a node's predecessor
		Node* node = _node->left;
		while (node != nullptr && node->right != nullptr) {
			node = node->right;
		}
		return node;
	}

	Node* successor(Node* _node) {								// Find a node's successor
		Node* node = _node->right;
		while (node != nullptr && node->left != nullptr) {
			node = node->left;
		}
		return node;
	}

	void leftRotation(Node*& parent) {							
		Node* right_child = parent->right;
		Node* child_left = right_child->left;
		parent->right = right_child->left;
		right_child->left = parent;
		right_child->parent = parent->parent;
		parent->parent = right_child;
		if (child_left) {
			child_left->parent = parent;
		}
		parent = right_child;
		if (parent->parent == nullptr) {
			root = parent;
		}
		else if (parent->parent->value > parent->value) {
			parent->parent->left = parent;
		}
		else if (parent->parent->value < parent->value){
			parent->parent->right = parent;
		}
	}

	void rightRotation(Node*& parent) {
		Node* left_child = parent->left;
		Node* child_right = left_child->right;
		parent->left = child_right;
		left_child->right = parent;
		left_child->parent = parent->parent;
		parent->parent = left_child;
		if (child_right) {
			child_right->parent = parent;
		}
		parent = left_child;
		if (parent->parent == nullptr) {
			root = parent;
		}
		else if (parent->parent->value > parent->value) {
			parent->parent->left = parent;
		}
		else if (parent->parent->value < parent->value) {
			parent->parent->right = parent;
		}
	}

	void insertFixUp(Node* node) {
		while (node != root && node->parent->color == 0 && node->parent->parent != nullptr) {
			Node* parent = node->parent;
			Node* grand_parent = node->parent->parent;
			Node* uncle = nullptr;
			if (parent == grand_parent->left) {
				uncle = grand_parent->right;
				if (uncle != nullptr && uncle->color == 0) {				// Uncle node's color is Red
					uncle->color = 1;										// Just Change the parent and uncle node's color to Black,
					parent->color = 1;										// and grand parent color to Red
					grand_parent->color = 0;
					node = grand_parent;
				}
				else {														// Uncle node is null or color is Black
					if (node == parent->right) {							// If node on the right, rotate to the left
						leftRotation(parent);				
					}
					parent->color = 1;										// Change parent node color to Black and grand parent color to red
					grand_parent->color = 0;
					rightRotation(grand_parent);							// Rotate grand parent to the right
					break;
				}
			}
			else {															// Mirror to above
				uncle = grand_parent->left;
				if (uncle != nullptr && uncle->color == 0) {
					uncle->color = 1;
					parent->color = 1;
					grand_parent->color = 0;
					node = grand_parent;
				}
				else {
					if (node == parent->left) {
						rightRotation(parent);
					}
					parent->color = 1;
					grand_parent->color = 0;
					leftRotation(grand_parent);
					break;
				}
			}
		}
		root->color = 1;													// Root node must be Black
	}

	void deleteFixUp(Node*& _node, Node*& parent) {
		bool double_black = true;						// Means not balance
		Node* node = _node;
		if (node == parent->left) {
			parent->left = nullptr;
		}
		else {
			parent->right = nullptr;
		}
		node = nullptr;
		while (double_black && node != root && parent != nullptr) {
			Node* sibling = nullptr;
			if (node == parent->left) {
				sibling = parent->right;
				if (sibling == nullptr) {				// Sibling is null
					if (parent->color == 0) {			// Parent color is Red
						parent->color = 1;				// Change parent color to Black
						double_black = false;			// Tree is balance now
					}
					else {								// Parent color is Black
						node = parent;					// Parent become a DB node
						parent = parent->parent;
					}
				}
				else if (sibling->color == 0) {			// Sibling's color is Red
					parent->color = 0;					// Change parent color to Red
					sibling->color = 1;					// Change sibling's color to Black
					leftRotation(parent);				// Rotate parent, but parent position is changed
					parent = parent->left;				// Back to the correct postion
				}
				else {									// Sibling's color is Black
					Node* sibling_left_child = sibling->left;
					Node* sibling_right_child = sibling->right;
					if (sibling_left_child != nullptr && sibling_left_child->color == 0) {			// Sibling's left child color is Red
						sibling->color = 0;															// Change sibling's color to Black
						sibling_left_child->color = 1;												// Change sibling left child's color to Black
						rightRotation(sibling);														// Rotate sibling
					}
					else if (sibling_right_child != nullptr && sibling_right_child->color == 0) {		// Sibling's right child color is Red
						int temp = sibling->color;														// Change sibling right child's color to Black
						sibling->color = parent->color;													// Switch parent and sibling's color
						parent->color = temp;															// Rotate parent
						sibling_right_child->color = 1;													// Tree is balance now
						leftRotation(parent);
						double_black = false;
					}
					else {								// Sibling's both child color is Black
						if (parent->color == 0) {		// Parent color is red
							parent->color = 1;			// Change parent color to Black, sibling's color to Red
							sibling->color = 0;			// Tree is balance now
							double_black = false;
						}
						else {							// Parent color is Black
							sibling->color = 0;			// Sibling's color is Red
							node = parent;				// Parent become a DB node
							parent = parent->parent;
						}
					}
				}
			}
			else {										// Mirror to above
				sibling = parent->left;
				if (sibling == nullptr) {				
					if (parent->color == 0) {
						parent->color = 1;
						double_black = false;
					}
					else {
						node = parent;
						parent = parent->parent;
					}
				}
				else if (sibling->color == 0) {			
					parent->color = 0;
					sibling->color = 1;
					rightRotation(parent);
					parent = parent->right;
				}
				else {									
					Node* sibling_left_child = sibling->left;
					Node* sibling_right_child = sibling->right;
					if (sibling_left_child != nullptr && sibling_left_child->color == 0) {			// Sibling's left child is red
						int temp = sibling->color;
						sibling->color = parent->color;
						parent->color = temp;
						sibling_left_child->color = 1;
						rightRotation(parent);
						double_black = false;
					}
					else if (sibling_right_child != nullptr && sibling_right_child->color == 0) {		// Sibling's right child is red

						sibling->color = 0;
						sibling_right_child->color = 1;
						leftRotation(sibling);

					}
					else {								
						if (parent->color == 0) {		
							parent->color = 1;
							sibling->color = 0;
							double_black = false;
						}
						else {							
							sibling->color = 0;
							node = parent;
							parent = parent->parent;
						}
					}
				}
			}
		}
		if (root != nullptr) {
			root->color = 1;		// Root node must be Black
		}
	}
};



int main() {
	int a[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	RedBlackTree RBT;
	for (int num : a) {
		RBT.insertion(num);
		RBT.print();
	}
	for (int num : a) {
		RBT.deletion(num);
		RBT.print();
	}

	return 0;
}