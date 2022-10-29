#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

#define RR  0
#define LL  1
#define RL  2
#define LR  3
#define R0  4
#define R1  5
#define R_1 6
#define L0  7
#define L1  8
#define L_1 9

struct Node {
	int val;
	int treeHeight;
	Node* left;
	Node* right;
	Node* parent;

	Node() {
		this->val = 0;
		this->treeHeight = 0;
		this->left = nullptr;
		this->right = nullptr;
		this->parent = nullptr;
	}

	Node(int val) {
		this->val = val;
		this->treeHeight = 0;
		this->left = nullptr;
		this->right = nullptr;
		this->parent = nullptr;
	}
};

class AVLTree {
	vector<int> rotationType;
	vector<int> Ans;
	int getTreeHeight(Node*& curr) {
		if (curr == nullptr) return -1;
		int leftH = (curr->left == nullptr) ? -1 : (curr->left->treeHeight);
		int rightH = (curr->right == nullptr) ? -1 : (curr->right->treeHeight);
		return max(leftH, rightH) + 1;
	}
	int getHeightDifference(Node*& curr) {
		if (curr == nullptr) return 0;
		int leftH = getTreeHeight(curr->left);
		int rightH = getTreeHeight(curr->right);
		return leftH - rightH;
	}
	void adjustTree(Node*& curr, bool deleting = false) {
		int diffHeight = getHeightDifference(curr);
		if (deleting) {
			if (diffHeight > 1) {
				int diff = getHeightDifference(curr->left);
				if (diff > 0) Rotation(curr, L1);
				else if(diff == 0)Rotation(curr, L0);
				else Rotation(curr, L_1);
			}
			else if (diffHeight < -1) {
				int diff = getHeightDifference(curr->right);
				if (diff > 0) Rotation(curr, R1);
				else if (diff == 0)Rotation(curr, R0);
				else Rotation(curr, R_1);
			}
		}
		else {
			if (diffHeight > 1) {
				if (getHeightDifference(curr->left) > 0) Rotation(curr, LL);
				else Rotation(curr, LR);
			}
			else if (diffHeight < -1) {
				if (getHeightDifference(curr->right) <= 0) Rotation(curr, RR);
				else Rotation(curr, RL);
			}
		}
	}
	void Rotation(Node* curr, int type) {
		this->rotationType.push_back(type);

		Node *mid = nullptr, *last = nullptr, *currParent = curr->parent;
		bool left = true;
		if (currParent != nullptr && currParent->right == curr) left = false;

		if (type == RR) {
			mid = curr->right;
			last = mid->right;
			curr->right = mid->left;
			mid->left = curr;

			if(curr->right) curr->right->parent = curr;
		}
		else if (type == LL) {
			mid = curr->left;
			last = mid->left;
			curr->left = mid->right;
			mid->right = curr;

			if (curr->left) curr->left->parent = curr;
		}
		else if (type == RL) {
			mid = curr->right->left;
			last = curr->right;
			curr->right = mid->left;
			last->left = mid->right;
			mid->right = last;
			mid->left = curr;

			if (curr->right) curr->right->parent = curr;
			if (last->left) last->left->parent = last;
		}
		else if (type == LR) {
			mid = curr->left->right;
			last = curr->left;
			curr->left = mid->right;
			last->right = mid->left;
			mid->right = curr;
			mid->left = last;

			if (curr->left) curr->left->parent = curr;
			if (last->right) last->right->parent = last;
		}
		// RR
		else if (type == R0) {
			mid = curr->right;
			last = mid->right;
			curr->right = mid->left;
			mid->left = curr;

			if (curr->right) curr->right->parent = curr;
		}
		// RL
		else if (type == R1) {
			mid = curr->right->left;
			last = curr->right;
			curr->right = mid->left;
			last->left = mid->right;
			mid->right = last;
			mid->left = curr;

			if (curr->right) curr->right->parent = curr;
			if (last->left) last->left->parent = last;
		}
		// RR
		else if (type == R_1) {
			mid = curr->right;
			last = mid->right;
			curr->right = mid->left;
			mid->left = curr;

			if (curr->right) curr->right->parent = curr;
		}
		// LL
		else if (type == L0) {
			mid = curr->left;
			last = mid->left;
			curr->left = mid->right;
			mid->right = curr;

			if (curr->left) curr->left->parent = curr;
		}
		// LL
		else if (type == L1) {
			mid = curr->left;
			last = mid->left;
			curr->left = mid->right;
			mid->right = curr;

			if (curr->left) curr->left->parent = curr;
		}
		// LR
		else if (type == L_1) {
			mid = curr->left->right;
			last = curr->left;
			curr->left = mid->right;
			last->right = mid->left;
			mid->right = curr;
			mid->left = last;

			if (curr->left) curr->left->parent = curr;
			if (last->right) last->right->parent = last;
		}

		if (currParent != nullptr) {
			if (left) currParent->left = mid;
			else currParent->right = mid;
		}
		else {
			this->root = mid;
		}
		mid->parent = currParent;
		curr->parent = mid;
		last->parent = mid;

		curr->treeHeight = getTreeHeight(curr);
		last->treeHeight = getTreeHeight(last);
		mid->treeHeight = getTreeHeight(mid);
	}

	Node* searchNode(Node* curr, const int& val, bool& finish, vector<Node*>& path) {
		if (curr == nullptr || finish) return curr;
		Node* temp;
		if (curr->val < val) {
			path.push_back(curr);
			temp = searchNode(curr->right, val, finish, path);
		}
		else if (curr->val > val) {
			path.push_back(curr);
			temp = searchNode(curr->left, val, finish, path);
		}
		else {
			finish = true;
			temp = curr;
		}
		return temp;
	}
public:
	Node* root;
	AVLTree() { this->root = nullptr; }
	~AVLTree() { traceNode(root, true); }

	void printRotation() {
		cout << this->rotationType.size() << '\n';
		for (int i = 0; i < this->rotationType.size(); i++) {
			switch (this->rotationType[i])
			{
			case LL: cout << "LL"; break;
			case RR: cout << "RR"; break;
			case RL: cout << "RL"; break;
			case LR: cout << "LR"; break;
			case R0: case L0: cout << "R0"; break;
			case R1: case L1: cout << "R1"; break;
			case R_1: case L_1: cout << "R-1"; break;
			default:
				break;
			}
			if (i != this->rotationType.size() - 1) cout << ',';
		}
	}

	void insert(Node*& curr, const int& val) {
		if (curr == nullptr) {
			curr = new Node(val);
			return;
		}
		else {
			if (val > curr->val) {
				if (curr->right == nullptr) {
					Node* newNode = new Node(val);
					curr->right = newNode;
					newNode->parent = curr;
				}
				else {
					insert(curr->right, val);
				}
			}
			else if (val < curr->val) {
				if (curr->left == nullptr) {
					Node* newNode = new Node(val);
					curr->left = newNode;
					newNode->parent = curr;

				}
				else {
					insert(curr->left, val);
				}
			}
			else {
				cout << "number exist.\n";
				return;
			}
			
			curr->treeHeight = getTreeHeight(curr);
			adjustTree(curr);
		}

	}

	void printInorder() {
		this->Ans.clear();
		traceNode(this->root);

		for (int i = 0; i < this->Ans.size(); i++) {
			cout << this->Ans[i];
			if (i != this->Ans.size() - 1) cout << ' ';
			else cout << '\n';
		}
	}

	void del(Node* curr, const int& val) {
		bool finish = false;
		bool left = true;
		vector<Node*> path;
		curr = searchNode(curr, val, finish, path);
		if (curr->parent && curr->parent->right == curr) left = false;

		if (curr->left == nullptr) {
			if (left) {
				curr->parent->left = curr->right;
				if (curr->right) curr->right->parent = curr->parent->left;
			}
			else { 
				curr->parent->right = curr->right;
				if (curr->right) curr->right->parent = curr->parent->right;
			}
			delete curr;
		}
		else if (curr->right == nullptr) {
			if (left) {
				curr->parent->left = curr->left;
				if (curr->left) curr->left->parent = curr->parent->left;
			}
			else {
				curr->parent->right = curr->left;
				if (curr->left) curr->left->parent = curr->parent->right;
			}
			delete curr;
		}
		else {
			Node* temp = curr->left;
			path.push_back(curr);
			for (; temp->right != nullptr; temp = temp->right) {
				if(temp->right->right) path.push_back(temp);
			}
			swap(curr->val, temp->val);
			if (temp->parent == curr) {
				curr->left = temp->left;
				if (temp->left) temp->left->parent = curr->left;
			}
			else {
				temp->parent->right = temp->left;
				if (temp->left) temp->left->parent = temp->parent->right;
			}
			delete temp;
		}

		for (int i = path.size()-1; i >= 0; i--) {
			path[i]->treeHeight = getTreeHeight(path[i]);
			adjustTree(path[i], true);
		}
	}

	void traceNode(Node* curr, bool deleting = false) {
		if (curr == nullptr) return;

		traceNode(curr->left, deleting);

		if (deleting) {
			traceNode(curr->right, deleting);
			delete curr;
		}
		else {
			Ans.push_back(curr->val);
			traceNode(curr->right, deleting);
		}
	}

};

int main() {
	string str;
	getline(cin, str);
	stringstream ss(str);
	
	int num = 0;
	AVLTree tree;
	
	for (; getline(ss, str, ',');) {
		num = stoi(str);
		tree.insert(tree.root, num);
	}

	for (; cin >> str >> num;) {
		if (str == "I") {
			tree.insert(tree.root, num);
		}
		else if (str == "D") {
			tree.del(tree.root, num);
		}
	}

	tree.printInorder();
	tree.printRotation();
}