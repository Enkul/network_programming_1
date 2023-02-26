#include <iostream>
#include <string>

using namespace std;

string number_to_mongolian(int number) {
    string names[] = {"хоосон", "нэг", "хоёр", "гурав", "дөрөв", "тав", "зургаан", "долоо", "найм", "есөн", "арван", "арван нэгэн", "арван хоёр", "арван гурав", "арван дөрөв", "арван тав", "арван зургаан", "арван долоо", "арван найм", "арван есөн"};
    
    string result = "";
    
    if (number == 0) {
        result = names[0];
    } else {
        if (number < 0) {
            result = "хураангуй " + number_to_mongolian(-number);
        } else {
            int digit = number % 10;
            int ten = (number / 10) % 10;
            if (ten == 1) {
                result = names[10 + digit];
            } else {
                if (digit > 0) {
                    result = names[digit];
                }
                if (ten > 0) {
                    if (!result.empty()) {
                        result = names[ten] + " " + result;
                    } else {
                        result = names[ten];
                    }
                }
            }
        }
    }
    
    return result;
}

int main() {
    int number;
    cout << "Гараас тоо оруулна уу: ";
    cin >> number;
    
    string mongolian_name = number_to_mongolian(number);
    cout << "Таны оруулсан тоо Монголоор: " << mongolian_name << endl;
    
    return 0;
}
