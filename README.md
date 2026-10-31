# MiniSearch

Mesin pencari dokumen sederhana yang ditulis dengan C++. Program membaca file `.txt` dari folder `data/`, membangun inverted index, lalu mencari dokumen lewat terminal atau halaman web lokal.

<!-- Setelah punya tangkapan layar, simpan di docs/screenshot.png lalu hapus tanda komentar:
![Tampilan MiniSearch](docs/screenshot.png)
-->

## Fitur

- Tokenizer: memecah teks menjadi kata (huruf kecil, tanpa tanda baca)
- Inverted index: mencatat kata ada di dokumen mana dan berapa kali muncul
- Pencarian beberapa kata (dokumen harus memuat semua kata)
- Peringkat hasil berdasarkan jumlah kemunculan kata
- Pencarian interaktif di terminal
- Antarmuka web yang terhubung ke server C++ lokal
- Tes otomatis untuk tokenizer dan pencarian

## Cara kerja

1. Semua file `.txt` di `data/` dibaca saat program dinyalakan.
2. Tiap dokumen dipecah menjadi kata oleh tokenizer.
3. Kata-kata dicatat ke inverted index: `kata -> (nomor dokumen -> jumlah kemunculan)`.
4. Saat mencari, kata yang diketik dirapikan dengan tokenizer yang sama, lalu dicocokkan ke indeks tanpa membaca ulang file.
5. Dokumen yang memuat semua kata diberi skor (total kemunculan) dan diurutkan dari yang tertinggi.

## Struktur folder

```
src/        kode C++ (tokenizer, indeks, pembaca dokumen, server, mode terminal)
tests/      tes otomatis
web/        halaman pencarian (HTML, CSS, JavaScript)
data/       dokumen contoh yang dicari
```

## Cara menjalankan

Perintah di bawah ditulis untuk Windows dengan MSYS2 (UCRT64) dan dijalankan dari folder proyek. Butuh compiler dengan dukungan C++17.

**Mode terminal**

```
g++ -std=c++17 -Isrc src/main.cpp src/tokenizer.cpp src/indeks.cpp src/dokumen.cpp -o minisearch
./minisearch
```

Ketik kata untuk mencari, atau `keluar` untuk berhenti.

**Mode web**

```
g++ -std=c++17 -D_WIN32_WINNT=0x0A00 -Isrc src/server.cpp src/tokenizer.cpp src/indeks.cpp src/dokumen.cpp -o server -lws2_32
./server
```

Lalu buka `http://localhost:8080` di browser. Server hanya menerima koneksi dari komputer yang sama (`127.0.0.1`). Tekan Ctrl + C untuk berhenti.

## Menjalankan tes

```
g++ -std=c++17 tests/tes.cpp src/tokenizer.cpp src/indeks.cpp -o tes
./tes
```

Hasil yang diharapkan: `Semua tes lulus.`

## Memakai dokumenmu sendiri

Taruh file `.txt` di folder `data/`, lalu jalankan ulang program. Indeks dibangun ulang setiap kali program dinyalakan.

## Keterbatasan

- Hanya membaca file `.txt`.
- Tokenizer membuang tanda baca, jadi `C++` menjadi `c`.
- Pencarian beberapa kata hanya mode "semua kata harus ada".
- Skor hanya menghitung jumlah kemunculan (belum memakai TF-IDF), sehingga dokumen panjang cenderung unggul.
- Indeks tidak disimpan ke file dan dibangun ulang setiap kali program berjalan.
- Perintah kompilasi di atas khusus Windows (`-lws2_32`).

## Pustaka pihak ketiga

- [cpp-httplib](https://github.com/yhirose/cpp-httplib) oleh yhirose untuk server HTTP (`src/httplib.h`). Lihat lisensinya di repositori aslinya.

## Rencana

- Menyorot kata pencarian pada cuplikan hasil
- Peringkat dengan TF-IDF
- Menyimpan indeks ke file
