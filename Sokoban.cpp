#include <iostream>
#include <vector>
using namespace std;

class Sokoban {
private:
	vector<vector<char>> map;
	int playerX, playerY;

public:
	Sokoban(const vector<vector<char>>& level) : map(level) {
		for (int i = 0; i < map.size(); ++i) {
			for (int j = 0; j < map[i].size(); ++j) {
				if (map[i][j] == 'P') {
					playerX = i;
					playerY = j;
				}
			}
		}
	}

	void displayMap() {
		for (const auto& row : map) {
			for (char cell : row) {
				cout << cell << " ";
			}
			cout << endl;
		}
	}

	void movePlayer(char direction) {
		int newX = playerX, newY = playerY;
		switch (direction) {
			case 'w': newX--; break; // 上
			case 's': newX++; break; // 下
			case 'a': newY--; break; // 左
			case 'd': newY++; break; // 右
			default: cout << "無效輸入!請重新輸入正確指令!" << endl; return;
		}

		if (map[newX][newY] == ' ') {
			swap(map[playerX][playerY], map[newX][newY]);
			playerX = newX;
			playerY = newY;
		}
		else {
			cout << "這裡不能移動!" << endl;
		}
	}
};

int main() {
	vector<vector<char>> level = {
		{'#', '#', '#', '#', '#'},
		{'#', ' ', ' ', ' ', '#'},
		{'#', ' ', 'P', ' ', '#'},
		{'#', ' ', ' ', ' ', '#'},
		{'#', '#', '#', '#', '#'}
	};

	Sokoban game(level);

	while (true) {
		game.displayMap();
		char move;
		cout << "用 W(上) S(下) A(左) D(右) 移動:";
		cin >> move;
		game.movePlayer(move);
	}

	return 0;
}