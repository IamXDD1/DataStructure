#include <iostream>
#include <vector>

using namespace std;

class Node {
public:
	string name;
	int arrival_time;
	int required_time;
	Node() {};
	Node(string name, int arrival_time, int required_time) :
		name(name), arrival_time(arrival_time), required_time(required_time) {};
};

class Queue {
public:
	vector<Node> root;
	Queue(){};
	void push(Node node) {
		this->root.push_back(node);
	}
	void pop() {
		if (this->root.size() > 0) {
			this->root.erase(this->root.begin());
		}
	}
	void reduceTime() {
		this->root[0].required_time--;
	}
	int size() {
		return this->root.size();
	}
	Node first() {
		if (this->root.size() > 0)
			return this->root[0];
	}
};

int main() {
	int counterNum;
	cin >> counterNum;
	if (counterNum > 10) {
		counterNum = 10;
	}

	Queue* counter = new Queue[counterNum];

	Node person;
	vector<Node> input;
	vector<Node> output;
	for (; cin >> person.name >> person.arrival_time >> person.required_time;) {
		input.push_back(person);
	}

	int countPeople = input.size();
	bool changeTime = false;

	for (int time = 0; output.size() != countPeople;) {
		changeTime = false;
		if (!input.empty()) {
			if (input[0].arrival_time == time) {
				int counter_choice = 0;
				// 抵達時間 = 當前時間時，選擇一個櫃台 (比人數在比號碼)
				for (int i = 0, peopleNum = counter[0].size(); i < counterNum; i++) {
					if (counter[i].size() < peopleNum) {
						counter_choice = i;
						peopleNum = counter[i].size();
					}
				}

				counter[counter_choice].push(input[0]);
				input.erase(input.begin());
			}
			else {
				time++;
				changeTime = true;
			}
		}
		else {
			time++;
			changeTime = true;
		}
		// 如果時間有做更動，則判斷是否有人已完成辦理
		if (changeTime) {
			for (int i = 0; i < counterNum; i++) {
				if (counter[i].size() > 0) {
					counter[i].reduceTime();
					if (counter[i].first().required_time == 0) {
						output.push_back(Node(counter[i].first().name, time, i));
						counter[i].pop();
					}
				}
			}
		}

	}

	for (int i = 0; i < output.size(); i++) {
		cout << output[i].name << ' ' << output[i].arrival_time << ' ' << output[i].required_time << '\n';
	}

	delete[] counter;

	return 0;
}