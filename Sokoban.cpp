#include <iostream>
#include <vector>
using namespace std;

class Sokoban {
private:
	vector<vector<char>> map;
	int playerX, playerY;
	bool playerOnGoal; // 紀錄玩家是否在目標點上

public:
	Sokoban(const vector<vector<char>>& level) : map(level), playerOnGoal(false) {
		for (int i = 0; i < map.size(); ++i) {
			for (int j = 0; j < map[i].size(); ++j) {
				if (map[i][j] == 'P') {
					playerX = i;
					playerY = j;
					map[i][j] = ' '; // 玩家初始位置，將該位置設置為空地
				}
			}
		}
	}

	void displayMap() {
		for (int i = 0; i < map.size(); ++i) {
			for (int j = 0; j < map[i].size(); ++j) {
				if (i == playerX && j == playerY) {
					if (playerOnGoal) {
						cout << '+'; // 玩家站在目標點上會變 '+'
					}
					else {
						cout << 'P'; // 玩家在空地時顯示 'P'
					}
				}
				else {
					cout << map[i][j]; // 顯示地圖其他內容
				}
				cout << ' ';
			}
			cout << endl;
		}
	}

	bool isCompleted() {
		for (const auto& row : map) {
			for (char cell : row) {
				if (cell == 'B') return false; // 如果還有其他箱子，遊戲就會繼續
			}
		}
		return true; // 所有箱子都已經到達目標點
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

				updatePlayerPosition(newX, newY);
			}
			else {
				cout << "無法再推動箱子了！" << endl;
			}

		}

		// 如果是空地或目標點，可以移動
		else if (map[newX][newY] == ' ' || map[newX][newY] == '.') {
			/*swap(map[playerX][playerY], map[newX][newY]);
			playerX = newX;
			playerY = newY;*/
			updatePlayerPosition(newX, newY);
		}
		else {
			cout << "這裡不能再移動了！" << endl;
		}
	}

	void updatePlayerPosition(int newX, int newY) {
		// 玩家移動前，檢查當前玩家是否站在目標點上
		if (playerOnGoal) {
			map[playerX][playerY] = '.'; // 恢復原來的目標點
		}
		else {
			map[playerX][playerY] = ' '; // 將原來位置設置為空地
		}

		// 更新玩家的新位置
		playerX = newX;
		playerY = newY;
		playerOnGoal = (map[newX][newY] == '.'); // 檢查玩家是否站在目標點上
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