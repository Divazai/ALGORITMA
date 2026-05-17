#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
using namespace std;

const int MAX = 100;

// Struktur data
struct Barang
{
    string nama;
    string kategori;
    int stok;
    int stokMin;
    string kadaluarsa;
};

Barang barang[MAX];
int jumlah = 0;

// ================= BACA FILE =================
void loadData()
{
    ifstream file("data.txt");
    if (!file)
        return;

    jumlah = 0;

    while (jumlah < MAX && getline(file, barang[jumlah].nama))
    {
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
void saveData()
{
    ofstream file("data.txt");

    for (int i = 0; i < jumlah; i++)
    {
        file << barang[i].nama << endl;
        file << barang[i].kategori << endl;
        file << barang[i].stok << endl;
        file << barang[i].stokMin << endl;
        file << barang[i].kadaluarsa << endl;
        file << endl;
    }

    file.close();
}

// ================= CARI BARANG =================
bool cariBarang(string cari, int &posisi)
{
    for (int i = 0; i < jumlah; i++)
    {
        if (barang[i].nama == cari)
        {
            posisi = i;
            return true;
        }
    }
    return false;
}

// ================= TAMBAH BARANG =================
void tambahBarang()
{
    if (jumlah >= MAX)
    {
        cout << "Data penuh\n\n";
        return;
    }

    cin.ignore();
    cout << "Tambah Barang\n";

    cout << "Nama: ";
    getline(cin, barang[jumlah].nama);
    while (barang[jumlah].nama == "")
    {
        cout << "Nama tidak boleh kosong\n";
        getline(cin, barang[jumlah].nama);
    }

    cout << "Kategori: ";
    getline(cin, barang[jumlah].kategori);
    while (barang[jumlah].kategori == "")
    {
        cout << "Kategori tidak boleh kosong\n";
        getline(cin, barang[jumlah].kategori);
    }

    cout << "Stok: ";
    cin >> barang[jumlah].stok;

    cout << "Stok minimum: ";
    cin >> barang[jumlah].stokMin;

    cin.ignore();
    cout << "Kadaluarsa: ";
    getline(cin, barang[jumlah].kadaluarsa);
    while (barang[jumlah].kadaluarsa == "")
    {
        cout << "Kadaluarsa tidak boleh kosong\n";
        getline(cin, barang[jumlah].kadaluarsa);
    }

    jumlah++;
    saveData();

    cout << "Data ditambahkan\n\n\n";
}

// ================= TAMPIL DATA =================
void tampilData()
{
    cout << "DATA BARANG\n";

    cout << "+----+----------------------+------------+--------+--------+------------------+\n";
    cout << "|No  |Nama                  |Kategori    |Stok    |Min     |Kadaluarsa        |\n";
    cout << "+----+----------------------+------------+--------+--------+------------------+\n";

    for (int i = 0; i < jumlah; i++)
    {
        cout << "| " << right << setw(2) << i + 1
             << " | " << left << setw(30) << barang[i].nama
             << " | " << left << setw(10) << barang[i].kategori
             << " | " << right << setw(6) << barang[i].stok
             << " | " << right << setw(6) << barang[i].stokMin
             << " | " << left << setw(16) << barang[i].kadaluarsa << " |\n";
    }

    cout << "+----+----------------------+------------+--------+--------+------------------+\n\n\n";
}

// ================= TAMBAH STOK =================
void tambahStok()
{
    string nama;
    int tambah;
    int posisi;

    cin.ignore();
    cout << "Tambah Stok\n";
    cout << "Nama barang: ";
    getline(cin, nama);

    if (cariBarang(nama, posisi))
    {
        cout << "Stok sekarang: " << barang[posisi].stok << endl;

        cout << "Tambah: ";
        cin >> tambah;

        barang[posisi].stok += tambah;
        saveData();

        cout << "Stok bertambah\n\n\n";
    }
    else
    {
        cout << "Barang tidak ditemukan\n\n\n";
    }
}

// ================= KURANGI STOK =================
void kurangiStok()
{
    string nama;
    int kurang;
    int posisi;

    cin.ignore();
    cout << "Kurangi Stok\n";
    cout << "Nama barang: ";
    getline(cin, nama);

    if (cariBarang(nama, posisi))
    {
        cout << "Stok sekarang: " << barang[posisi].stok << endl;

        cout << "Kurang: ";
        cin >> kurang;

        if (kurang <= barang[posisi].stok)
        {
            barang[posisi].stok -= kurang;
            saveData();

            cout << "Stok berkurang\n\n\n";
        }
        else
        {
            cout << "Stok tidak cukup\n\n\n";
        }
    }
    else
    {
        cout << "Barang tidak ditemukan\n\n\n";
    }
}

// ================= CARI BARANG =================
void cariData()
{
    string cariNama;
    bool ditemukan = false;

    cin.ignore();
    cout << "Cari Barang\n";
    cout << "Nama: ";
    getline(cin, cariNama);

    for (int i = 0; i < jumlah; i++)
    {
        if (barang[i].nama.find(cariNama) != string::npos)
        {
            cout << "Ditemukan\n";
            cout << "Nama      : " << barang[i].nama << endl;
            cout << "Kategori  : " << barang[i].kategori << endl;
            cout << "Stok      : " << barang[i].stok << endl;
            cout << "Kadaluarsa: " << barang[i].kadaluarsa << endl;
            cout << "\n\n\n";
            ditemukan = true;
        }
    }
    if (!ditemukan)
    {
        cout << "Barang tidak ditemukan\n\n\n";
    }
}

// ================= HAPUS BARANG =================
void hapusBarang()
{
    string nama;
    int posisi;

    cin.ignore();
    cout << "Hapus Barang\n";
    cout << "Nama barang: ";
    getline(cin, nama);

    if (cariBarang(nama, posisi))
    {
        for (int i = posisi; i < jumlah - 1; i++)
        {
            barang[i] = barang[i + 1];
        }
        jumlah--;
        saveData();

        cout << "Data berhasil dihapus\n\n\n";
    }
    else
    {
        cout << "Barang tidak ditemukan\n\n\n";
    }
}

// ================= MAIN =================
int main()
{
    int pilih;

    loadData();

    do
    {
        cout << "=======MENU=======\n";
        cout << "1. Tambah barang\n";
        cout << "2. Lihat data\n";
        cout << "3. Tambah stok\n";
        cout << "4. Kurangi stok\n";
        cout << "5. Cari barang\n";
        cout << "6. Hapus barang\n";
        cout << "7. Keluar\n";
        cout << "Pilih: ";
        cin >> pilih;

        switch (pilih)
        {
        case 1:
            cout << "\n";
            tambahBarang();
            break;
        case 2:
            cout << "\n";
            tampilData();
            break;
        case 3:
            cout << "\n";
            tambahStok();
            break;
        case 4:
            cout << "\n";
            kurangiStok();
            break;
        case 5:
            cout << "\n";
            cariData();
            break;
        case 6:
            cout << "\n";
            hapusBarang();
            break;
        case 7:
            cout << "Selesai\n\n\n";
            break;
        default:
            cout << "Pilihan salah\n\n\n";
        }

    } while (pilih != 7);

    return 0;
}
