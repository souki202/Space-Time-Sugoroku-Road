#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <functional>
#include <cstring>

int field[100000] = { 0 };
int field2[100000] = { 0 };
bool roop[100000] = { false };
//bool safe[100000] = { 0 };
int min[100000] = { 0 };
int n;

int main() {
	std::cin >> n;
	for (int i = 0; i < n; i++) {
		std::cin >> field[i];
	}

	std::memset(field2, -1, sizeof(int) * 100000);

	//���[�v�ꏊ������
	for (int i = 1; i < n; i++) { //�J�n�ʒu
		std::vector<int> passed;
		bool isOk = false;
		int pos = i;
		passed.push_back(pos);
		while (!isOk) {
			int d = field[pos];
			pos += d;
			if (field[pos]) { //����n�}�X�ړ�
				if (std::find(passed.begin(), passed.end(), pos) != passed.end()) {
					break;//�ʉߍς݂̂Ƃ���ɂ����Ȃ�A���[�v���Ă���
				}
				if (roop[pos]) break; //���[�v����ꏊ�Ƃ��ċL�^�ς�
				if (field2[pos] >= 0) {
					isOk = true;
					pos = field2[pos];
					break; //OK�ꏊ�Ƃ��ċL�^�ς�
				}
			}
			else {
				isOk = true; //0�̃}�X�ɂ��������B
				break;
			}
			passed.push_back(pos);
		}
		passed.push_back(pos);
		if (isOk) {
			for (auto& x : passed) field2[x] = pos;
		}
		else for (auto& x : passed) roop[x] = true;
	}
	std::queue<std::pair<int, int>> q;
	q.push(std::make_pair(0, 0));
	while (!q.empty()) {
		auto node = q.front(); q.pop();

		for (int i = 1; i <= 6; i++) {
			auto next = node;
			next.second += i;
			if (next.second >= n - 1) { //�S�[�[�[��
				std::cout << next.first + 1 << std::endl;
				return 0;
			}
			if (roop[next.second] || field2[next.second] == -1) continue;
			next.second = field2[next.second]; //���
			next.first++;
			if (next.second >= n - 1) { //�S�[�[�[��
				std::cout << next.first << std::endl;
				return 0;
			}
			if (min[next.second] && min[next.second] <= next.first) continue;
			min[next.second] = next.first;
			q.push(next);
		}
	}

	return 0;
}