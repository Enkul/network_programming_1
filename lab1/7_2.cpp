#include <iostream>
#include <math.h>
using namespace std;

int main () {
    float height,weight,overweight;
    cin >> height >> weight;
    // BMI = kg/m2 where kg is a person's weight in kilograms and m2 is their height in metres squared. A BMI of 25.0 or more is overweight, while the healthy range is 18.5 to 24.9. BMI applies to most adults 18-65 years.
    float bmi = weight / pow(height,2) * 10000;
    if ( bmi > 18.5 && bmi < 24.9) {
        cout << "healthy";
    }
    else if (bmi > 24.9) {
        overweight = 0.002 * pow(height,2) - weight;
        cout << "overweight: " << overweight << endl;
    }
    else {
        overweight = 0.002 * pow(height,2) - weight;
        cout << "underweight: " << overweight << endl;
    }
}