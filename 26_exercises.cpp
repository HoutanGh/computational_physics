#include <iostream>
#include <cmath>
#include <string>
#include <bitset>


void exercise1(){

    double number;
    std::cout << "Exercise 1: Decimal to Binary Conversion\n";
    std::cout << "Enter a decimal number: ";
    std::cin >> number;


    if (number < 0) {
        number = -number;
    }
    // split into integer part and decimal part

    int integerPart = static_cast<int>(number);
    double decimalPart = number - integerPart;

    std::string binaryInteger = "";
    while (integerPart > 0) {
        binaryInteger = std::to_string(integerPart % 2) + binaryInteger;
        integerPart /= 2;
    }
    
    std::string binaryDecimal = "";
    int precision = 32;

    while (decimalPart > 0 && precision > 0) {
        // just the standard way to get binary repr of decimal part
        decimalPart *= 2;
        if (decimalPart >= 1) {
            binaryDecimal += "1";
            decimalPart -= 1;
        } else {
            binaryDecimal += "0";
        }
        precision--;

    }

    // edge cases
    std::string binaryRepresentation = binaryInteger;
    if (!binaryDecimal.empty()) {
        binaryRepresentation += "." + binaryDecimal;
    }

    if (number < 0) {
        binaryRepresentation = "-" + binaryRepresentation;
    }

    std::cout << "Binary representation: " << binaryRepresentation << "\n";

}




int main() {
    while (true) {
        std::cout << "\nSelect and exercise (1-8, 0 to exit):\n";
        std::cout << "1. Decimal to Binary Conversion\n";
    

        int choice;
        std::cin >> choice;

        switch (choice) {
            case 1: exercise1(); break;
            case 0: std::cout << "Exiting...\n"; return 0;
            default: std::cout << "Invalid choice. Try again.\n";
        }
    }
}