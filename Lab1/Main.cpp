#include <iostream>
#include <time.h>

using namespace std;

int _max(int *mass, const int len) {

	int max = 0;

	for (int i = 0; i < len; i++) {
		if (max < mass[i])
			max = mass[i];
	}
	
	return max;
}

int _sum(int *mass, const int len) {

	int sum = 0;

	for (int i = len - 1, last_positive = false; i >= 0; i--) {
		if (mass[i] > 0 && !last_positive) {
			last_positive = true;
		}
		else if (last_positive) {
			sum += mass[i];
		}
	}

	return sum;
}

void main() {
	setlocale(LC_ALL, "");

	srand(time(NULL));

	const int len = 20;
	int mass[len] = {};

	for (int i = 0; i < len; i++) {
		mass[i] = -100 + rand() / (200);
		cout << mass[i] << " ";
	}

	cout << endl << "Максимальное значение: " << _max(mass, len) << endl;

	cout << "Сумма до последнего положительного: " << _sum(mass, len) << endl;

	system("pause");
}