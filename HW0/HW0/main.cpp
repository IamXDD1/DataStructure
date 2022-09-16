#include <iostream>

int arr[46] = {};

int Fibonacci(int index) {
	if (index < 2) return arr[index];

	if (arr[index] != -1) {
		return arr[index];
	}
	else {
		arr[index] = Fibonacci(index - 1) + Fibonacci(index - 2);
		return arr[index - 1] + arr[index - 2];
	}
}

int main() {
	for (int i = 0; i < 46; i++) {
		arr[i] = -1;
	}

	arr[0] = 0;
	arr[1] = 1;

	int inputCount = 0;
	std::cin >> inputCount;
	for (int i = 0; i < inputCount; i++) {
		int num;
		std::cin >> num;
		std::cout << Fibonacci(num) << '\n';
	}
	

	return 0;
}