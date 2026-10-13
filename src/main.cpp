#include <iostream>
#include <string>
#include <vector>
#include <cctype>

// Memecah teks menjadi daftar kata (huruf kecil, tanpa tanda baca)
std::vector<std::string> tokenize(const std::string& teks) {
    std::vector<std::string> hasil;
    std::string kata;

    for (char c : teks) {
        if (std::isalnum(static_cast<unsigned char>(c))) {
            kata += static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
        } else if (!kata.empty()) {
            hasil.push_back(kata);
            kata.clear();
        }
    }
    if (!kata.empty()) {
        hasil.push_back(kata);
    }
    return hasil;
}

int main() {
    std::string kalimat = "Belajar C++ itu seru, Belajar terus!";
    std::vector<std::string> daftarKata = tokenize(kalimat);

    for (const std::string& k : daftarKata) {
        std::cout << k << std::endl;
    }
    return 0;
}
