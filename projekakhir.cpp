#include <iostream>
using namespace std;

struct Keluhan {
    int id;
    char nama[50];
    char kategori[50];
    char isi[100];
    Keluhan *next; 
};

Keluhan *temp = nullptr; // !ampung awal sementara

// Fungsi untuk memuat keluhan dari file
void muatKeluhandariFile() {
    FILE *file = fopen("keluhan.txt", "r");
    if (file == nullptr) {
        cout << "Gagal membuka file\n";
        return;
    }

    Keluhan *bantu = nullptr; // sebagai navigasi bantu
    
    while (!feof(file)){
        Keluhan *baru = new Keluhan;
        baru->next = nullptr;

        if (fscanf(file, "%d %s %s %[^\n]\n", &baru->id, baru->nama, baru->kategori, baru->isi) != 4) {
            delete baru;
            break;
        }
        
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
    FILE *file = fopen("keluhan.txt", "w");
    if (file == nullptr) {
        cout << "Gagal membuka file\n";
        return;
    }

    Keluhan *bantu = temp;
    while (bantu != nullptr) {
        fprintf(file, "%d %s %s %s\n", bantu->id, bantu->nama, bantu->kategori, bantu->isi);
        bantu = bantu->next;
    }

    fclose(file);
    return;
}

// Fungsi untuk membuat keluhan baru
void buatKeluhan() {
    muatKeluhandariFile();
    Keluhan *baru = new Keluhan;

    cout << "Nama pelapor (cukup 1 kata) : "; cin >> baru->nama;
    cout << "Kategori keluhan (Fasilitas, Dosen) : "; cin >> baru->kategori; cin.ignore();
    cout << "Isi keluhan : \n"; cin.getline(baru->isi, 100);
    baru->next = nullptr;

    if (temp == nullptr) {
        baru->id = 1;
        temp = baru;
    } else {
        Keluhan *bantu = temp;
        while (bantu->next != nullptr) {
            bantu = bantu->next;
        }
        baru->id = baru->id + 1;
        bantu->next = baru;
    }

    simpanKeluhan();
    cout << "Keluhan berhasil disimpan\n\n";

    system("pause");
    system("cls");
}

// Fungsi untuk menampilkan keluhan
void tampilKeluhan() {
    // muatKeluhandariFile();
    if (temp == nullptr) {
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

void cariNama() {
    char cari[50];
    cout << "Masukkan nama pelapor yang dicari : "; cin >> cari;
    Keluhan *bantu = temp;
    while (bantu != nullptr) {
        if (bantu->nama == cari) {
            cout << "Pelapor ke : " << bantu->id << endl;
            cout << "Nama pelapor : " << bantu->nama << endl;
            cout << "Kategori keluhan : " << bantu->kategori << endl;
            cout << "Isi keluhan : \n"; 
            cout << bantu->isi << endl;
        }
        bantu = bantu->next;
    }
}

void cariTopik() {
    char cari[50];
    cout << "Masukkan kategori keluhan yang dicari : "; cin >> cari;
    Keluhan *bantu = temp;
    while (bantu != nullptr) {
        if (bantu->kategori == cari) {
            cout << "Pelapor ke : " << bantu->id << endl;
            cout << "Nama pelapor : " << bantu->nama << endl;
            cout << "Kategori keluhan : " << bantu->kategori << endl;
            cout << "Isi keluhan : \n"; 
            cout << bantu->isi << endl;
        }
        bantu = bantu->next;
    }
}

void cariKeluhan() {
    int pilih;
    cout << "~~ Menu Pencarian Keluhan ~~\n";
    cout << "1. Cari berdasarkan nama pelapor\n";
    cout << "2. Cari berdasarkan kategori keluhan\n";
    cout << "3. Kembali ke menu utama\n";
    cout << "Masukkan pilihan : "; cin >> pilih;

    switch (pilih) {
        case 1:
            cariNama();
            break;
        case 2:
            cariTopik();
            break;
        case 3:
            return;
        default:
            cout << "Pilihan tidak valid, silakan coba lagi.\n";
            break;
    }
}

// Fungsi untuk menghapus keluhan
void hapusKeluhan() {
    muatKeluhandariFile();
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
    cout << ":===========================================:\n";
    cout << "|   Menu Sistem Laporan Keluhan Mahasiswa   |\n";
    cout << "|         UPN 'Veteran' Yogyakarta          |\n";
    cout << "|===========================================|\n";
    cout << "| 1. Buat Keluhan Baru                      |\n";
    cout << "| 2. Tampilkan Keluhan Berdasarkan Kategori |\n";
    cout << "| 3. Cari Keluhan                           |\n";
    cout << "| 4. Urutkan Keluhan                        |\n";
    cout << "| 5. Hapus Keluhan                          |\n";
    cout << "| 6. Keluar                                 |\n";
    cout << ":===========================================:\n";
}

int main () {
    int pilih;
    do {
        tampilkanMenu();
        cout << "Masukkan menu yang dipilih : "; cin >> pilih; 
        switch (pilih) {
            case 1: 
                system("cls");
                buatKeluhan();
                break;
            case 2: 
                tampilKeluhan();
                break;
            case 3: 
                cariKeluhan();
                break;
            case 4: 
                // urutkan keluhan
                break;
            case 5:
                hapusKeluhan();
                break;
            case 6:
                cout << ":=============================================:\n";
                cout << "| Terima kasih telah membuat laporan keluhan. |\n";
                cout << "|      Keluhan akan segera kami proses.       |\n";
                cout << ":=============================================:\n";
                break;
            default:
                cout << "\n!! <Menu tidak valid, silakan coba lagi.> !!\n";
                break;
        }
    } while (pilih < 8);

    return 0;
}