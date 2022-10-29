#include <iostream>
#include <string>
#include <vector>

using namespace std;

bool finish = false;
void DFS(int**& map, string& res, vector<char> out, int& width, int x, int y, char dir);

int main() {
	int width;
	cin >> width;
	int** map = new int*[width];

	for (int i = 0; i < width; i++) {
		map[i] = new int[width];
	}

	for (int i = 0; i < width; i++) {
		for (int j = 0; j < width; j++) {
			int field;
			cin >> field;
			map[i][j] = field;
		}
	}

	string res;
	DFS(map, res, vector<char>(), width, 0, 0, 'E');
	cout << res;

	for (int i = 0; i < width; i++) {
		delete[] map[i];
	}
	delete[] map;
	return 0;
}
void DFS(int**& map, string& res, vector<char> out, int& width, int x, int y, char dir) {
	if (x < 0 || y < 0 || x >= width || y >= width) return;
	if (map[y][x] == 0 || map[y][x] == 2) return;
	if (finish) return;

	out.push_back(dir);
	map[y][x] = 2;

	if (x == width - 1 && y == width - 1) {
		finish = true;
		for (int i = 1; i < out.size(); i++) {
			res += out[i];
		}
		return;
	}

	DFS(map, res, out, width, x + 1, y, 'E');
	DFS(map, res, out, width, x, y - 1, 'N');
	DFS(map, res, out, width, x - 1, y, 'W');
	DFS(map, res, out, width, x, y + 1, 'S');
}