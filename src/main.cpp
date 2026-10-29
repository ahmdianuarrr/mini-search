#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#include "indeks.h"
#include "dokumen.h"
using namespace std;
namespace fs = std::filesystem;

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

    Indeks indeks = bangunIndeks(dokumen);
    cout << dokumen.size() << " dokumen dimuat. Ketik kata, atau 'keluar'." << endl;

    while (true) {
        cout << endl << "Cari: ";
        string masukan;

        if (!getline(cin, masukan) || masukan == "keluar") {
            break;
        }

        vector<pair<int, int>> hasil = cari(indeks, masukan);

        if (hasil.empty()) {
            cout << "Tidak ditemukan." << endl;
        } else {
            cout << hasil.size() << " dokumen ditemukan:" << endl;
            for (auto h : hasil) {
                cout << "- " << namaFile[h.first] << " (skor " << h.second << ")" << endl;
            }
        }
    }

    cout << "Sampai jumpa!" << endl;
    return 0;
}