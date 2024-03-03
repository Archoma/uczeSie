#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

void drawTable(const std::vector<std::string>& rows) {
    size_t max_length = 0;
    for (const auto& row : rows) {
        if (row.length() > max_length) {
            max_length = row.length();
        }
    }

    // Unicode Box Drawing characters
    char topLeft = 0xDA, topRight = 0xBF, horizontal = 0xC4, vertical = 0xB3,
         bottomLeft = 0xC0, bottomRight = 0xD9;

    // Górna krawędź
    std::cout << topLeft << std::string(max_length + 2, horizontal) << topRight << std::endl;

    // Wiersze
    for (const auto& row : rows) {
        std::cout << vertical << ' ' << row << std::string(max_length - row.length(), ' ') << ' ' << vertical << std::endl;
    }

    // Dolna krawędź
    std::cout << bottomLeft << std::string(max_length + 2, horizontal) << bottomRight << std::endl;
}

int main() {
    std::vector<std::string> rows = {
        "Header",
        "Row 1",
        "Row 2",
        "Row 3 with more text"
    };

    drawTable(rows);

    return 0;
}
