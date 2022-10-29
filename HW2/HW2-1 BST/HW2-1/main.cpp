#include <iostream>
#include <vector>

#define Inorder 0
#define Preorder 1
#define Postorder 2

using namespace std;

vector<int> Ans;

struct Node {
	int val;
	Node* left;
	Node* right;

	Node() {
		this->val = 0;
		this->left = nullptr;
		this->right = nullptr;
	}

	Node(int val) {
		this->val = val;
		this->left = nullptr;
		this->right = nullptr;
	}
};

class BST {
public:
	Node* root;
	BST() { this->root = nullptr; }
	~BST() { traceNode(root, Inorder, true); }

	void insert(int val) {
		Node* newNode = new Node(val);
		if (this->root == nullptr) {
			this->root = newNode;
			return;
		}

		for (Node* temp = this->root;;) {
			if (val > temp->val) {
				if (temp->right == nullptr) {
					temp->right = newNode;
					return;
				}
				else {
					temp = temp->right;
				}
			}
			else {
				if (temp->left == nullptr) {
					temp->left = newNode;
					return;
				}
				else {
					temp = temp->left;
				}
			}

		}
	}

	void traceNode(Node* curr, int order, bool deleting = false) {
		if (curr == nullptr) return;

		if (order == Preorder && !deleting) Ans.push_back(curr->val);

		traceNode(curr->left, order, deleting);

		if (deleting) {
			traceNode(curr->right, order, deleting);
			delete curr;
		}
		else {
			if (order == Inorder) Ans.push_back(curr->val);
			traceNode(curr->right, order, deleting);
			if (order == Postorder) Ans.push_back(curr->val);
		}
	}
};

int main() {

	int num = 0;
	BST tree;
	for (; cin >> num;) {
		tree.insert(num);
	}
	
	tree.traceNode(tree.root, Inorder);
	for (int i = 0; i < Ans.size(); i++) {
		cout << Ans[i];
		if (i != Ans.size() - 1) cout << ' ';
	}
	cout << '\n';
	Ans.clear();

	tree.traceNode(tree.root, Preorder);
	for (int i = 0; i < Ans.size(); i++) {
		cout << Ans[i];
		if (i != Ans.size() - 1) cout << ' ';
	}
	cout << '\n';
	Ans.clear();

	tree.traceNode(tree.root, Postorder);
	for (int i = 0; i < Ans.size(); i++) {
		cout << Ans[i];
		if (i != Ans.size() - 1) cout << ' ';
	}
	Ans.clear();
}