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

	bool isCompleted() {
		for (const auto& row : map) {
			for (char cell : row) {
				if (cell == 'B') return false;
			}
		}
		return true;
	}

	void movePlayer(char direction) {
		int newX = playerX, newY = playerY;
		switch (direction) {
			case 'w': newX--; break; // 上
			case 's': newX++; break; // 下
			case 'a': newY--; break; // 左
			case 'd': newY++; break; // 右
			default: cout << "無效輸入！請重新輸入指令！" << endl; return;
		}

		// 如果是箱子前方，檢查後面箱子空間
		if (map[newX][newY] == 'B' || map[newX][newY] == '*') {
			int beyondX = newX + (newX - playerX); // 計算箱子推動後的位置
			int beyondY = newY + (newY - playerY);

			if (map[beyondX][beyondY] == ' ' || map[beyondX][beyondY] == '.') {
				
				// 推動箱子
				if (map[beyondX][beyondY] == '.') {
					map[beyondX][beyondY] = '*'; // 箱子到達目標點
				}
				else {
					map[beyondX][beyondY] = 'B'; // 推動到空地
				}

				if (map[newX][newY] == '*') {
					map[newX][newY] = '.';  // 如果箱子原來在目標點上，恢復目標點
				}
				else {
					map[newX][newY] = ' '; // 移動箱子後的空地
				}

				swap(map[playerX][playerY], map[newX][newY]);
				playerX = newX;
				playerY = newY;
			}
			else {
				cout << "無法再推動箱子了！" << endl;
			}

		}

		// 如果是空地或目標點，可以移動
		else if (map[newX][newY] == ' ' || map[newX][newY] == '.') {
			swap(map[playerX][playerY], map[newX][newY]);
			playerX = newX;
			playerY = newY;
		}
		else {
			cout << "這裡不能再移動了！" << endl;
		}
	}
};

int main() {
	// 初始化地圖
	vector<vector<char>> level = {
		{'#', '#', '#', '#', '#', '#', '#'},
		{'#', ' ', ' ', ' ', ' ', ' ', '#'},
		{'#', ' ', ' ', ' ', ' ', ' ', '#'},
		{'#', ' ', 'P', 'B', ' ', ' ', '#'},
		{'#', ' ', ' ', ' ', ' ', ' ', '#'},
		{'#', ' ', ' ', '.', ' ', ' ', '#'},
		{'#', '#', '#', '#', '#', '#', '#'}
	};

	Sokoban game(level);

	// 遊戲循環
	while (true) {
		game.displayMap();

		if (game.isCompleted()) {
			cout << "恭喜你通關了！" << endl;
			break;
		}

		char move;
		cout << "用 W(上) S(下) A(左) D(右) 移動:";
		cin >> move;
		game.movePlayer(move);
	}


	return 0;
}