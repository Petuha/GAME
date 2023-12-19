#include <iostream>
#include <time.h>
#include "../Matrix/Matrix.h"
using namespace std;
long long sum(long long a, int b) {
	return a + b;
}
void test(int n, int m) {
	cout << "n = " << n << " m = " << m << '\n';
	Matrix<int> mat(n, m);
	int x = 1;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			mat[i][j] = x;
			x++;
		}
	}
	unsigned long long ts, tf;
	ts = clock();
	std::vector<long long> arr = mat.calc<long long>(0, sum);
	tf = clock();
	cout << "Test with threads: " << tf - ts << '\n';
	ts = clock();
	std::vector<long long> brr = mat.calcnothreads<long long>(0, sum);
	tf = clock();
	cout << "Test without threads: " << tf - ts << '\n';
}
int main() {
	test(8, 1e8);
	test(1e4, 1e4);
	test(1e2, 1e6);
	test(12, 1e9 / 12);
	return 0;
}