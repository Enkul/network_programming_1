#include <iostream>
using namespace std;

// Нэг өрхийн сарын цахилгааны зардлыг тооцоолдог програм бичнэ үү. Гараас
// өдөрт зарцуулах дундаж кВт, 1 кВт/цаг-ийн үнийг авна.

int main() {
	float kbt,kbt_hour;
	cin >> kbt >> kbt_hour;
	float total;
	total = kbt * kbt_hour * 30;
	cout << "өдөрт зарцуулах дундаж зардал: " << kbt_hour * kbt << endl;
	cout << "Нэг өрхийн сарын цахилгааны зардал: " <<  total;
	return 0;
}