#include <iostream>

class Counter {
private:
    int total;

public:
    Counter(int start) {
        total = start;                          // !!!
    }

    void add_up_to(int n) {
        for (int i = 1; i <= n; i++) {          // !!!
            total += i;                         // !!!
        }
    }

    int get_total() {
        return total;                           // !!!
    }
};

int adjust(int value) {
    if (value % 2 == 0) {                       // !!!
        return value / 2;                   
    } else {                                    // !!!
        return value * 3 + 1;                   // !!!
    }
}

int main() {
    Counter c(5);                               // !!!

    c.add_up_to(3);                             // !!!

    int result = adjust(c.get_total());         // !!!

    std::cout << "Result: " << result << "\n";  // !!!
    return 0;                                   // !!!
}