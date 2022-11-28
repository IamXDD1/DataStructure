#include <iostream>
#include <string>
#include <vector>

using namespace std;

#define RED true
#define BLACK false

bool noGame = false;

struct Group {
	vector<int> members;
	vector<pair<int, int>> outfield;
	int jump_ball;
	Group() :jump_ball(0) {};
};

struct Node {
	bool color;
	Node* left;
	Node* right;
	Node* parent;
	int val;
	Node(int num) : color(RED), val(num) {
		this->left = this->right = this->parent = NULL;
	}
};

class RedBlackTree {
	Node* root;
	void rotate(Node* curr) {
		Node* mid = curr->parent, * top = curr->parent->parent, * temp = NULL;
		bool changeRoot = false;
		if (top == this->root) changeRoot = true;

		if (top->left == mid && mid->left == curr) {
			temp = LL(top, mid, curr);
		}
		else if (top->left == mid && mid->right == curr) {
			temp = LR(top, mid, curr);
		}
		else if (top->right == mid && mid->right == curr) {
			temp = RR(top, mid, curr);
		}
		else if (top->right == mid && mid->left == curr) {
			temp = RL(top, mid, curr);
		}
		if (changeRoot) this->root = temp;
		return;
	}
	Node* RR(Node* top, Node* mid, Node* bottom) {
		mid->parent = top->parent;
		if(top->parent != NULL)
			(top->parent->left == top) ? (mid->parent->left = mid) : (mid->parent->right = mid);
		top->parent = mid;
		bottom->parent = mid;
		top->right = mid->left;
		mid->left = top;

		mid->color = BLACK;
		top->color = RED;
		bottom->color = RED;

		return mid;
	}
	Node* LL(Node* top, Node* mid, Node* bottom) {
		mid->parent = top->parent;
		if (top->parent != NULL)
			(top->parent->left == top) ? (top->parent->left = mid) : (top->parent->right = mid);
		bottom->parent = mid;
		top->parent = mid;
		top->left = mid->right;
		mid->right = top;

		mid->color = BLACK;
		top->color = RED;
		bottom->color = RED;

		return mid;
	}
	Node* RL(Node* top, Node* mid, Node* bottom) {
		bottom->parent = top->parent;
		if (top->parent != NULL)
			(top->parent->left == top) ? (top->parent->left = bottom) : (top->parent->right = bottom);
		top->parent = bottom;
		mid->parent = bottom;
		top->right = bottom->left;
		mid->left = bottom->right;
		bottom->left = top;
		bottom->right = mid;

		bottom->color = BLACK;
		top->color = RED;
		mid->color = RED;

		return bottom;
	}
	Node* LR(Node* top, Node* mid, Node* bottom) {
		bottom->parent = top->parent;
		if (top->parent != NULL)
			(top->parent->left == top) ? (top->parent->left = bottom) : (top->parent->right = bottom);
		top->parent = bottom;
		mid->parent = bottom;
		top->left = bottom->right;
		mid->right = bottom->left;
		bottom->left = mid;
		bottom->right = top;

		bottom->color = BLACK;
		top->color = RED;
		mid->color = RED;

		return bottom;
	}
	void trace(Node* curr, int level, Group& teamA, Group& teamB) {
		if (curr == NULL) return;
		trace(curr->left, level + 1, teamA, teamB);

		if (curr->color == RED) {
			teamA.members.push_back(curr->val);
			teamA.outfield.push_back({ level, curr->val });
		}
		else {
			teamB.members.push_back(curr->val);
			teamB.outfield.push_back({ level, curr->val });
		}

		trace(curr->right, level + 1, teamA, teamB);
		return;
	}

	void checkColor(Node* curr) {
		if (curr->right != NULL && curr->left != NULL) {
			if (curr->right->color == RED && curr->left->color == RED) {
				curr->color = RED;
				curr->right->color = curr->left->color = BLACK;
			}
		}

		if (curr->parent != NULL) {
			if (curr->color == RED && curr->parent->color == RED) {
				rotate(curr);
			}
		}
	}

	void insertion(Node* curr, int& num) {
		if (curr == NULL) {
			curr = new Node(num);
			this->root = curr;
			return;
		}

		checkColor(curr);

		if (num > curr->val) {
			if (curr->right == NULL) {
				curr->right = new Node(num);
				curr->right->parent = curr;
				checkColor(curr->right);
			}
			else {
				insertion(curr->right, num);
			}
		}
		else {
			if (curr->left == NULL) {
				curr->left = new Node(num);
				curr->left->parent = curr;
				checkColor(curr->left);
			}
			else {
				insertion(curr->left, num);
			}
		}
		return;
	}
	void outputInOrder(Node* curr) {
		if (curr == NULL) return;
		outputInOrder(curr->left);
		cout << curr->val << ' ';
		outputInOrder(curr->right);
	}
	void sortGroupOutfield(Group& team) {
		for (int i = 0; i < team.outfield.size(); i++) {
			pair<int, int> temp = team.outfield[i];
			for (int j = i; j > 0; j--) {
				if (temp.first < team.outfield[j - 1].first) {
					team.outfield[j] = team.outfield[j - 1];
				}
				else if (temp.first > team.outfield[j - 1].first) {
					team.outfield[j] = temp;
					break;
				}
				else {
					if (temp.second < team.outfield[j - 1].second) {
						team.outfield[j] = team.outfield[j - 1];
					}
					else {
						team.outfield[j] = temp;
						break;
					}
				}
				if (j == 1) {
					team.outfield[0] = temp;
				}
			}
		}

		vector<pair<int, int>> temp;
		team.jump_ball = team.outfield[0].second;
		for (int i = 3; i > 0; i--) {
			temp.push_back(team.outfield[team.outfield.size() - i]);
		}
		team.outfield = temp;
	}
public:
	RedBlackTree() : root(NULL) {};
	void InOrder() {
		outputInOrder(this->root);
	}
	void insert(int& num) {
		insertion(this->root, num);
		this->root->color = BLACK;
		return;
	}
	void splitToGroup(Group& teamA, Group& teamB) {
		trace(this->root, 1, teamA, teamB);
		if (teamA.outfield.size() < 4 || teamB.outfield.size() < 4) {
			noGame = true;
			return;
		}
		sortGroupOutfield(teamA);
		sortGroupOutfield(teamB);

		return;
	}
};

void outputGroupResult(Group& teamA, Group& teamB);

int main() {
	RedBlackTree students;
	
	for (int num = 0; cin >> num;) {
		students.insert(num);
	}

	Group teamA;
	Group teamB;
	students.splitToGroup(teamA, teamB);

	// cout << "InOrder: ";
	// students.InOrder();
	// cout << '\n';

	outputGroupResult(teamA, teamB);

	return 0;
}

void outputGroupResult(Group& teamA, Group& teamB) {
	if (noGame) {
		cout << "No game";
	}
	else {
		cout << "Red team: ";
		for (int i = 0; i < teamA.members.size(); i++) {
			cout << teamA.members[i];
			if (i != teamA.members.size() - 1) cout << ',';
		}
		cout << '\n';
		cout << "outfield: ";
		for (int i = 0; i < teamA.outfield.size(); i++) {
			cout << teamA.outfield[i].second;
			if (i != teamA.outfield.size() - 1) cout << ',';
		}
		cout << '\n';
		cout << "jump ball: " << teamA.jump_ball << '\n';

		cout << "Black team: ";
		for (int i = 0; i < teamB.members.size(); i++) {
			cout << teamB.members[i];
			if (i != teamB.members.size() - 1) cout << ',';
		}
		cout << '\n';
		cout << "outfield: ";
		for (int i = 0; i < teamB.outfield.size(); i++) {
			cout << teamB.outfield[i].second;
			if (i != teamB.outfield.size() - 1) cout << ',';
		}
		cout << '\n';
		cout << "jump ball: " << teamB.jump_ball;
	}
	return;
}