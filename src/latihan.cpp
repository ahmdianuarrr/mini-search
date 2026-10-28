#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <cctype>
#include <fstream>
#include <sstream>
#include <filesystem>
using namespace std;
namespace fs = std::filesystem;

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

string bacaFile(const fs::path& lokasi) {
    ifstream file(lokasi);
    stringstream isi;
    isi << file.rdbuf();
    return isi.str();
}

void muatDokumen(string folder, vector<string>& dokumen, vector<string>& namaFile) {
    for (const auto& item : fs::directory_iterator(folder)) {
        if (item.path().extension() == ".txt") {
            dokumen.push_back(bacaFile(item.path()));
            namaFile.push_back(item.path().filename().string());
        }
    }
}

int main() {
    vector<string> dokumen;
    vector<string> namaFile;

    if (!fs::exists("data")) {
        cout << "Folder 'data' tidak ditemukan." << endl;
        return 1;
    }

    muatDokumen("data", dokumen, namaFile);

    if (dokumen.empty()) {
        cout << "Tidak ada file .txt di folder 'data'." << endl;
        return 1;
    }

    map<string, set<int>> indeks = bangunIndeks(dokumen);
    cout << dokumen.size() << " dokumen dimuat. Ketik kata, atau 'keluar'." << endl;

    while (true) {
        cout << endl << "Cari: ";
        string masukan;

        if (!getline(cin, masukan) || masukan == "keluar") {
            break;
        }

        set<int> hasil = cari(indeks, masukan);

        if (hasil.empty()) {
            cout << "Tidak ditemukan." << endl;
        } else {
            cout << hasil.size() << " dokumen ditemukan:" << endl;
            for (int id : hasil) {
                cout << "- " << namaFile[id] << endl;
            }
        }
    }

    cout << "Sampai jumpa!" << endl;
    return 0;
}