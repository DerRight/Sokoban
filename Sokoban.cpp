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
			case 'w': newX--; break; // �W
			case 's': newX++; break; // �U
			case 'a': newY--; break; // ��
			case 'd': newY++; break; // �k
			default: cout << "�L�Ŀ�J!�Э��s��J���T���O!" << endl; return;
		}

		if (map[newX][newY] == ' ') {
			swap(map[playerX][playerY], map[newX][newY]);
			playerX = newX;
			playerY = newY;
		}
		else {
			cout << "�o�̤��ಾ��!" << endl;
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
		cout << "�� W(�W) S(�U) A(��) D(�k) ����:";
		cin >> move;
		game.movePlayer(move);
	}

	return 0;
}