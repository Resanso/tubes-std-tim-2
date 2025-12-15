#include "scheduler.h"
#include <iostream>

// ==========================================
// MATA KULIAH
// ==========================================

void createListMataKuliah(ListMataKuliah &L) {
    L.first = NULL;
    L.last = NULL;
}

adrMataKuliah createElmMataKuliah(InfotypeMataKuliah data) {
    adrMataKuliah P = new ElmMataKuliah;
    P->info = data;
    P->next = NULL;
    P->prev = NULL;
    return P;
}

void insertLastMataKuliah(ListMataKuliah &L, adrMataKuliah P) {
    if (L.first == NULL && L.last == NULL) {
        L.first = P;
        L.last = P;
    } else {
        P->prev = L.last;
        L.last->next = P;
        L.last = P;
    }
}

void deleteMataKuliahByID(ListMataKuliah &L, ListTugas &L_Tugas, std::string idMK) {
    // 1. Cari pointer mata kuliah/parent node
    adrMataKuliah P = findMataKuliah(L, idMK);

    if (P == NULL) {
        return; 
    }

    // 2. Menghapus semua tugas yang terhubung dengan mata kuliah ini
    adrTugas P_Task = L_Tugas.first;
    while (P_Task != NULL) {
        adrTugas nextTask = P_Task->next; // Save next pointer
        if (P_Task->courseRelation == P) {
            // Delete this task using existing function
            deleteTugasByID(L_Tugas, P_Task->info.idTugas);
        }
        P_Task = nextTask;
    }

    // 3. Menghapus parent node
    if (P == L.first && P == L.last) {
        // Case: Only 1 element in list
        L.first = NULL;
        L.last = NULL;
    } else if (P == L.first) {
        // Case: Delete first element
        L.first = P->next;
        L.first->prev = NULL;
    } else if (P == L.last) {
        // Case: Delete last element
        L.last = P->prev;
        L.last->next = NULL;
    } else {
        // Case: Delete in middle
        adrMataKuliah prec = P->prev;
        adrMataKuliah succ = P->next;
        prec->next = succ;
        succ->prev = prec;
    }

    delete P;
}

adrMataKuliah findMataKuliah(ListMataKuliah L, std::string idMK) {
    adrMataKuliah P = L.first;
    while (P != NULL) {
        if (P->info.idMK == idMK) {
            return P;
        }
        P = P->next;
    }
    return NULL;
}


// ==========================================
// KATEGORI TUGAS
// ==========================================

void createListKategori(ListKategori &L) {
    L.first = NULL;
}

adrKategori createElmKategori(InfotypeKategori data) {
    adrKategori P = new ElmKategori;
    P->info = data;
    P->next = NULL;
    return P;
}

void insertLastKategori(ListKategori &L, adrKategori P) {
    if (L.first == NULL) {
        L.first = P;
    } else {
        adrKategori Q = L.first;
        while (Q->next != NULL) {
            Q = Q->next;
        }
        Q->next = P;
    }
}

void deleteKategoriByID(ListKategori &L, std::string idKategori) {
    if (L.first == NULL) {
        return; // Empty list
    }

    adrKategori P = L.first;
    adrKategori prev = NULL;
    bool found = false;

    // cari node dan predesesor
    while (P != NULL && !found) {
        if (P->info.idKategori == idKategori) {
            found = true;
        } else {
            prev = P;
            P = P->next;
        }
    }

    if (found) {
        if (prev == NULL) {
            // Case: hapus elemen pertama
            L.first = P->next;
        } else {
            // Case: hapus elemen tengah atau terakhir
            prev->next = P->next;
        }
        delete P;
    }
}

adrKategori findKategori(ListKategori L, std::string idKategori) {
    adrKategori P = L.first;
    while (P != NULL) {
        if (P->info.idKategori == idKategori) {
            return P;
        }
        P = P->next;
    }
    return NULL;
}


// ==========================================
// TUGAS
// ==========================================

void createListTugas(ListTugas &L) {
    L.first = NULL;
    L.last = NULL;
}

adrTugas createElmTugas(InfotypeTugas data) {
    adrTugas P = new ElmTugas;
    P->info = data;
    P->next = NULL;
    P->prev = NULL;
    P->courseRelation = NULL;
    P->categoryRelation = NULL;
    return P;
}

void insertLastTugas(ListTugas &L, adrTugas P) {
    if (L.first == NULL && L.last == NULL) {
        // Case: List is empty
        L.first = P;
        L.last = P;
    } else {
        // Case: List is not empty
        P->prev = L.last;
        L.last->next = P;
        L.last = P;
    }
}

void deleteTugasByID(ListTugas &L, std::string idTugas) {
    adrTugas P = findTugas(L, idTugas);

    if (P == NULL) {
        return;
    }

    if (P == L.first && P == L.last) {
        // Case: hanya 1 elemen
        L.first = NULL;
        L.last = NULL;
    } else if (P == L.first) {
        // Case: hapus elemen pertama
        L.first = P->next;
        L.first->prev = NULL;
    } else if (P == L.last) {
        // Case: hapus elemen terakhir
        L.last = P->prev;
        L.last->next = NULL;
    } else {
        // Case: hapus elemen tengah
        adrTugas prec = P->prev;
        adrTugas succ = P->next;
        prec->next = succ;
        succ->prev = prec;
    }

    // penghapusan tugas menghapus parent-nya
    // jadi cukup menghapus pointer relasinya
    P->courseRelation = NULL;
    P->categoryRelation = NULL;

    delete P;
}

adrTugas findTugas(ListTugas L, std::string idTugas) {
    adrTugas P = L.first;
    while (P != NULL) {
        if (P->info.idTugas == idTugas) {
            return P;
        }
        P = P->next;
    }
    return NULL;
}

void assignTaskRelations(adrTugas P, adrMataKuliah M, adrKategori K) {
    if (P != NULL) {
        P->courseRelation = M;
        P->categoryRelation = K;
    }
}


// ==========================================
// MAIN FUNCTION (ASSIGNMENT)
// ==========================================

void assignTask(ListMataKuliah L_MK, ListKategori L_Kat, ListTugas &L_Tugas, InfotypeTugas data, std::string idMK, std::string idKategori) {
    // 1. mencari Parent 1 (MataKuliah)
    adrMataKuliah P_MK = findMataKuliah(L_MK, idMK);
    if (P_MK == NULL) {
        std::cout << "[Error] Mata Kuliah dengan ID " << idMK << " tidak ditemukan." << std::endl;
        return;
    }

    // 2. mencari Parent 2 (KategoriTugas)
    adrKategori P_Kat = findKategori(L_Kat, idKategori);
    if (P_Kat == NULL) {
        std::cout << "[Error] Kategori dengan ID " << idKategori << " tidak ditemukan." << std::endl;
        return;
    }

    // 3. membuat Child Node (Tugas)
    adrTugas P_Tugas = createElmTugas(data);

    // 4. menghubungkan parent dan child
    assignTaskRelations(P_Tugas, P_MK, P_Kat);

    // 5. menambahkan child ke list tugas
    insertLastTugas(L_Tugas, P_Tugas);

    std::cout << "[Success] Tugas '" << data.judul << "' berhasil ditambahkan ke " 
              << P_MK->info.namaMK << " (" << P_Kat->info.namaKategori << ")." << std::endl;
}


// ==========================================
// VIEW FUNCTIONS
// ==========================================

void showAllTasks(ListTugas L_Tugas) {
    if (L_Tugas.first == NULL) {
        std::cout << "[Info] Tidak ada data tugas." << std::endl;
        return;
    }

    std::cout << "=== DAFTAR SEMUA TUGAS ===" << std::endl;
    adrTugas P = L_Tugas.first;
    int i = 1;
    while (P != NULL) {
        std::cout << i << ". ";
        
        if (P->courseRelation != NULL) {
            std::cout << "[" << P->courseRelation->info.namaMK << "] - ";
        } else {
            std::cout << "[Unknown MK] - ";
        }

        std::cout << P->info.judul;

        if (P->categoryRelation != NULL) {
            std::cout << " (Kategori: " << P->categoryRelation->info.namaKategori << ")";
        } else {
            std::cout << " (Kategori: Unknown)";
        }
        
        if (P->info.status) {
            std::cout << " [DONE]"; 
        } else {
            std::cout << " [NOT DONE]";
        }

        std::cout << std::endl;
        P = P->next;
        i++;
    }
    std::cout << "==========================" << std::endl;
}

void showTasksBySubject(ListTugas L_Tugas, ListMataKuliah L_MK, std::string idMK) {
    // 1. Cek apakah mata kuliah ada
    adrMataKuliah P_MK = findMataKuliah(L_MK, idMK);
    if (P_MK == NULL) {
        std::cout << "[Error] Mata Kuliah dengan ID " << idMK << " tidak ditemukan." << std::endl;
        return;
    }

    std::cout << "=== TUGAS UNTUK " << P_MK->info.namaMK << " ===" << std::endl;
    
    adrTugas P = L_Tugas.first;
    bool found = false;
    int i = 1;

    while (P != NULL) {
        // Filter: cek apakah address parent-nya sesuai
        if (P->courseRelation == P_MK) {
            std::cout << i << ". " << P->info.judul << " (Deadline: " << P->info.deadline << ")";
            
            if (P->categoryRelation != NULL) {
                std::cout << " - Type: " << P->categoryRelation->info.namaKategori;
            }

            std::cout << std::endl;
            found = true;
            i++;
        }
        P = P->next;
    }

    if (!found) {
        std::cout << "[Info] Belum ada tugas untuk mata kuliah ini." << std::endl;
    }
    std::cout << "==================================" << std::endl;
}
