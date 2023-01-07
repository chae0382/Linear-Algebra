#include <iostream>
#include <iomanip>
using namespace std;

int GCD(int, int);
int LCM(int, int);
int main() {
	int n;
	int m;
	cout << "Matrix�� Upper triangular matrix �� ��ȯ�ϱ�\n\n";
	cout << "�Է��ϰ��� �ϴ� matrix�� ���� ���� �Է��Ͻÿ�.";
	cin >> m;
	cout << "�Է��ϰ��� �ϴ� matrix�� ���� ���� �Է��Ͻÿ�.";
	cin >> n;
	//m*n �迭�� �����Ҵ� ���ش�.
	int **matrix = new int*[m];
	for (int i = 0; i < m; i++) {
		matrix[i] = new int[n];
	}
	cout << "\nmatrix component�� �Է��Ͻÿ�.(�Է°��� ������ �����)\n";
	//�Էµ� ���� matrix�� �ش� index�� �־��ش�.
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			cin >> matrix[i][j];
		}
	}
	//upper triangular matrix�� i>j �϶� a(ij)=0 �̹Ƿ� i=j �϶��� �������� ��� �Ʒ� ��鿡 row operation �� ���ش�.
	int i = 0;
	while (i < m && i < n) {
		if (matrix[i][i] == 0) {//diagonal �� 0�� ���� �ʱ� ���� 0�� �ƴ� ��� �ٲپ��ش�.
			for (int j = 0; j < m; j++) {
				if (matrix[j][i] != 0) {
					//R(i)<->R(j)
					for (int k = 0; k < n; k++) {
						int tmp = matrix[i][k];
						matrix[i][k] = matrix[j][k];
						matrix[j][k] = tmp;
					}
					break;
				}
			}
		}
		for (int j = i+1; j < m; j++) {
			if (matrix[j][i] == 0)continue;
			//����� ���������� ���� �����ϱ� ���� matrix[i][i]�� �� �Ʒ� ������ ���� ������ �ּҰ������ ���ϰ�,
			//�ּҰ������ �̿��� �� �Ʒ� ���ҵ��� ��� 0���� ������ش�.
			else {
				int lcm = LCM(matrix[i][i], matrix[j][i]);
				int mul1 = lcm / matrix[i][i];//i��° �࿡ mul1�� ���ϰ� j��° �࿡ mul2�� ���ϸ�
				int mul2 = lcm / matrix[j][i];//�� ���� 0�� �ƴ� �� ���� ���Ұ� �ּҰ������ ��������.
				for (int k = 0; k < n; k++) {
					//R(j)<- R(j) * mul2
					//R(j)<- -mul1 * R(j) + R(j)
					matrix[j][k] = mul2 * matrix[j][k];
					matrix[j][k] = matrix[j][k] -mul1 * matrix[i][k];
				}
			}
		}
		++i; 
	}
	cout << "\n��� : \n\n";
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			//matrix�� �����ؼ� ����Ѵ�.
			cout << setw(3) << matrix[i][j] << " ";
		}
		cout << endl;
	}

}
int GCD(int x, int y) { // x,y�� �ִ������� ���ϴ� �Լ�
	if (y == 0) {
		return x;
	}
	return GCD(y, x%y);
}
int LCM(int x, int y) { // x,y�� �ּҰ������ ���ϴ� �Լ�
	return x * y / GCD(x, y);
}