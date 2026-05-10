#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
using namespace std;

const int MAX = 100;

// Struktur data
struct Barang {
    string nama;
    string kategori;
    int stok;
    int stokMin;
    string kadaluarsa;
};

Barang barang[MAX];
int jumlah = 0;

// ================= BACA FILE =================
void loadData() {
    ifstream file("data.txt"); 
    if (!file) return;

    jumlah = 0;

    while (getline(file, barang[jumlah].nama)) {
        getline(file, barang[jumlah].kategori);
        file >> barang[jumlah].stok;
        file >> barang[jumlah].stokMin;
        file.ignore();
        getline(file, barang[jumlah].kadaluarsa);
        file.ignore();
        jumlah++;
    }

    file.close();
}

// ================= SIMPAN FILE =================
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

// ================= CARI =================
bool cariBarang(string nama, int &posisi) {
    for (int i = 0; i < jumlah; i++) {
        if (barang[i].nama == nama) {
            posisi = i;
            return true;
        }
    }
    return false;
}

// ================= TAMBAH =================
void tambahBarang() {
    if (jumlah >= MAX) {
        cout << "Data penuh\n";
        return;
    }

    cin.ignore();
    cout << "Tambah Barang\n";

    cout << "Nama: ";
    getline(cin, barang[jumlah].nama);

    cout << "Kategori: ";
    getline(cin, barang[jumlah].kategori);

    cout << "Stok: ";
    cin >> barang[jumlah].stok;

    cout << "Stok minimum: ";
    cin >> barang[jumlah].stokMin;

    cin.ignore();
    cout << "Kadaluarsa: ";
    getline(cin, barang[jumlah].kadaluarsa);

    jumlah++;
    saveData();

    cout << "Data ditambahkan\n";
}

// ================= TAMPIL =================
void tampilData() {
    cout << "DATA BARANG\n";

    cout << "+----+----------------------+------------+--------+--------+------------------+\n";
    cout << "|No  |Nama                  |Kategori    |Stok    |Min     |Kadaluarsa        |\n";
    cout << "+----+----------------------+------------+--------+--------+------------------+\n";

    for (int i = 0; i < jumlah; i++) {
        cout << "| " << setw(2) << i + 1
             << " | " << setw(20) << left << barang[i].nama
             << " | " << setw(10) << left << barang[i].kategori
             << " | " << setw(6) << right << barang[i].stok
             << " | " << setw(6) << barang[i].stokMin
             << " | " << setw(16) << left << barang[i].kadaluarsa << "|\n";
    }

    cout << "+----+----------------------+------------+--------+--------+------------------+\n";
}

// ================= TAMBAH STOK =================
void tambahStok() {
    string nama;
    int tambah;
    int posisi;

    cin.ignore();
    cout << "Tambah Stok\n";
    cout << "Nama barang: ";
    getline(cin, nama);

    if (cariBarang(nama, posisi)) {
        cout << "Stok sekarang: " << barang[posisi].stok << endl;

        cout << "Tambah: ";
        cin >> tambah;

        barang[posisi].stok += tambah;
        saveData();

        cout << "Stok bertambah\n";
    } else {
        cout << "Barang tidak ada\n";
    }
}

// ================= KURANGI STOK =================
void kurangiStok() {
    string nama;
    int kurang;
    int posisi;

    cin.ignore();
    cout << "Kurangi Stok\n";
    cout << "Nama barang: ";
    getline(cin, nama);

    if (cariBarang(nama, posisi)) {
        cout << "Stok sekarang: " << barang[posisi].stok << endl;

        cout << "Kurang: ";
        cin >> kurang;

        if (kurang <= barang[posisi].stok) {
            barang[posisi].stok -= kurang;
            saveData();

            cout << "Stok berkurang\n";
        } else {
            cout << "Stok tidak cukup\n";
        }
    } else {
        cout << "Barang tidak ada\n";
    }
}

// ================= CARI =================
void cariData() {
    string nama;
    int posisi;

    cin.ignore();
    cout << "Cari Barang\n";
    cout << "Nama: ";
    getline(cin, nama);

    if (cariBarang(nama, posisi)) {
        cout << "Ditemukan\n";
        cout << "Nama: " << barang[posisi].nama << endl;
        cout << "Kategori: " << barang[posisi].kategori << endl;
        cout << "Stok: " << barang[posisi].stok << endl;
        cout << "Kadaluarsa: " << barang[posisi].kadaluarsa << endl;
    } else {
        cout << "Barang tidak ditemukan\n";
    }
}

// ================= MAIN =================
int main() {
    int pilih;

    loadData();

    do {
        cout << "MENU\n";
        cout << "1. Tambah barang\n";
        cout << "2. Lihat data\n";
        cout << "3. Tambah stok\n";
        cout << "4. Kurangi stok\n";
        cout << "5. Cari barang\n";
        cout << "6. Keluar\n";
        cout << "Pilih: ";
        cin >> pilih;

        switch (pilih) {
            case 1: tambahBarang(); break;
            case 2: tampilData(); break;
            case 3: tambahStok(); break;
            case 4: kurangiStok(); break;
            case 5: cariData(); break;
            case 6: cout << "Selesai\n"; break;
            default: cout << "Pilihan salah\n";
        }

    } while (pilih != 6);

    return 0;
}
