#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <cctype>
using namespace std;

vector<string> tokenize(string teks) {
    vector<string> hasil;
    string kata;

    for (int i = 0; i < teks.size(); i++) {
        char huruf = tolower(teks[i]);

        if (isalnum(huruf)) {
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

map<string, set<int>> bangunIndeks(const vector<string>& dokumen) {
    map<string, set<int>> indeks;

    for (int id = 0; id < dokumen.size(); id++) {
        vector<string> daftarKata = tokenize(dokumen[id]);

        for (int j = 0; j < daftarKata.size(); j++) {
            indeks[daftarKata[j]].insert(id);
        }
    }

    return indeks;
}

set<int> cari(const map<string, set<int>>& indeks, string kata) {
    set<int> kosong;

    vector<string> token = tokenize(kata);
    if (token.empty()) {
        return kosong;
    }

    auto ketemu = indeks.find(token[0]);
    if (ketemu == indeks.end()) {
        return kosong;
    }

    return ketemu->second;
}

int main() {
    vector<string> dokumen = {
        "Belajar C++ itu seru",
        "Belajar Python juga seru",
        "Mesin pencari memakai inverted index"
    };

    map<string, set<int>> indeks = bangunIndeks(dokumen);

    cout << "=== Isi indeks ===" << endl;
    for (auto pasangan : indeks) {
        cout << pasangan.first << " ->";
        for (int id : pasangan.second) {
            cout << " " << id;
        }
        cout << endl;
    }

    vector<string> kataUji = {"belajar", "python", "kucing"};

    for (int i = 0; i < kataUji.size(); i++) {
        set<int> hasil = cari(indeks, kataUji[i]);

        cout << endl << "Mencari: " << kataUji[i] << endl;

        if (hasil.empty()) {
            cout << "Tidak ditemukan." << endl;
        } else {
            for (int id : hasil) {
                cout << "- [" << id << "] " << dokumen[id] << endl;
            }
        }
    }

    return 0;
}