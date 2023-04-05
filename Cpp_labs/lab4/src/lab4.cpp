#include <iostream>
#include <algorithm>

using namespace std;


class Matrix {
private:
	int n = 1; // порядок матрицы
	double **ptr; // для матрицы

public:
	Matrix(int n_size):
			n(n_size)
	{
		for (int i = 0; i < n; i++) {
			ptr[i] = new double[n];
		}
		ptr = set_data();
	}

	~Matrix() {
		for (int i = 0; i < n; i++) {
			delete ptr[i];
		}
		delete [] ptr;
	}

	int get_size() { return n; }

	void show() { // вывод элементов матрицы
		cout << "MATRIX:" << endl;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				cout << ptr[i][j] << " ";
			}
			cout << endl;
		}
	}


	int set_data() {
		int element;
		cout << "input elements:" << endl;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				cin >> element;
				ptr[i][j] = element;
			}
		}
		return ptr;
	}


	void operator--() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			ptr[i][j] -= 0.1;
			}
		}
	}

	void operator--(int) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				ptr[i][j] -= 0.1;
			}
		}
	}

	Matrix operator-(Matrix obj) {
		int first_size = n;
		int sexond_size = obj.n;
		Matrix new_matrix = obj;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; i++) {
				new_matrix.ptr[i][j] -= ptr[i][j];
			}
		}
		return new_matrix;
	}

	void operator*(int k) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				ptr[i][j] *= k;
			}
		}
	}
};

int main() {
	int number;
//	cout << "input number of rows: ";
//	cin >> number;
	Matrix new_t = Matrix(4);
	new_t.show();
	return 0;
}
