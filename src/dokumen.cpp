#include "dokumen.h"
#include <filesystem>
#include <fstream>
#include <sstream>

namespace fs = std::filesystem;

static std::string bacaFile(const fs::path& lokasi) {
    std::ifstream file(lokasi);
    std::stringstream isi;
    isi << file.rdbuf();
    return isi.str();
}

void muatDokumen(const std::string& folder,
                 std::vector<std::string>& dokumen,
                 std::vector<std::string>& namaFile) {
    for (const auto& item : fs::directory_iterator(folder)) {
        if (item.path().extension() == ".txt") {
            dokumen.push_back(bacaFile(item.path()));
            namaFile.push_back(item.path().filename().string());
        }
    }
}