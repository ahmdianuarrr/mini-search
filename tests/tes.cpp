#include <cassert>
#include <iostream>
#include "../src/tokenizer.h"
#include "../src/indeks.h"

void tesTokenizer() {
    std::vector<std::string> a = tokenize("HaLo, dunia !");
    assert(a.size() == 2);
    assert(a[0] == "halo");
    assert(a[1] == "dunia");

    assert(tokenize("halo dunia").size() == 2);
    assert(tokenize("a,,b").size() == 2);
    assert(tokenize("").empty());
    assert(tokenize("!!!").empty());
}

void tesCari() {
    std::vector<std::string> dokumen = {
        "belajar belajar seru",
        "belajar python",
        "film seru"
        "kereta argo ngawi jesgejes"
    };
    Indeks indeks = bangunIndeks(dokumen);

    auto a = cari(indeks, "belajar");
    assert(a.size() == 2);
    assert(a[0].first == 0);
    assert(a[0].second == 2);
    assert(a[1].first == 1);

    auto b = cari(indeks, "belajar seru");
    assert(b.size() == 1);
    assert(b[0].first == 0);
    assert(b[0].second == 3);

    assert(cari(indeks, "kereta").empty());
    assert(cari(indeks, "!!!").empty());
}

int main() {
    tesTokenizer();
    tesCari();
    std::cout << "Semua tes lulus." << std::endl;
    return 0;
}