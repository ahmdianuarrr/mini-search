#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
#include "httplib.h"
#include "indeks.h"
#include "dokumen.h"
using namespace std;

string escapeJson(const string& s) {
    string hasil;
    for (char c : s) {
        if (c == '"') {
            hasil += "\\\"";
        } else if (c == '\\') {
            hasil += "\\\\";
        } else if (static_cast<unsigned char>(c) < 0x20) {
            hasil += ' ';
        } else {
            hasil += c;
        }
    }
    return hasil;
}

int main() {
    vector<string> dokumen;
    vector<string> namaFile;

    if (!filesystem::exists("data")) {
        cout << "Folder 'data' tidak ditemukan." << endl;
        return 1;
    }

    muatDokumen("data", dokumen, namaFile);

    if (dokumen.empty()) {
        cout << "Tidak ada file .txt di folder 'data'." << endl;
        return 1;
    }

    Indeks indeks = bangunIndeks(dokumen);

    httplib::Server server;
    server.set_mount_point("/", "web");

    server.Get("/cari", [&](const httplib::Request& req, httplib::Response& res) {
        string kueri = req.get_param_value("q");
        vector<pair<int, int>> hasil = cari(indeks, kueri);

        string json = "{\"jumlah\":" + to_string(hasil.size()) + ",\"hasil\":[";

        for (int i = 0; i < hasil.size(); i++) {
            int id = hasil[i].first;
            string cuplikan = dokumen[id].substr(0, 100);

            if (i > 0) {
                json += ",";
            }
            json += "{\"nama\":\"" + escapeJson(namaFile[id]) + "\"";
            json += ",\"skor\":" + to_string(hasil[i].second);
            json += ",\"cuplikan\":\"" + escapeJson(cuplikan) + "\"}";
        }

        json += "]}";
        res.set_content(json, "application/json; charset=utf-8");
    });

    cout << dokumen.size() << " dokumen dimuat." << endl;
    cout << "Server berjalan di http://localhost:8080 (Ctrl + C untuk berhenti)" << endl;

    if (!server.listen("127.0.0.1", 8080)) {
        cout << "Gagal memulai server. Port 8080 mungkin sedang dipakai." << endl;
        return 1;
    }

    return 0;
}