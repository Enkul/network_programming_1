#include <bits/stdc++.h>
using namespace std;

class Lesson {
	public:
		int id;
		string code;
		int credit;
		string name; 
};
class Student {
	public:
		int id;
		string name;
		string code;
		string password;
		Lesson lessons[10];
		void login(string,string);
		void register(){
			cout << "what is your name: ";
			cin >> name;
			cout << "what is your code: ";
			cin >> code;
			string current_password;
			string confirm_password;
			cout << "ehnii nuuuts ugee orulna uu:";
			cin >> current_password;
			cout << "password batalgaajuulna: ";
			
		};
		// void getLessons();


};

class Teacher: private Student {
	public:
		void editLesson();
		void deleteLesson();
		void getLesson();

};


// global variables
Lesson lessons[3];

void set_lessons() {
	lessons[0].name = "Сүлжээний программчлал I";
	lessons[0].code = "F.NS351";
	lessons[0].credit = 3;
	lessons[1].name = "Нууцлалын протоколууд";
	lessons[1].code = "F.NS355";
	lessons[1].credit = 3;
	lessons[2].name = "Веб системийн аюулгүй байдал";
	lessons[2].code = "F.NS357";
	lessons[2].credit = 3;
}

int main() {
	set_lessons();
	cout << "hiceelin ner || hiceelin code || hiceelin credit" << endl;
	for (int i = 0; i < 3; i++) {
		cout << lessons[i].name << " " << lessons[i].code << " " << lessons[i].credit << endl;
	}
	return 0;
}