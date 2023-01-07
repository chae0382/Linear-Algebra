#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
using namespace std;

int GCD(int, int);
int LCM(int, int);
int main() {
	int n;
	int m;
	cout << "Matrix A�� LU factorization ���� ��ȯ�ϱ�\n\n";
	cout << "�Է��ϰ��� �ϴ� matrix�� ���� ���� �Է��Ͻÿ�.";
	cin >> m;
	cout << "�Է��ϰ��� �ϴ� matrix�� ���� ���� �Է��Ͻÿ�.";
	cin >> n;

	//m*n �迭�� �����Ҵ� ���ش�.
	int **Umatrix = new int*[m];
	int **matrix = new int*[m];
	for (int i = 0; i < m; i++) {
		Umatrix[i] = new int[n];
		matrix[i] = new int[n];
	}
	cout << "\nmatrix A �� component�� �Է��Ͻÿ�.(�Է°��� ������ �����)\n";
	//�Էµ� ���� matrix A�� �ش� index�� �־��ش�.
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			cin >> matrix[i][j];
			Umatrix[i][j] = matrix[i][j];
		}
	}
	//elementary matrice�� m�� n �� ���� ���� ��� ���� ������ matrix�̴�.
	int e = m;

	//e*e �� elementary matrice �� ���ҷ� ������ vector �� �����.
	vector <vector <vector <double>>> elem;

	//�⺻���� e*e elemtary matrice ���Ҹ� vector �� �������´�.
	vector<vector<double>>e2;
	for (int i = 0; i < e; i++) {
		vector<double>e1;
		for (int j = 0; j < e; j++) {
			if (i == j) e1.push_back(1);
			else {
				e1.push_back(0);
			}
		}
		e2.push_back(e1);
	}

	int eN = 0;

	//elementary matrix�� upper triangular matrix�� ����� �������� ����Ǵ� row operation �� ���� �����ǹǷ� 
	//matrix A�� upper triangular matrix�� �����.
	//upper triangular matrix�� i>j �϶� a(ij)=0 �̹Ƿ� i=j �϶��� �������� ��� �Ʒ� ��鿡 row operation �� ���ش�.

	int i = 0; int j = 0;
	while (i < m && j < n) {
		if (Umatrix[i][j] == 0) {
			for (int k = i; k < m; k++) {
				if (Umatrix[k][j] != 0) {
					//R(i)<->R(k) operation �� ������ �ؾ� upper triangular matrix �� ���� �� �ִ� ����
					//LU factorization �� �� �� ����.

					cout << "������ matrix A �� LU factorization �� �� �� �����ϴ�." << endl;
					return 0;
				}
			}
		}
		for (int k = i + 1; k < m; k++) {
			if (Umatrix[k][j] == 0)continue;

			//����� ���������� ���� �����ϱ� ���� matrix[i][i]�� �� �Ʒ� ������ ���� ������ �ּҰ������ ���ϰ�,
			//�ּҰ������ �̿��� �� �Ʒ� ���ҵ��� ��� 0���� ������ش�.
			else {
				int lcm = LCM(Umatrix[i][j], Umatrix[k][j]);
				int mul1 = lcm / Umatrix[i][j];//i��° �࿡ mul1�� ���ϰ� j��° �࿡ mul2�� ���ϸ�
				int mul2 = lcm / Umatrix[k][j];//�� ���� 0�� �ƴ� �� ���� ���Ұ� �ּҰ������ ��������.
				for (int l = 0; l < n; l++) {

					//R(k)<- R(k) * mul2
					Umatrix[k][l] = mul2 * Umatrix[k][l];

					//R(k)<- - mul1 * R(i) + R(k)
					Umatrix[k][l] = Umatrix[k][l] - mul1 * Umatrix[i][l];
				}

				//R(k)<- R(k) * mul2
				//row operation �� ���������Ƿ� elementary matrix �� inverse�� �����ϰ�
				//�װ��� elem ���Ϳ� �߰��ǵ��� �Ѵ�.
				elem.push_back(e2);
				eN++;
				for (int l = 0; l < e; l++) {
					elem[eN - 1][k][l] = (double)elem[eN - 1][k][l] / mul2;
				}

				//R(k)<- - mul1 * R(i) + R(k)
				// row operation �� ���������Ƿ� elementary matrix �� inverse�� �����ϰ�
				//�װ��� elem ���Ϳ� �߰��ǵ��� �Ѵ�.
				elem.push_back(e2);
				eN++;
				for (int l = 0; l < e; l++) {
					elem[eN - 1][k][l] += mul1 * elem[eN - 1][i][l];
				}
			}
		}
		++i; ++j;
	}

	//������ elementary matrix �� inverse ���� �����ָ� Lower triangular matrix �� ���´�.
	double ***Lmatrix = new double**[eN];
	for (int i = 0; i < eN; i++) {
		Lmatrix[i] = new double*[e];
	}
	for (int i = 0; i < eN; i++) {
		for (int j = 0; j < e; j++) {
			Lmatrix[i][j] = new double[e];
		}
	}
	for (int i = 0; i < e; i++) {
		for (int j = 0; j < e; j++) {
			Lmatrix[0][i][j] = elem[0][i][j];
		}
	}
	double s = 0;
	for (int i = 0; i < eN - 1; i++) {
		for (int j = 0; j < e; j++) {
			for (int k = 0; k < e; k++) {
				s = 0;
				for (int l = 0; l < e; l++) {
					s += Lmatrix[i][j][l] * elem[i + 1][l][k];
				}
				Lmatrix[i + 1][j][k] = s;
			}
		}
	}

	//matrix�� �����ؼ� ����Ѵ�.
	cout << "\nLU factorization ��� : \n\n";

	for (i = 0; i < m; i++) {
		if (i == 0) { cout << "A = "; }
		else {
			cout << "    ";
		}
		for (j = 0; j < n; j++) {
			cout << setprecision(2) << setw(8) << matrix[i][j];
		}
		if (i == 0) {
			cout << setw(8) << " = ";
		}
		else {
			cout << setw(8) << "  ";
		}
		for (j = 0; j < e; j++) {
			cout << setprecision(2) << setw(8) << Lmatrix[eN - 1][i][j];
		}
		if (i == m / 2) {
			cout << setw(8) << " X ";
		}
		else {
			cout << setw(8) << "  ";
		}
		for (j = 0; j < n; j++) {
			cout << setprecision(2) << setw(8) << Umatrix[i][j];
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