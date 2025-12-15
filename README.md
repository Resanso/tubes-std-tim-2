# Student Task Scheduler - Visualisasi MLL

Berikut adalah representasi visual dari struktur Multi-Linked List (MLL) Relasional N-to-M yang digunakan dalam proyek ini.

## Struktur Diagram (Mermaid)

Diagram ini menunjukkan:

1.  **List Mata Kuliah (DLL)**: Parent 1 (Kuning)
2.  **List Kategori (SLL)**: Parent 2 (Hijau)
3.  **List Tugas (DLL)**: Child (Biru) yang menghubungkan keduanya.

```mermaid
flowchart TD
    %% --- STYLE DEFINITIONS ---
    classDef mk fill:#ffeb3b,stroke:#fbc02d,stroke-width:2px,color:black,rx:5,ry:5;
    classDef kat fill:#69f0ae,stroke:#00c853,stroke-width:2px,color:black,rx:5,ry:5;
    classDef tugas fill:#448aff,stroke:#1565c0,stroke-width:2px,color:white,rx:5,ry:5;

    %% --- PARENT 1: MATA KULIAH ---
    subgraph List_MataKuliah [List Mata Kuliah DLL]
        direction LR
        MK1(MK: Algoritma) <--> MK2(MK: Struktur Data)
        MK2 <--> MK3(MK: Basis Data)
    end

    %% --- PARENT 2: KATEGORI TUGAS ---
    subgraph List_Kategori [List Kategori SLL]
        direction LR
        K1(K: Kuis) --> K2(K: Tubes) --> K3(K: Ujian)
    end

    %% --- CHILD: TUGAS ---
    subgraph List_Tugas [List Tugas Child DLL]
        direction LR
        %% Node Tugas 1 & 2
        T1(Tugas 1: Tubes Strukdat) <--> T2(Tugas 2: Kuis Algo)
    end

    %% --- RELATIONSHIPS N-to-MPart ---

    %% Relasi Tugas 1 -> Ke Parent
    T1 -.->|courseRelation| MK2
    T1 -.->|categoryRelation| K2

    %% Relasi Tugas 2 -> Ke Parent
    T2 -.->|courseRelation| MK1
    T2 -.->|categoryRelation| K1

    %% --- APPLY STYLES ---
    class MK1,MK2,MK3 mk;
    class K1,K2,K3 kat;
    class T1,T2 tugas;
```
