#include <iostream>
#include <cstring>
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
    
    while (!feof(file)){ //membaca sampai baris terakhir file
        Keluhan *baru = new Keluhan;
        baru->next = nullptr;

        if (fscanf(file, "%d %s %s %[^\n]\n", &baru->id, baru->nama, baru->kategori, baru->isi) != 4) {
            // jika record yang diambil tidak memenuho 4 variabel maka akan dihapus dan pembacaan berhenti
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
    // semua yang ada di linked ist ditulis ulang ke dalam file
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
    Keluhan *baru = new Keluhan;
    cout << "+> Buat Laporan Keluhan\n\n";

    cout << "Nama pelapor (cukup 1 kata) : "; 
    cin >> baru->nama;

    int pilih;
    cout << "Kategori keluhan\n"; 
    cout << "1. Fasilitas\n";
    cout << "2. Pelayanan\n";
    cout << "3. Dosen\n";
    cout << "Pilih kategori keluhan      : "; 
    cin >> pilih;
    switch (pilih) {
    case 1:
        strcpy(baru->kategori, "Fasilitas"); // menyalin 1 gaya string ke memori string lain
        break;
    case 2:
        strcpy(baru->kategori, "Pelayanan"); 
        break;
    case 3:
        strcpy(baru->kategori, "Dosen"); 
        break;
    default:
        cout << "Pilihan tidak valid!\n";
        break;
    }

    cin.ignore();
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
        baru->id = bantu->id + 1;
        bantu->next = baru;
    }

    simpanKeluhan();
    cout << endl;
    cout << ":============================:\n";
    cout << "| Keluhan berhasil disimpan. |\n";
    cout << ":============================:\n";

    system("pause");
    system("cls");
}

// Fungsi untuk menampilkan keluhan
void tampilKeluhan() {
    cout << "+> Laporan Keluhan\n\n";

    if (temp == nullptr) {
        cout << "Belum ada keluhan.\n";
        return;
    } 

    Keluhan *bantu = temp;
    while (bantu != nullptr) {
        cout << ":==============================================:\n";
        cout << "| Pelapor ke : " << bantu->id << endl;
        cout << "|----------------------------------------------\n";
        cout << "| Nama pelapor : " << bantu->nama << endl;
        cout << "| Kategori keluhan : " << bantu->kategori << endl;
        cout << "| Isi keluhan : \n"; 
        cout << "|----------------------------------------------\n";
        cout << "| " << bantu->isi << endl;
        cout << ":==============================================:\n\n";
        bantu = bantu->next;
    }

    system("pause");
    system("cls");
}

void cariId() {
    cout << "+> Cari keluhan berdasarkan ID\n\n";

    int cari;
    cout << "Masukkan ID pelapor yang dicari : "; cin >> cari;

    Keluhan *bantu = temp;
    bool ditemukan = false;
    while (bantu != nullptr) {
        if (bantu->id == cari) {
            cout << ":==============================================:\n";
            cout << "| Pelapor ke : " << bantu->id << endl;
            cout << "| Nama pelapor : " << bantu->nama << endl;
            cout << "| Kategori keluhan : " << bantu->kategori << endl;
            cout << "| Isi keluhan : \n";
            cout << "| " << bantu->isi << endl;
            cout << ":==============================================:\n\n";
            ditemukan = true;
        }
        bantu = bantu->next;
    }

    if (!ditemukan) {
        cout << "Keluhan dengan ID tersebut tidak ditemukan.\n";
    }

    system("pause");
    system("cls");
}

void cariNama() {
    cout << "+> Cari keluhan berdasarkan nama\n\n";

    char cari[50];
    cout << "Masukkan nama pelapor yang dicari : "; cin >> cari;

    Keluhan *bantu = temp;
    bool ditemukan = false;
    while (bantu != nullptr) {
        if (strcmp(bantu->nama, cari) == 0) {
            cout << ":==============================================:\n";
            cout << "| Pelapor ke : " << bantu->id << endl;
            cout << "| Nama pelapor : " << bantu->nama << endl;
            cout << "| Kategori keluhan : " << bantu->kategori << endl;
            cout << "| Isi keluhan : \n";
            cout << "| " << bantu->isi << endl;
            cout << ":==============================================:\n\n";
            ditemukan = true;
        }
        bantu = bantu->next;
    }

    if (!ditemukan) {
        cout << "Keluhan dengan nama tersebut tidak ditemukan.\n";
    }

    system("pause");
    system("cls");
}  

void cariKeluhan() {
    cout << "+> Cari keluhan \n\n";
    
    int pilih;
    cout << ":======================================:\n";
    cout << "|        Menu Pencarian Keluhan        |\n";
    cout << ":======================================:\n";
    cout << "| 1. Cari berdasarkan ID pelapor       |\n";
    cout << "| 2. Cari berdasarkan nama pelapor     |\n";
    cout << "| 3. Kembali ke menu utama             |\n";
    cout << ":======================================:\n";
    cout << "Masukkan pilihan : "; cin >> pilih;

    switch (pilih) {
        case 1:
            system("cls");
            cariId();
            break;
        case 2:
            system("cls");
            cariNama();
            break;
        case 3:
            return;
        default:
            cout << "Pilihan tidak valid, silakan coba lagi.\n";
            break;
    }
}


void tukarData(Keluhan *a, Keluhan *b) {
    int tempId = a->id;
    char tempNama[50], tempKategori[50], tempIsi[100];
    
    strcpy(tempNama, a->nama);
    strcpy(tempKategori, a->kategori);
    strcpy(tempIsi, a->isi);
    
    a->id = b->id;
    strcpy(a->nama, b->nama);
    strcpy(a->kategori, b->kategori);
    strcpy(a->isi, b->isi);
    
    b->id = tempId;
    strcpy(b->nama, tempNama);
    strcpy(b->kategori, tempKategori);
    strcpy(b->isi, tempIsi);
}
void urutkanById() {
    if (temp == nullptr || temp->next == nullptr) return;
    
    bool swapped;
    Keluhan *ptr1;
    Keluhan *lptr = nullptr;
    
    do {
        swapped = false;
        ptr1 = temp;
        
        while (ptr1->next != lptr) {
            if (ptr1->id > ptr1->next->id) {
                tukarData(ptr1, ptr1->next);
                swapped = true;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}
void urutkanByNama() {
    if (temp == nullptr || temp->next == nullptr) return;
    
    bool swapped;
    Keluhan *ptr1;
    Keluhan *lptr = nullptr;
    
    do {
        swapped = false;
        ptr1 = temp;
        
        while (ptr1->next != lptr) {
            if (strcmp(ptr1->nama, ptr1->next->nama) > 0) {
                tukarData(ptr1, ptr1->next);
                swapped = true;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}

void urutkanKeluhan() {
    cout << "+> Urutkan Keluhan\n\n";
    
    int pilih;
    cout << ":======================================:\n";
    cout << "|        Menu Pengurutan Keluhan       |\n";
    cout << ":======================================:\n";
    cout << "| 1. Urutkan berdasarkan ID            |\n";
    cout << "| 2. Urutkan berdasarkan nama pelapor  |\n";
    cout << "| 3. Kembali ke menu utama             |\n";
    cout << ":======================================:\n";
    cout << "Masukkan pilihan : "; cin >> pilih;

    switch (pilih) {
        case 1:
            urutkanById();
            cout << "\nKeluhan berhasil diurutkan berdasarkan ID!\n";
            break;
        case 2:
            urutkanByNama();
            cout << "\nKeluhan berhasil diurutkan berdasarkan nama pelapor!\n";
            break;
        case 3:
            return;
        default:
            cout << "Pilihan tidak valid, silakan coba lagi.\n";
            break;
    }
    
    simpanKeluhan();
    system("pause");
    system("cls");
}

// Fungsi untuk menghapus keluhan
void hapusKeluhan() {
    cout << "+> Hapus laporan keluhan \n\n";

    if (temp == nullptr) {
        cout << "Belum ada keluhan\n";
        return;
    } 

    char cari[50];
    cout << "Masukkan nama pelapor yang ingin dihapus : "; cin >> cari;

    Keluhan *hapus;
    // masih error belum bisa nangkep nama yang di cari
    if (strcmp(temp->nama, cari) == 0) {
        // jika record yang dihapus berada di paling depan
        // strcmp membandingkan string tipe char
        hapus = temp;
        temp = temp->next;
        delete hapus;
    } else {
        Keluhan *bantu = temp;
        while (bantu->next != nullptr && strcmp(bantu->next->nama, cari) != 0) {
            bantu = bantu->next;
        }

        if(bantu->next == nullptr) {
            cout << "\n !! Keluhan dengan nama <" << cari << "> tidak ada !!\n\n";
            system("pause");
            system("cls");
            return;
        }

        cout << ":==============================================:\n";
        cout << "| Nama pelapor : " << bantu->next->nama << endl;
        cout << "| Kategori keluhan : " << bantu->next->kategori << endl;
        cout << "| Isi keluhan : \n"; 
        cout << "|----------------------------------------------\n";
        cout << "| " << bantu->next->isi << endl;
        cout << ":==============================================:\n\n";

        char choice;
        cout << "Yakin ingin menghapus? (y/n) : ";
        cin.ignore();
        cin >> choice;

        if (choice == 'y' || choice == 'Y') {
            hapus = bantu->next;
            bantu->next = hapus->next;
            delete hapus;
        } else {
            cout << endl;
            cout << ":=================================:\n";
            cout << "| Penghapusan keluhan dibatalkan. |\n";
            cout << ":=================================:\n";
            system("pause");
            system("cls");
            return;
        }
    }

    simpanKeluhan();

    cout << endl;
    cout << ":============================:\n";
    cout << "| Keluhan berhasil dihapus.  |\n";
    cout << ":============================:\n";


    system("pause");
    system("cls");
}

// Fungsi untuk menampilkan menu utama
void tampilkanMenu() {
    cout << ":===========================================:\n";
    cout << "|   Menu Sistem Laporan Keluhan Mahasiswa   |\n";
    cout << "|         UPN 'Veteran' Yogyakarta          |\n";
    cout << "|===========================================|\n";
    cout << "| 1. Buat Keluhan Baru                      |\n";
    cout << "| 2. Tampilkan Keluhan                      |\n";
    cout << "| 3. Cari Keluhan                           |\n";
    cout << "| 4. Urutkan Keluhan                        |\n";
    cout << "| 5. Hapus Keluhan                          |\n";
    cout << "| 6. Keluar                                 |\n";
    cout << ":===========================================:\n";
}

int main () {
    int pilih;
    muatKeluhandariFile();
    do {
        tampilkanMenu();
        cout << "Masukkan menu yang dipilih : "; cin >> pilih; 
        switch (pilih) {
            case 1: 
                system("cls");
                buatKeluhan();
                break;
            case 2: 
                system("cls");
                tampilKeluhan();
                break;
            case 3: 
                system("cls");
                cariKeluhan();
                break;
            case 4: 
                system("cls");
                urutkanKeluhan();
                break;
            case 5:
                system("cls");
                hapusKeluhan();
                break;
            case 6:
                system("cls");
                cout << ":=============================================:\n";
                cout << "| Terima kasih telah membuat laporan keluhan. |\n";
                cout << "|  Keluhan yang ada akan segera kami proses.  |\n";
                cout << ":=============================================:\n";
                break;
            default:
                cout << "\n!! <Menu tidak valid, silakan coba lagi.> !!\n";
                break;
        }
    } while (pilih < 6);

    return 0;
}
