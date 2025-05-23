
#include <iostream>
using namespace std;

struct Keluhan {
    int id;
    string nama;
    string kategori;
    string isi;
    Keluhan *next; 
};

Keluhan *temp = nullptr;

// Fungsi untuk memuat keluhan dari file
void muatKeluhandariFile() {
    FILE *file = fopen("keluhan.txt", "r");
    if (file == nullptr) {
        cout << "Gagal membuka file\n";
        return;
    }
    Keluhan *bantu = nullptr;
    while (!feof(file)) {
        Keluhan *baru = new Keluhan;
        fscanf(file, "%d %s %s %s\n", &baru->id, baru->nama.c_str(), baru->kategori.c_str(), baru->isi.c_str());
        baru->next = nullptr;
        if (temp == nullptr) {
            temp = baru;
            bantu = temp;
        } else {
            bantu->next = baru;
            bantu = bantu->next;
        }
    }
    fclose(file);
}

// Fungsi untuk menyimpan keluhan ke file
void simpanKeluhan() {
    Keluhan *bantu = temp;
    FILE *file = fopen("keluhan.txt", "w");
    if (file == nullptr) {
        cout << "Gagal membuka file\n";
        return;
    }
    while (bantu != nullptr) {
        fprintf(file, "%d %s %s %s\n", bantu->id, bantu->nama.c_str(), bantu->kategori.c_str(), bantu->isi.c_str());
        bantu = bantu->next;
    }

    fclose(file);
    cout << "Keluhan berhasil disimpan ke file\n";
    return;
}

// Fungsi untuk membuat keluhan baru
void buatKeluhan() {
    Keluhan *baru = new Keluhan;

    cout << "Nama pelapor : "; cin >> baru->nama;
    cout << "Kategori keluhan (Fasilitas, Dosen) : "; cin >> baru->kategori; cin.ignore();
    cout << "Isi keluhan : \n"; getline(cin, baru->isi);
    baru->next = nullptr;
    if (temp == nullptr) {
        baru->id = 1;
        temp = baru;
    } else {
        baru->id = baru->id++;
    }
    cout << "Keluhan berhasil disimpan\n";
    simpanKeluhan();
    return;
}

// Fungsi untuk menampilkan keluhan
void tampilKeluhan() {
    if (temp = nullptr) {
        cout << "Belum ada keluhan\n";
        return;
    } else {
        Keluhan *bantu = temp;
        while (bantu != nullptr) {
            cout << "Pelapor ke : " << bantu->id << endl;
            cout << "Nama pelapor : " << bantu->nama << endl;
            cout << "Kategori keluhan : " << bantu->kategori << endl;
            cout << "Isi keluhan : \n"; 
            cout << bantu->isi << endl;
            bantu = bantu->next;
        }
    }
    return;
}

void hapusKeluhan() {
    if (temp == nullptr) {
        cout << "Belum ada keluhan\n";
        return;
    } else {
        Keluhan *bantu = temp;
        Keluhan *hapus = nullptr;
        while (bantu != nullptr) {
            cout << "Pelapor ke : " << bantu->id << endl;
            cout << "Nama pelapor : " << bantu->nama << endl;
            cout << "Kategori keluhan : " << bantu->kategori << endl;
            cout << "Isi keluhan : \n"; 
            cout << bantu->isi << endl;
            bantu = bantu->next;
        }
    }
    simpanKeluhan();

}

// Fungsi untuk menampilkan menu utama
void tampilkanMenu() {
    cout << "~~ Menu Sistem Laporan Keluhan Mahasiswa UPNVYK ~~\n";
    cout << "1. Buat Keluhan Baru\n";
    cout << "2. Tampilkan Keluhan Berdasarkan Kategori\n";
    cout << "3. Cari Keluhan\n";
    cout << "4. Urutkan Keluhan\n";
    cout << "5. Hapus Keluhan\n";
    cout << "6. Keluar\n";
}

int main () {
    int pilih;
    muatKeluhandariFile();
    do {
        tampilkanMenu();
        cout << "Masukkan menu yang dipilih : "; cin >> pilih; 

        switch (pilih) {
            case 1: 
                buatKeluhan();
                break;
            case 2: 
                tampilKeluhan();
                break;
            case 3: 
                hapusKeluhan();
                break;
            case 4: 
                // cari keluhan berdasarkan nama || id
                break;
            case 5:
                // urutkan keluhan berdasarkan nama || id
                break;
            case 6:
                // hapus keluhan berdasarkan id
                break;
            case 7: 
                // keluar
                // makasih ya keluhan segera di pr
                break;
            default:
                break;

        }
    } while (pilih < 8);

}