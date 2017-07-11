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

	//ループ場所を検索
	for (int i = 1; i < n; i++) { //開始位置
		std::vector<int> passed;
		bool isOk = false;
		int pos = i;
		passed.push_back(pos);
		while (!isOk) {
			int d = field[pos];
			pos += d;
			if (field[pos]) { //次がnマス移動
				if (std::find(passed.begin(), passed.end(), pos) != passed.end()) {
					break;//通過済みのところについたなら、ループしている
				}
				if (roop[pos]) break; //ループする場所として記録済み
				if (field2[pos] >= 0) {
					isOk = true;
					pos = field2[pos];
					break; //OK場所として記録済み
				}
			}
			else {
				isOk = true; //0のマスにあたった。
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
			if (next.second >= n - 1) { //ゴーーール
				std::cout << next.first + 1 << std::endl;
				return 0;
			}
			if (roop[next.second] || field2[next.second] == -1) continue;
			next.second = field2[next.second]; //飛ぶ
			next.first++;
			if (next.second >= n - 1) { //ゴーーール
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