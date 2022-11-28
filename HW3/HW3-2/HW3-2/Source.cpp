#include <iostream>
#include <vector>

using namespace std;

void BubbleSort(vector<int>& input);
void InsertionSort(vector<int>& input);
void SelectionSort(vector<int>& input);
void printResult(vector<int>& res, bool endl = true) {
	for (int i = 0; i < res.size(); i++) {
		cout << res[i];
		if (i != res.size() - 1) 
			cout << ' ';
	}
	if (endl) cout << '\n';
}

int main() {
	vector<int> input;
	for (int num = 0; cin >> num;) {
		input.push_back(num);
	}
	vector<int> bubble = input;
	vector<int> insertion = input;
	vector<int> selection = input;

	BubbleSort(bubble);
	InsertionSort(insertion);
	SelectionSort(selection);

	printResult(bubble, false);

	return 0;
}

void BubbleSort(vector<int>& input) {
	int count = 0;
	for (int i = input.size()-1; i >= 0 ; i--) {
		for (int j = 0; j < i; j++) {
			if (input[j] > input[j + 1]) {
				swap(input[j], input[j + 1]);
				count++;
			}
			if (count == 5) {
				cout << "Bubble: " << input[j] << ", " << input[j + 1] << "; ";
				printResult(input);
				count++;
			}
		}
	}
}
void InsertionSort(vector<int>& input) {
	for (int curr = 1; curr < input.size(); curr++) {
		int val = input[curr];
		for (int i = curr; i > 0; i--) {
			if (input[i - 1] < val) {
				input[i] = val;
				break;
			}
			else {
				input[i] = input[i - 1];
			}
			if (i == 1) {
				input[0] = val;
			}
		}
		if (curr == 4) {
			cout << "Insertion: ";
			printResult(input);
		}
	}
}
void SelectionSort(vector<int>& input) {
	for (int curr = 0; curr < input.size(); curr++) {
		int index = curr;
		for (int i = curr; i < input.size(); i++) {
			if (input[i] < input[index]) {
				index = i;
			}
		}
		swap(input[curr], input[index]);
		if (curr == 4) {
			cout << "Selection: " << input[curr] << "; ";
			printResult(input);
		}
	}
}