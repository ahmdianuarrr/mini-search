const kotak = document.getElementById("kata");
const tombol = document.getElementById("tombol");
const hasil = document.getElementById("hasil");

async function cari() {
    const kata = kotak.value.trim();

    if (kata === "") {
        hasil.textContent = "";
        return;
    }

    hasil.textContent = "Mencari...";

    try {
        const respons = await fetch("/cari?q=" + encodeURIComponent(kata));
        const data = await respons.json();
        tampilkan(data);
    } catch (galat) {
        hasil.textContent = "Gagal terhubung ke server.";
    }
}

function kataKueri(kata){
    return kata()
    .tolowerCase
    .split(/[^a-z0-9]+/)
    .filter(function (k) { return k !== ""; });

}

function sorot(teks, daftarKata) {
    const wadah = document.createElement("p");
    const potongan = teks.split(/([a-zA-Z0-9]+)/);

    for (const bagian of potongan) {
        if (daftarKata.includes(bagian.toLowerCase())) {
            const tanda = document.createElement("mark");
            tanda.textContent = bagian;
            wadah.appendChild(tanda);
        } else {
            wadah.appendChild(document.createTextNode(bagian));
        }
    }

    return wadah;
}

function tampilkan(data, kata) {
    const daftarKata = KataKueri(kata)
    hasil.textContent = "";

    const info = document.createElement("p");
    info.textContent = data.jumlah + " dokumen ditemukan";
    hasil.appendChild(info);

    for (const item of data.hasil) {
        const kartu = document.createElement("div");
        kartu.className = "kartu";

        const judul = document.createElement("strong");
        judul.textContent = item.nama + " (skor " + item.skor + ")";

       const isi = sorot(item.cuplikan, daftarKata);
       
        kartu.appendChild(judul);
        kartu.appendChild(isi);
        hasil.appendChild(kartu);
    }
}

tombol.addEventListener("click", cari);
kotak.addEventListener("keydown", function (e) {
    if (e.key === "Enter") {
        cari();
    }
});