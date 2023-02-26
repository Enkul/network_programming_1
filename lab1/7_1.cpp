#include <iostream>
#include <utility>
#include <math.h>
using namespace std;
pair<int,int> t[3];
bool check(float a,float b,float c) {
    if (a + b > c || a + c > b || b + c > a) return true;
    return false;

}

float area(float a,float b,float c) {
    float s = (a + b + c) / 2;
    return sqrt(s * (s - a) * (s - b) * (s - c));
}
// float findLength(int x,int y) {
    
// }
int main() {
    for (int i = 0; i < 3; i++) {
        cout << "pls, give me coordinate: ";
        cin >> t[i].first >> t[i].second;
    }
    float a = (float)sqrt(pow((t[1].first - t[0].first),2) + pow((t[1].second - t[0].second),2));
    float b = (float)sqrt(pow((t[2].first - t[0].first),2) + pow((t[2].second - t[0].second),2));
    float c = (float)sqrt(pow((t[2].first - t[1].first),2) + pow((t[2].second - t[1].second),2));
    // cout <<  true ? "hello world" : "qwer";
    cout << "a: " << a << endl;
    cout << "b: " << b << endl;
    cout << "c: " << c << endl;
    if (check(a,b,c)) {
        cout << area(a,b,c) << endl;
    } else {
        cout << "doesn't exist triangle";
    }

    // cout << check(a,b,c) ? area(a,b,c) : "doesn't exist triangle";
    
}