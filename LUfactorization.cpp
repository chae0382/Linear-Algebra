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
	cout << "Matrix A를 LU factorization 으로 변환하기\n\n";
	cout << "입력하고자 하는 matrix의 행의 수를 입력하시오.";
	cin >> m;
	cout << "입력하고자 하는 matrix의 열의 수를 입력하시오.";
	cin >> n;

	//m*n 배열을 동적할당 해준다.
	int **Umatrix = new int*[m];
	int **matrix = new int*[m];
	for (int i = 0; i < m; i++) {
		Umatrix[i] = new int[n];
		matrix[i] = new int[n];
	}
	cout << "\nmatrix A 의 component를 입력하시오.(입력값은 정수만 허용함)\n";
	//입력된 수를 matrix A의 해당 index에 넣어준다.
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			cin >> matrix[i][j];
			Umatrix[i][j] = matrix[i][j];
		}
	}
	//elementary matrice는 m과 n 중 작은 값의 행과 열을 가지는 matrix이다.
	int e = m;

	//e*e 의 elementary matrice 를 원소로 가지는 vector 를 만든다.
	vector <vector <vector <double>>> elem;

	//기본적인 e*e elemtary matrice 원소를 vector 로 만들어놓는다.
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

	//elementary matrix는 upper triangular matrix를 만드는 과정에서 수행되는 row operation 에 따라 결정되므로 
	//matrix A를 upper triangular matrix로 만든다.
	//upper triangular matrix는 i>j 일때 a(ij)=0 이므로 i=j 일때를 기준으로 잡아 아래 행들에 row operation 을 해준다.

	int i = 0; int j = 0;
	while (i < m && j < n) {
		if (Umatrix[i][j] == 0) {
			for (int k = i; k < m; k++) {
				if (Umatrix[k][j] != 0) {
					//R(i)<->R(k) operation 을 무조건 해야 upper triangular matrix 로 만들 수 있는 경우는
					//LU factorization 을 할 수 없다.

					cout << "다음의 matrix A 는 LU factorization 을 할 수 없습니다." << endl;
					return 0;
				}
			}
		}
		for (int k = i + 1; k < m; k++) {
			if (Umatrix[k][j] == 0)continue;

			//계산이 복잡해지는 것을 방지하기 위해 matrix[i][i]와 그 아래 각각의 행의 원소의 최소공배수를 구하고,
			//최소공배수를 이용해 그 아래 원소들을 모두 0으로 만들어준다.
			else {
				int lcm = LCM(Umatrix[i][j], Umatrix[k][j]);
				int mul1 = lcm / Umatrix[i][j];//i번째 행에 mul1을 곱하고 j번째 행에 mul2를 곱하면
				int mul2 = lcm / Umatrix[k][j];//두 행의 0이 아닌 맨 앞의 원소가 최소공배수로 같아진다.
				for (int l = 0; l < n; l++) {

					//R(k)<- R(k) * mul2
					Umatrix[k][l] = mul2 * Umatrix[k][l];

					//R(k)<- - mul1 * R(i) + R(k)
					Umatrix[k][l] = Umatrix[k][l] - mul1 * Umatrix[i][l];
				}

				//R(k)<- R(k) * mul2
				//row operation 이 실행됬으므로 elementary matrix 의 inverse를 생성하고
				//그것이 elem 벡터에 추가되도록 한다.
				elem.push_back(e2);
				eN++;
				for (int l = 0; l < e; l++) {
					elem[eN - 1][k][l] = (double)elem[eN - 1][k][l] / mul2;
				}

				//R(k)<- - mul1 * R(i) + R(k)
				// row operation 이 실행됬으므로 elementary matrix 의 inverse를 생성하고
				//그것이 elem 벡터에 추가되도록 한다.
				elem.push_back(e2);
				eN++;
				for (int l = 0; l < e; l++) {
					elem[eN - 1][k][l] += mul1 * elem[eN - 1][i][l];
				}
			}
		}
		++i; ++j;
	}

	//생성된 elementary matrix 의 inverse 들을 곱해주면 Lower triangular matrix 가 나온다.
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

	//matrix를 정렬해서 출력한다.
	cout << "\nLU factorization 결과 : \n\n";

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
int GCD(int x, int y) { // x,y의 최대공약수를 구하는 함수
	if (y == 0) {
		return x;
	}
	return GCD(y, x%y);
}
int LCM(int x, int y) { // x,y의 최소공배수를 구하는 함수
	return x * y / GCD(x, y);
}