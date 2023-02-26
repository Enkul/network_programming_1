// Оюутны голч дүнгээр оюутныг ямар сурж байгааг тодорхойлох. 
// Үүнд: Гараас оюутны голч дүнг оруулахад нөхцөл шалгаад ямар сурч байгааг нь
//  тодорхойлох бөгөөд хэрхэн суралцах талаар зөвлөгөө өгдөг байна.
//  Жич: Програм тасралтгүй ажиллана.

#include <iostream>
using namespace std;

class Student {
	public:
		string name;
		float gpa;
		string code;
};

void check(Student student) {
	if (student.gpa < 3.0) {
		cout << student.name << " nertei " << student.code << " code-toi oyutan ta ";
		cout << "hiceelee sn hiiged, uuhaa bagasgaira !!!" << endl;
 	} else {
 		cout << student.name << " nertei " << student.code << " code-toi oyutan ta ";
 		cout << "hiceelee sn hiideg oyutan baina, urgeljuuled sn surarai :D" << endl;
 	}
}
int main() {
	while (1) {
		Student student;
		cout << "oyutanii ner: ";
		cin >> student.name;
		cout << "oyutanii code: ";
		cin >> student.code;
		cout << "oyutanii golch dun: ";
		cin >> student.gpa;
		check(student);
	}

	return 0;
}