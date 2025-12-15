#include "scheduler.h"
#include <iostream>

using namespace std;

void printMenu() {
    cout << "\n=== STUDENT TASK SCHEDULER ===" << endl;
    cout << "1. Tambah Mata Kuliah" << endl;
    cout << "2. Tambah Kategori Tugas" << endl;
    cout << "3. Tambah Tugas (Assign Task)" << endl;
    cout << "4. Tampilkan Semua Tugas" << endl;
    cout << "5. Tampilkan Tugas per Mata Kuliah" << endl;
    cout << "6. Hapus Mata Kuliah (Cascading Delete)" << endl;
    cout << "0. Exit" << endl;
    cout << "Pilihan: ";
}

void initData(ListMataKuliah &L_MK, ListKategori &L_Kat) {
    // inisiasi Categories
    insertLastKategori(L_Kat, createElmKategori({"KAT01", "Kuis"}));
    insertLastKategori(L_Kat, createElmKategori({"KAT02", "Tubes"}));
    insertLastKategori(L_Kat, createElmKategori({"KAT03", "Tucil"}));
    insertLastKategori(L_Kat, createElmKategori({"KAT04", "Ujian"}));

    // inisiasi mata kuliah
    insertLastMataKuliah(L_MK, createElmMataKuliah({"1", "ANALISIS DAN PERANCANGAN PERANGKAT LUNAK IF-48-11 [RSC]", 3}));
    insertLastMataKuliah(L_MK, createElmMataKuliah({"2", "ANALISIS KOMPLEKSITAS ALGORITMA IF-48-11", 3}));
    insertLastMataKuliah(L_MK, createElmMataKuliah({"3",   "BAHASA INDONESIA IF-48-GABUP.03 [AOI]", 2}));
    insertLastMataKuliah(L_MK, createElmMataKuliah({"4", "SISTEM BASIS DATA IF-48-11 [HAU]", 3}));
    insertLastMataKuliah(L_MK, createElmMataKuliah({"5",      "SISTEM OPERASI S1 INFORMATIKA", 3}));
    insertLastMataKuliah(L_MK, createElmMataKuliah({"6", "SISTEM OPERASI IF-48-11 [AQI]", 3}));
    insertLastMataKuliah(L_MK, createElmMataKuliah({"7",   "STRUKTUR DATA S1 INFORMATIKA", 3}));
    insertLastMataKuliah(L_MK, createElmMataKuliah({"8", "STRUKTUR DATA IF-48-11 [DQU]", 3}));
    insertLastMataKuliah(L_MK, createElmMataKuliah({"9", "TEORI BAHASA DAN AUTOMATA IF-48-11 [DWD]", 3}));
    insertLastMataKuliah(L_MK, createElmMataKuliah({"10", "TEORI PELUANG IF-48-11 [PKR]", 3}));

    cout << "[Init] Data Mata Kuliah dan Kategori berhasil diinisialisasi." << endl;
}

int main() {
    // 1. inisiasi saat kode pertama kali dijalankan
    ListMataKuliah L_MK;
    ListKategori L_Kat;
    ListTugas L_Tugas;

    createListMataKuliah(L_MK);
    createListKategori(L_Kat);
    createListTugas(L_Tugas);

    initData(L_MK, L_Kat);

    int choice;
    do {
        printMenu();
        cin >> choice;

        if (choice == 1) {
            InfotypeMataKuliah data;
            cout << "ID MK: "; cin >> data.idMK;
            cout << "Nama MK: "; cin.ignore(); getline(cin, data.namaMK);
            cout << "SKS: "; cin >> data.sks;
            insertLastMataKuliah(L_MK, createElmMataKuliah(data));
            cout << "[Success] MK " << data.namaMK << " ditambahkan." << endl;

        } else if (choice == 2) {
            InfotypeKategori data;
            cout << "ID Kategori: "; cin >> data.idKategori;
            cout << "Nama Kategori: "; cin.ignore(); getline(cin, data.namaKategori);
            insertLastKategori(L_Kat, createElmKategori(data));
            cout << "[Success] Kategori " << data.namaKategori << " ditambahkan." << endl;

        } else if (choice == 3) {
            InfotypeTugas data;
            string idMK, idKat;
            cout << "ID MK Parent: "; cin >> idMK;
            cout << "ID Kategori Parent: "; cin >> idKat;
            
            cout << "ID Tugas: "; cin >> data.idTugas;
            cout << "Judul Tugas: "; cin.ignore(); getline(cin, data.judul);
            cout << "Deadline (YYYY-MM-DD): "; cin >> data.deadline;
            data.status = false; // Default not done

            assignTask(L_MK, L_Kat, L_Tugas, data, idMK, idKat);

        } else if (choice == 4) {
            showAllTasks(L_Tugas);

        } else if (choice == 5) {
            string idMK;
            cout << "Masukkan ID MK: "; cin >> idMK;
            showTasksBySubject(L_Tugas, L_MK, idMK);

        } else if (choice == 6) {
            string idMK;
            cout << "Masukkan ID MK yang akan dihapus: "; cin >> idMK;
            cout << "[Warning] Menghapus MK akan menghapus semua tugas terkait!" << endl;
            deleteMataKuliahByID(L_MK, L_Tugas, idMK);
            cout << "[Success] Proses penghapusan selesai." << endl;
        }

    } while (choice != 0);

    cout << "Program selesai." << endl;
    return 0;
}
