#include <iostream>
#include <iomanip>
using namespace std;

int GCD(int, int);
int LCM(int, int);
int main() {
	int n;
	int m;
	cout << "Matrix를 Upper triangular matrix 로 변환하기\n\n";
	cout << "입력하고자 하는 matrix의 행의 수를 입력하시오.";
	cin >> m;
	cout << "입력하고자 하는 matrix의 열의 수를 입력하시오.";
	cin >> n;
	//m*n 배열을 동적할당 해준다.
	int **matrix = new int*[m];
	for (int i = 0; i < m; i++) {
		matrix[i] = new int[n];
	}
	cout << "\nmatrix component를 입력하시오.(입력값은 정수만 허용함)\n";
	//입력된 수를 matrix의 해당 index에 넣어준다.
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			cin >> matrix[i][j];
		}
	}
	//upper triangular matrix는 i>j 일때 a(ij)=0 이므로 i=j 일때를 기준으로 잡아 아래 행들에 row operation 을 해준다.
	int i = 0;
	while (i < m && i < n) {
		if (matrix[i][i] == 0) {//diagonal 이 0이 되지 않기 위해 0이 아닌 행과 바꾸어준다.
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
			//계산이 복잡해지는 것을 방지하기 위해 matrix[i][i]와 그 아래 각각의 행의 원소의 최소공배수를 구하고,
			//최소공배수를 이용해 그 아래 원소들을 모두 0으로 만들어준다.
			else {
				int lcm = LCM(matrix[i][i], matrix[j][i]);
				int mul1 = lcm / matrix[i][i];//i번째 행에 mul1을 곱하고 j번째 행에 mul2를 곱하면
				int mul2 = lcm / matrix[j][i];//두 행의 0이 아닌 맨 앞의 원소가 최소공배수로 같아진다.
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
	cout << "\n결과 : \n\n";
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			//matrix를 정렬해서 출력한다.
			cout << setw(3) << matrix[i][j] << " ";
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