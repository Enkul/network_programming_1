// Түргэн хоолны газрын хоол захиалгыг загварчлах.
 // Үүнд: Үйлчлүүлэгч түргэн хоолны газар ороход ямар хоол захиалахыг нь асууна. 
 // Мөн өөр хоол захиалах эсэхийг асуугаад нэмж захиалга авч болно. 
 // Ямар, ямар хоол захиалснаас нь шалтгаалан хоолны төлбөр бодож гаргаад, 
 // төлсөн мөнгөний хариулт мөнгийг буцаан өгдөг програм бичнэ. 
 // Жич: Дараагийн үйлчлүүлэгч өмнөх үйлчлүүлэгчийн дараа шууд үйлчлүүлдэг байна.

#include <iostream>
#include <string>
#include <queue>
using namespace std;
class Food {
    public:
        int price;
        string name;
        int stock;
};

Food menu[2];
class Person {
    public:
        string name;
        int total = 0;
        int balance = 0;
};

// queue<Person> persons;
void set_menu() {
    menu[0].name = "pirishki";
    menu[0].price = 1000;
    menu[0].stock = 3;
    menu[1].name = "goimon";
    menu[1].price = 3000;
    menu[1].stock = 3; 
}

void see_menu() {
    cout << "menu-d baigaa hoolig haruulj baina" << endl;
    cout << "hoolnii ner " << "hoolnii une" << "delguur bga shirheg" << endl;
    for (int i = 0; i < 2; i++) {
        cout << menu[i].name  << " " << menu[i].price  << " " << menu[i].stock << endl; 

    }
}

void order() {
    see_menu();
    cout << "tanii nerig hen gedeg we:" << endl;
    string name;
    cin >> name;
    Person person;
    queue<string> foods;
    person.name = name;
    while (true) {
        cout << "ta ymr hool zahialah we:";
        string food;
        cin >> food;
        int count;
        cout << "ta heden shirhegig zahialah we:";
        cin >> count;
        try {
            if (count < 1) {
                throw(count);
            }
        } catch (int count) {
            cout << "ta hoolnii zahialgin shirhegin toogo zuw orulna uu:" << endl;
            cout << "tanii orulsan buruu utga: " << count << endl;
            cout << "ta buruu utga orulsan ucir programas garlaa" << endl;
            break;
        }
        try {
            bool flag = true;
            for (int i = 0; i < 2; i++) {
                if (menu[i].name == food) {
                    flag = false;
                }
            }
            if (flag) {
                throw(food);
            }
        } catch (string food) {
            cout << "ta hoolnii neree zuw orulna uu:" << endl;
            cout << "tanii orulsan buruu utga: " << food << endl;
            cout << "ta buruu utga orulsan ucir programas garlaa" << endl;
            break;
        }
        foods.push(food + " " + to_string(count) + " shirheg");
        for (int i = 0; i < 2; i++) {
            if (menu[i].name == food) {
                person.total += menu[i].price * count;
            }
        }
        cout << person.name << " tanii tulbur " << person.total << " bolj baina, ta tootsoogoo hiihuu (yes or no)?";
        string answer;
        cin >> answer;
        if (answer == "yes") {
            int cash;
            cout << "ta munguu ugnuu:";
            cin >> cash;
            person.balance = cash;
            if (person.balance == person.total) {
                cout << "bayrlla, tanii zahialsan hoolnuud" << endl;
                person.total = 0;
                while (!foods.empty()) {
                    cout << foods.front() << endl;
                    foods.pop();
                }
            } else {
                if (person.balance - person.total > 0) {
                    cout << "tanii hariul mungu " << person.balance - person.total << endl;
                    // break;
                    while (!foods.empty()) {
                        cout << foods.front() << endl;
                     foods.pop();
                    }
                    person.total = 0;
                }
                else {
                    cout << "tanii tootsoo " << person.balance - person.total << " tugrugnii zuurutei baina" << endl;
                    cout << "ta munguu guitset ugj baij hooloo awah bolomjtoi" << endl;
                }
            }
        }
        cout << "ta dahij zahialga hiihu (yes or no)?";
        string ans;
        cin >> ans;
        if (ans != "yes")
            break;

        
    } 
}
int main() {
    set_menu();
    order();
    return 0;
}