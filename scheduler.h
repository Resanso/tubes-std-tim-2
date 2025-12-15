#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <string>

// Definisi parent dan child

/* Parent 1: Mata Kuliah */
struct InfotypeMataKuliah {
    std::string idMK;
    std::string namaMK;
    int sks;
};

/* Parent 2: Kategori Tugas */
struct InfotypeKategori {
    std::string idKategori;
    std::string namaKategori; 
};

/* Child/Relasi: Tugas */
struct InfotypeTugas {
    std::string idTugas;
    std::string judul;
    std::string deadline; 
    bool status;          
};


// Definisi pointer

// deklarasi element
struct ElmMataKuliah;
struct ElmKategori;
struct ElmTugas;

// deklarasi pointer
typedef ElmMataKuliah* adrMataKuliah;
typedef ElmKategori*   adrKategori;
typedef ElmTugas*      adrTugas;


// Definisi node

/* 
 * Parent 1: MataKuliah
 * Type: Double Linked List
 */
struct ElmMataKuliah {
    InfotypeMataKuliah info;
    adrMataKuliah next;
    adrMataKuliah prev;
};

/* 
 * Parent 2: KategoriTugas
 * Type: Single Linked List
 */
struct ElmKategori {
    InfotypeKategori info;
    adrKategori next;
};

/* 
 * Child/Relasi: Tugas
 * Type: Double Linked List
 * Function: menghubungkan parent dan child
 */
struct ElmTugas {
    InfotypeTugas info;
    
    // pointer tugas
    adrTugas next;
    adrTugas prev;
    
    // Relational Pointers (hubungan dengan parent)
    adrMataKuliah courseRelation;   // hubungan dengan MataKuliah
    adrKategori   categoryRelation; // hubungan dengan KategoriTugas
};


// Definisi list

/* List MataKuliah */
struct ListMataKuliah {
    adrMataKuliah first;
    adrMataKuliah last;
};

/* List KategoriTugas */
struct ListKategori {
    adrKategori first;
};

/* List Tugas */
struct ListTugas {
    adrTugas first;
    adrTugas last;
};


// Definisi fungsi primitif

// --- MataKuliah ---
void createListMataKuliah(ListMataKuliah &L);
adrMataKuliah createElmMataKuliah(InfotypeMataKuliah data);
void insertLastMataKuliah(ListMataKuliah &L, adrMataKuliah P);
void deleteMataKuliahByID(ListMataKuliah &L, ListTugas &L_Tugas, std::string idMK);
adrMataKuliah findMataKuliah(ListMataKuliah L, std::string idMK);

// --- KategoriTugas ---
void createListKategori(ListKategori &L);
adrKategori createElmKategori(InfotypeKategori data);
void insertLastKategori(ListKategori &L, adrKategori P);
void deleteKategoriByID(ListKategori &L, std::string idKategori);
adrKategori findKategori(ListKategori L, std::string idKategori);

// --- Tugas ---
void createListTugas(ListTugas &L);
adrTugas createElmTugas(InfotypeTugas data);
void insertLastTugas(ListTugas &L, adrTugas P);
void deleteTugasByID(ListTugas &L, std::string idTugas);
adrTugas findTugas(ListTugas L, std::string idTugas);

// --- Relational Helper ---
// Menghubungkan tugas dengan parent-nya
void assignTaskRelations(adrTugas P, adrMataKuliah M, adrKategori K);

// --- Main Function (Assignment) ---
void assignTask(ListMataKuliah L_MK, ListKategori L_Kat, ListTugas &L_Tugas, InfotypeTugas data, std::string idMK, std::string idKategori);

// --- View Functions ---
void showAllTasks(ListTugas L_Tugas);
void showTasksBySubject(ListTugas L_Tugas, ListMataKuliah L_MK, std::string idMK);

#endif // SCHEDULER_H
