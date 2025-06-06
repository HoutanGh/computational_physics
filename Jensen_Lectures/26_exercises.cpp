#include <iostream>
#include <cmath>
#include <string>
#include <bitset>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>


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

// 

struct exe2 {
    long long N;
    float singleDiff;
    double doubleDiff;
};


void exercise2() {
    std::cout << "Exercise 2: Series Summation\n";
    long long maxN;

    std::cout <<  "Enter the max N: ";
    std::cin  >> maxN;

    std::vector<long long> intervals;
    for (long long i = 1; i <= maxN; i *= 10) {
        intervals.push_back(i);
    }

    if (intervals.back() != maxN) {
        intervals.push_back(maxN);
    }

    std::vector<exe2> results;

    std::ofstream outFile("exe2.csv");
    outFile << std::setprecision(15) << std::scientific;
    outFile << "N, Single Diff, Double Diff\n";

    


    // this was 1. but not needed since doing the steps
    // for (long long i = 1; i <= N; i++) {
    //     s_up_single += 1.0f / i;
    //     s_up_double += 1.0 / i;
    // }

    
    // for (long long i = N; i >= 1; i--) {
    //     s_down_single += 1.0f / i;
    //     s_down_double += 1.0 / i;
    // }

    // relative differences for single and double precision
    
    // float relativeDifferenceSingle = std::abs(s_up_single - s_down_single) /
    //                                  std::max(s_up_single, s_down_single);
    
    // double relativeDifferenceDouble = std::abs(s_up_double - s_down_double) /
    //                                   std::max(s_up_double, s_down_double);

    for (auto N : intervals) {

        float s_up_single = 0.0f;
        double s_up_double = 0.0;
        float s_down_single = 0.0f;
        double s_down_double = 0.0;

        for (long long j = 1; j <= N; j++) {
            s_up_single += 1.0f / j;
            s_up_double += 1.0 / j;
        }

        
        for (long long j = N; j >= N; j--) {
            s_down_single += 1.0f / j;
            s_down_double += 1.0 / j;
        }

        float relativeDifferenceSingle = std::abs(s_up_single - s_down_single) /
                                         std::max(s_up_single, s_down_single);
        
        double relativeDifferenceDouble = std::abs(s_up_double - s_down_double) / 
                                          std::max(s_up_double, s_down_double);
        

        results.push_back({N, relativeDifferenceSingle, relativeDifferenceDouble});
    }

    std::sort(results.begin(), results.end(), [](const exe2 &a, const exe2 &b) {
        return a.N < b.N;
    });


    // file and console
        for (const auto &result : results) {
            outFile << result.N << "," << result.singleDiff << "," << result.doubleDiff << "\n";
            std::cout << std::fixed << std::setprecision(15); // High precision for console
            std::cout << "N = " << result.N
                    << " | Single Diff = " << result.singleDiff
                    << " | Double Diff = " << result.doubleDiff << "\n";
        }
        

    outFile.close();
}
// exercise 3

long double sine_series(double x, int terms = 100) {
    double result = 0.0;
    double term = x;
    int sign = 1;

    for (int n = 1; n <= terms; n+= 2) {
        result += sign * term;
        sign *= -1;
        term *= x * x / ((n + 1) + (n + 2));
    }

    return result;
}
double reduce_range(double x) {
    return fmod(x + M_PI, 2 * M_PI) - M_PI;  // ensures x is in [-π, π]
}

double compute(double x) {
    if (std::abs(x) < 1.9) {
        return x - sine_series(x);
    } else {
        return x - std::sin(x);
    }
}
void exercise3() {
    std::cout << "Exercise 3: sine expansion\n";
    
    double x_start, x_end, step;
    std::cout << "Enter start of range (x_start): ";
    std::cin >> x_start;
    std::cout << "Enter end of range (x_end): ";
    std::cin >> x_end;
    std::cout << "Enter step size: ";
    std::cin >> step;

    std::cout << std::fixed << std::setprecision(8);
    std::cout << "\n   x\t\tf(x)\n";
    std::cout << "-------------------------\n";

    for (double x = x_start; x <= x_end; x += step) {
        // setw doesnt change precision just the decimal points
        std::cout << std::setw(8) << x << "\t" << compute(reduce_range(x)) << "\n"; 
    }

}


int main() {
    while (true) {
        std::cout << "\nSelect and exercise (1-8, 0 to exit):\n";
        std::cout << "1. Decimal to Binary Conversion\n";
        std::cout << "2. Single, Doubl precision\n";
        std::cout << "3. Sine Series Expansion\n";
    

        int choice;
        std::cin >> choice;

        switch (choice) {
            case 1: exercise1(); break;
            case 2: exercise2(); break;
            case 3: exercise3(); break;
            case 0: std::cout << "Exiting...\n"; return 0;
            default: std::cout << "Invalid choice. Try again.\n";
        }
    }
}