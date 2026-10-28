#include "indeks.h"
#include "tokenizer.h"
#include <algorithm>

Indeks bangunIndeks(const std::vector<std::string>& dokumen) {
    Indeks indeks;

    for (int id = 0; id < dokumen.size(); id++) {
        std::vector<std::string> daftarKata = tokenize(dokumen[id]);

        for (int j = 0; j < daftarKata.size(); j++) {
            indeks[daftarKata[j]][id]++;
        }
    }

    return indeks;
}

std::vector<std::pair<int, int>> cari(const Indeks& indeks, const std::string& kueri) {
    std::vector<std::string> token = tokenize(kueri);
    std::vector<std::pair<int, int>> hasil;

    if (token.empty()) {
        return hasil;
    }

    std::map<int, int> skor;
    bool pertama = true;

    for (int i = 0; i < token.size(); i++) {
        std::map<int, int> kataIni;

        auto ketemu = indeks.find(token[i]);
        if (ketemu != indeks.end()) {
            kataIni = ketemu->second;
        }

        if (pertama) {
            skor = kataIni;
            pertama = false;
        } else {
            std::map<int, int> baru;
            for (auto p : skor) {
                auto cocok = kataIni.find(p.first);
                if (cocok != kataIni.end()) {
                    baru[p.first] = p.second + cocok->second;
                }
            }
            skor = baru;
        }
    }

    for (auto p : skor) {
        hasil.push_back({p.first, p.second});
    }

    std::sort(hasil.begin(), hasil.end(),
        [](std::pair<int, int> a, std::pair<int, int> b) {
            if (a.second != b.second) {
                return a.second > b.second;
            }
            return a.first < b.first;
        });

    return hasil;
}