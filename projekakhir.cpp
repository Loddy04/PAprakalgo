#include <iostream>
using namespace std;

// Fungsi untuk menampilkan menu utama
void tampilkanMenu() {
    cout << "~~ Menu Sistem Laporan Keluhan Mahasiswa UPNVYK ~~\n";
    cout << "1. Muat Keluhan dari File\n";
    cout << "2. Buat Keluhan Baru\n";
    cout << "3. Tampilkan Keluhan Berdasarkan Kategori\n";
    cout << "4. Cari Keluhan\n";
    cout << "5. Urutkan Keluhan\n";
    cout << "6. Hapus Keluhan\n";
    cout << "7. Keluar\n";
}

struct Keluhan {
    int id;
    string nama;
    string kategori;
    string isi;
    Keluhan *next; //linked list
};

Keluhan *temp = nullptr;

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
    return;
}

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
}


int main () {
    int pilih;

    do {
        tampilkanMenu();
        cout << "Masukkan menu yang dipilih : "; cin >> pilih; 

        switch (pilih) {
            case 1: 
                // muat keluhan dulu
                break;
            case 2: 
                buatKeluhan();
                break;
            case 3: 
                tampilKeluhan();
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