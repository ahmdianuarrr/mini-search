#include "tokenizer.h"
#include <cctype>

std::vector<std::string> tokenize(const std::string& teks) {
    std::vector<std::string> hasil;
    std::string kata;

    for (int i = 0; i < teks.size(); i++) {
        char huruf = std::tolower(static_cast<unsigned char>(teks[i]));

        if (std::isalnum(static_cast<unsigned char>(huruf))) {
            kata += huruf;
        } else {
            if (!kata.empty()) {
                hasil.push_back(kata);
                kata.clear();
            }
        }
    }

    if (!kata.empty()) {
        hasil.push_back(kata);
    }

    return hasil;
}