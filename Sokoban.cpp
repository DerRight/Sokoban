#include <iostream>
#include <vector>
using namespace std;

class Sokoban {
private:
	vector<vector<char>> map;
	int playerX, playerY;
	bool playerOnGoal; // �������a�O�_�b�ؼ��I�W

public:
	Sokoban(const vector<vector<char>>& level) : map(level), playerOnGoal(false) {
		for (int i = 0; i < map.size(); ++i) {
			for (int j = 0; j < map[i].size(); ++j) {
				if (map[i][j] == 'P') {
					playerX = i;
					playerY = j;
					map[i][j] = ' '; // ���a��l��m�A�N�Ӧ�m�]�m���Ŧa
				}
			}
		}
	}

	void displayMap() {
		for (int i = 0; i < map.size(); ++i) {
			for (int j = 0; j < map[i].size(); ++j) {
				if (i == playerX && j == playerY) {
					if (playerOnGoal) {
						cout << '+'; // ���a���b�ؼ��I�W�|�� '+'
					}
					else {
						cout << 'P'; // ���a�b�Ŧa����� 'P'
					}
				}
				else {
					cout << map[i][j]; // ��ܦa�Ϩ�L���e
				}
				cout << ' ';
			}
			cout << endl;
		}
	}

	bool isCompleted() {
		for (const auto& row : map) {
			for (char cell : row) {
				if (cell == 'B') return false; // �p�G�٦���L�c�l�A�C���N�|�~��
			}
		}
		return true; // �Ҧ��c�l���w�g��F�ؼ��I
	}

	void movePlayer(char direction) {
		int newX = playerX, newY = playerY;
		switch (direction) {
			case 'w': newX--; break; // �W
			case 's': newX++; break; // �U
			case 'a': newY--; break; // ��
			case 'd': newY++; break; // �k
			default: cout << "�L�Ŀ�J�I�Э��s��J���O�I" << endl; return;
		}

		// �p�G�O�c�l�e��A�ˬd�᭱�c�l�Ŷ�
		if (map[newX][newY] == 'B' || map[newX][newY] == '*') {
			int beyondX = newX + (newX - playerX); // �p��c�l���ʫ᪺��m
			int beyondY = newY + (newY - playerY);

			if (map[beyondX][beyondY] == ' ' || map[beyondX][beyondY] == '.') {
				
				// ���ʽc�l
				if (map[beyondX][beyondY] == '.') {
					map[beyondX][beyondY] = '*'; // �c�l��F�ؼ��I
				}
				else {
					map[beyondX][beyondY] = 'B'; // ���ʨ�Ŧa
				}

				if (map[newX][newY] == '*') {
					map[newX][newY] = '.';  // �p�G�c�l��Ӧb�ؼ��I�W�A��_�ؼ��I
				}
				else {
					map[newX][newY] = ' '; // ���ʽc�l�᪺�Ŧa
				}

				updatePlayerPosition(newX, newY);
			}
			else {
				cout << "�L�k�A���ʽc�l�F�I" << endl;
			}

		}

		// �p�G�O�Ŧa�Υؼ��I�A�i�H����
		else if (map[newX][newY] == ' ' || map[newX][newY] == '.') {
			/*swap(map[playerX][playerY], map[newX][newY]);
			playerX = newX;
			playerY = newY;*/
			updatePlayerPosition(newX, newY);
		}
		else {
			cout << "�o�̤���A���ʤF�I" << endl;
		}
	}

	void updatePlayerPosition(int newX, int newY) {
		// ���a���ʫe�A�ˬd��e���a�O�_���b�ؼ��I�W
		if (playerOnGoal) {
			map[playerX][playerY] = '.'; // ��_��Ӫ��ؼ��I
		}
		else {
			map[playerX][playerY] = ' '; // �N��Ӧ�m�]�m���Ŧa
		}

		// ��s���a���s��m
		playerX = newX;
		playerY = newY;
		playerOnGoal = (map[newX][newY] == '.'); // �ˬd���a�O�_���b�ؼ��I�W
	}
};

int main() {
	// ��l�Ʀa��
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

	// �C���`��
	while (true) {
		game.displayMap();

		if (game.isCompleted()) {
			cout << "���ߧA�q���F�I" << endl;
			break;
		}

		char move;
		cout << "�� W(�W) S(�U) A(��) D(�k) ����:";
		cin >> move;
		game.movePlayer(move);
	}


	return 0;
}