#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <cstdlib>
#include <algorithm>

using namespace std;

const int MAX = 100;

struct Barang {
    string nama;
    string kategori;
    int stok;
    int stokMin;
    string kadaluarsa;
};

Barang barang[MAX];
int jumlah = 0;

string toLower(string str) {
    transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}

void loadData() {
    ifstream file("data.txt"); 
    if (!file) return;

    jumlah = 0;
    string barisKosong; 

    while (jumlah < MAX && getline(file, barang[jumlah].nama)) {
        getline(file, barang[jumlah].kategori);
        file >> barang[jumlah].stok;
        file >> barang[jumlah].stokMin;
        file.ignore(); 
        getline(file, barang[jumlah].kadaluarsa);
        getline(file, barisKosong); 
        jumlah++;
    }

    file.close();
}

void saveData() {
    ofstream file("data.txt");

    for (int i = 0; i < jumlah; i++) {
        file << barang[i].nama << endl;
        file << barang[i].kategori << endl;
        file << barang[i].stok << endl;
        file << barang[i].stokMin << endl;
        file << barang[i].kadaluarsa << endl;
        file << endl; 
    }

    file.close();
}

bool cariBarang(string cari, int &posisi) {
    for (int i = 0; i < jumlah; i++) {
        if (toLower(barang[i].nama) == toLower(cari)) {
            posisi = i;
            return true;
        }
    }
    return false;
}

void tambahBarang() {
    if (jumlah >= MAX) {
        cout << "Gagal: Kapasitas penyimpanan data penuh!\n\n";
        return;
    }

    cout << "=== TAMBAH DATA BARU ===\n";

    cout << "Nama Data: ";
    getline(cin, barang[jumlah].nama);
    while(barang[jumlah].nama == "") {
        cout << "Nama tidak boleh kosong. Masukkan lagi: ";
        getline(cin, barang[jumlah].nama);
    }

    cout << "Kategori   : ";
    getline(cin, barang[jumlah].kategori);
    while(barang[jumlah].kategori == "") {
        cout << "Kategori tidak boleh kosong. Masukkan lagi: ";
        getline(cin, barang[jumlah].kategori);
    }

    while (true) {
        cout << "Stok awal  : ";
        cin >> barang[jumlah].stok;
        if (!cin.fail() && barang[jumlah].stok >= 0) break;
        cout << "Input tidak valid! Harap masukkan angka positif.\n";
        cin.clear(); cin.ignore(10000, '\n');
    }

    while (true) {
        cout << "Stok Min   : ";
        cin >> barang[jumlah].stokMin;
        if (!cin.fail() && barang[jumlah].stokMin >= 0) break;
        cout << "Input tidak valid! Harap masukkan angka positif.\n";
        cin.clear(); cin.ignore(10000, '\n');
    }

    cin.ignore();
    cout << "Kadaluarsa : ";
    getline(cin, barang[jumlah].kadaluarsa);
    while(barang[jumlah].kadaluarsa == "") {
        cout << "Tanggal kadaluarsa tidak boleh kosong. Masukkan lagi: ";
        getline(cin, barang[jumlah].kadaluarsa);
    }

    jumlah++;
    saveData();

    cout << "\nData berhasil ditambahkan dan disimpan!\n\n";
}

void tampilData() {
    cout << "========================================= DATA BARANG =========================================\n";
    cout << "+----+--------------------------------+----------------------+--------+--------+------------------+\n";
    cout << "|No  |Nama                            |Kategori              |Stok    |Min     |Kadaluarsa        |\n";
    cout << "+----+--------------------------------+----------------------+--------+--------+------------------+\n";

    if (jumlah == 0) {
        cout << "|                               TIDAK ADA DATA BARANG YANG TERSEDIA                               |\n";
    } else {
        for (int i = 0; i < jumlah; i++) {
            string namaTampil = (barang[i].nama.length() > 30) ? barang[i].nama.substr(0, 27) + "..." : barang[i].nama;
            string katTampil = (barang[i].kategori.length() > 20) ? barang[i].kategori.substr(0, 17) + "..." : barang[i].kategori;

            cout << "| " << right << setw(2) << i + 1
                 << " | " << left << setw(30) << namaTampil
                 << " | " << left << setw(20) << katTampil
                 << " | " << right << setw(6) << barang[i].stok
                 << " | " << right << setw(6) << barang[i].stokMin
                 << " | " << left << setw(16) << barang[i].kadaluarsa << " |\n";
        }
    }

    cout << "+----+--------------------------------+----------------------+--------+--------+------------------+\n\n";
}

void tambahStok() {
    string nama;
    int tambah;
    int posisi;

    cout << "=== TAMBAH STOK BARANG ===\n";
    cout << "Masukkan Nama Barang: ";
    getline(cin, nama);

    if (cariBarang(nama, posisi)) {
        cout << "Stok Saat Ini: " << barang[posisi].stok << endl;

        while (true) {
            cout << "Jumlah Tambah: ";
            cin >> tambah;
            if (!cin.fail() && tambah > 0) break;
            cout << "Input tidak valid! Masukkan angka lebih dari 0.\n";
            cin.clear(); cin.ignore(10000, '\n');
        }
        cin.ignore();

        barang[posisi].stok += tambah;
        saveData();

        cout << "\nStok berhasil ditambahkan!\n\n";
    } else {
        cout << "Barang tidak ditemukan.\n\n";
    }
}

void kurangiStok() {
    string nama;
    int kurang;
    int posisi;

    cout << "=== KURANGI STOK BARANG ===\n";
    cout << "Masukkan Nama Barang: ";
    getline(cin, nama);

    if (cariBarang(nama, posisi)) {
        cout << "Stok Saat Ini: " << barang[posisi].stok << endl;

        while (true) {
            cout << "Jumlah Kurang: ";
            cin >> kurang;
            if (!cin.fail() && kurang > 0) break;
            cout << "Input tidak valid! Masukkan angka lebih dari 0.\n";
            cin.clear(); cin.ignore(10000, '\n');
        }
        cin.ignore();

        if (kurang <= barang[posisi].stok) {
            barang[posisi].stok -= kurang;
            saveData();
            cout << "\nStok berhasil dikurangi!\n\n";
        } else {
            cout << "\nGagal: Jumlah pengurangan melebihi stok yang ada!\n\n";
        }
    } else {
        cout << "Barang tidak ditemukan.\n\n";
    }
}

void cariData() {
    string cariNama;
    bool ditemukan = false;

    cout << "=== PENCARIAN DATA BARANG ===\n";
    cout << "Masukkan kata kunci nama: ";
    getline(cin, cariNama);

    cout << "\nHasil Pencarian:\n";
    for (int i = 0; i < jumlah; i++) {
        if (toLower(barang[i].nama).find(toLower(cariNama)) != string::npos) {
            cout << "-----------------------------------\n";
            cout << "Nama       : " << barang[i].nama << endl;
            cout << "Kategori   : " << barang[i].kategori << endl;
            cout << "Stok       : " << barang[i].stok << " (Batas Min: " << barang[i].stokMin << ")" << endl;
            cout << "Kadaluarsa : " << barang[i].kadaluarsa << endl;
            ditemukan = true;
        }
    }
    
    if (!ditemukan) {
        cout << "Barang dengan kata kunci tersebut tidak ditemukan.\n";
    }
    cout << "-----------------------------------\n\n";
}

void hapusBarang() {
    string nama;
    int posisi;

    cout << "=== HAPUS DATA BARANG ===\n";
    cout << "Masukkan nama barang yang akan dihapus: ";
    getline(cin, nama);

    if (cariBarang(nama, posisi)) {
        for (int i = posisi; i < jumlah - 1; i++) {
            barang[i] = barang[i + 1];
        }
        jumlah--;
        saveData();

        cout << "\nData barang berhasil dihapus dari sistem!\n\n";
    } else {
        cout << "Barang tidak ditemukan.\n\n";
    }
}

void cekStokKritis() {
    cout << "=== PERINGATAN STOK MINIMUM (PERLU RESTOCK) ===\n";
    bool ada = false;
    
    for (int i = 0; i < jumlah; i++) {
        if (barang[i].stok <= barang[i].stokMin) {
            cout << "[RE-ORDER] " << barang[i].nama 
                 << " -> Stok Sekarang: " << barang[i].stok 
                 << " (Batas Minimum: " << barang[i].stokMin << ")\n";
            ada = true;
        }
    }
    
    if (!ada) {
        cout << "Aman! Semua barang memiliki jumlah stok yang mencukupi.\n";
    }
    cout << "\n";
}

int main() {
    int pilih;

    loadData();

    do {
        cout << "================ MENU UTAMA ================\n";
        cout << "1. Tambah Data Baru\n";
        cout << "2. Lihat Semua Data Barang\n";
        cout << "3. Tambah Stok\n";
        cout << "4. Kurangi Stok\n";
        cout << "5. Cari Barang\n";
        cout << "6. Hapus Barang\n";
        cout << "7. Cek Status Stok Kritis\n";
        cout << "8. Keluar Aplikasi\n";
        cout << "============================================\n";
        cout << "Pilih menu (1-8): ";
        cin >> pilih;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            pilih = 0; 
        } else {
            cin.ignore();
        }

        system("cls"); 

        switch (pilih) {
            case 1: tambahBarang(); break;
            case 2: tampilData(); break;
            case 3: tambahStok(); break;
            case 4: kurangiStok(); break;
            case 5: cariData(); break;
            case 6: hapusBarang(); break;
            case 7: cekStokKritis(); break;
            case 8: cout << "Program selesai. Terima kasih!\n\n"; break;
            default: cout << "Pilihan salah atau tidak valid! Silakan coba lagi.\n\n";
        }

    } while (pilih != 8);

    return 0;
}
