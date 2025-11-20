#include <iostream>
#include <string>

int evalFullyParenthesized(const std::string& expr);
int evalStandard(const std::string& expr);

int main() {
    std::string line;
    
    // read lines from standard input forever
    while (std::getline(std::cin, line)) {
        if (line.empty()) continue;
        // parse input: fpie|standard
        size_t sep = line.find('|');
        if (sep == std::string::npos) {
            std::cerr << "Invalid format: " << line << std::endl;
            continue;
        }
        std::string mode = line.substr(0, sep);
        std::string expr = line.substr(sep + 1);
        // evaluate expression
        try {
            int result;
            if (mode == "fpie") {
                result = evalFullyParenthesized(expr);
            } else if (mode == "standard") {
                result = evalStandard(expr);
            } else {
                std::cerr << "Unknown mode: " << mode << std::endl;
                continue;
            }
            std::cout << result << std::endl;
        } catch (const std::exception& e) {
            // catch errors (throw) and report
            std::cerr << e.what() << std::endl;
        }
    }
    
    return 0;
}