#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int Tomato[10000][1000] = {0};
int M, N, H, day=0, minuscnt =0;

// �յڸ� ������ ���� ����
vector<int> xD = { -1, 0, 0, 1};
vector<int> yD = { 0, 1, -1, 0};

void bfs() {
	int i, j, cnt1=0, cnt2, total = 0;
	queue<pair<int, int>> q;

	for (i = 0; i < N*H; i++) {
		for (j = 0; j < M; j++) {
			if (Tomato[i][j] == 1) {
				q.push(make_pair(i, j));   //������ ��� ����
				cnt1++;
			}
		}
	}
	total += cnt1;   
	while (!q.empty()) {
		if (total == M * N * H - minuscnt)  //1�� ������ -1�� ������ ���հ� ������ ����
			return;
		day++;   //��¥ ����
		cnt2 = 0;
		while (cnt1--) {
			int y = q.front().first;
			int x = q.front().second;
			q.pop();

			for (i = 0; i < 4; i++) {   //�� �ڸ� ������ ����
				int new_x = x + xD[i];
				int new_y = y + yD[i];
				if (new_x >= 0 && new_x < M && new_y < N*H && new_y >= 0) {  //���� ���� �����־����
					if ( Tomato[new_y][new_x] == 0  && y/N *N<=new_y && new_y < y / N * N +N) {
						cnt2++;     //�ݺ��� �߰�
						q.push(make_pair(new_y, new_x));
						Tomato[new_y][new_x] = 1;   
					}

				}
			}
			for (i = 0; i < 2; i++) {  //�� �� ����
				int new_y;
				if(i==0)
					new_y = y + N;
				else
					new_y = y - N;

				if (new_y < N * H && new_y >= 0) {
					if (Tomato[new_y][x] == 0) {
						cnt2++;   //�ݺ��� �߰�
						q.push(make_pair(new_y, x));
						Tomato[new_y][x] = 1;
					}
				}
			}
		}
		total += cnt2;
		cnt1 = cnt2;  //�ݺ��� �缳��
	}
}

int main() {
	int i, j, num, check=0;
	cin >> M >> N >> H;

	for (i = 0; i < N*H; i++) {
		for (j = 0; j < M; j++) {
			cin >> num;
			Tomato[i][j] = num;
		}
	}
	for (i = 0; i < N*H; i++) {
		for (j = 0; j < M; j++) {
			if (Tomato[i][j] == 0) {
				check = 1;
			}
			if (Tomato[i][j] == -1) {
				minuscnt++;
			}
			
		}
	}
	if (check == 0) {  //0�� ���� �� 0����ϰ� ����
		cout << 0;
		return 0;
	}

	check = 0;
	bfs(); 

	for (i = 0; i < N*H; i++) {
		for (j = 0; j < M; j++) {
			if (Tomato[i][j] == 0) {
				check = 1;
			}
		}
	}
	if (check == 1) {   //bfsŽ�� �� 0�� ���� �� -1����ϰ� ����
		cout << -1;
		return 0;
	}
	cout << day;

}
