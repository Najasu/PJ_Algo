#include<iostream>
#include <cstdlib> 
#include <stdio.h>
#include <cstring>
using namespace std;

struct Buku{
    char judul[100];
    char penulis[100];
    char penerbit[100];
    int tahun;
    int stock;
    Buku *prev;
    Buku *next;
};

Buku *kepala = NULL;
Buku *ekor = NULL;
Buku *awal, *akhir, *hapus, *NB, *depan, *list;
FILE *projek;

void bubbleSortTahun(Buku *head) {
    if (head == NULL) return;

    bool swapped;
    do {
        swapped = false;
        Buku *current = head;

        while (current->next != NULL) {
            if (current->tahun < current->next->tahun) {
                // Tukar semua data
                swap(current->judul,    current->next->judul);
                swap(current->penulis,  current->next->penulis);
                swap(current->penerbit, current->next->penerbit);
                swap(current->tahun,    current->next->tahun);
                swap(current->stock,    current->next->stock);
                swapped = true;
            }
            current = current->next;
        }
    } while (swapped);
}

void sisipNodeJudul(Buku *baru) {
    if (kepala == nullptr || strcmp(baru->judul, kepala->judul) < 0) {
        // Sisip di depan
        baru->next = kepala;
        if (kepala != nullptr) 
        kepala->prev = baru;
        kepala = baru;
    } else {
        Buku *bantu = kepala;
        while (bantu->next != nullptr && strcmp(baru->judul, bantu->next->judul) > 0) {
            bantu = bantu->next;
        }
        baru->next = bantu->next;
        if (bantu->next != nullptr) bantu->next->prev = baru;
        bantu->next = baru;
        baru->prev = bantu;
    }
}

void bacadata() {
    projek = fopen("projek.txt", "r");
    if (projek == NULL) {
        cout << "File tidak ditemukan atau tidak bisa dibuka!" << endl;
        return;
    }
    // Kosongkan list
    kepala = ekor = NULL;
    while (!feof(projek)) {
    Buku *baru = new Buku;
        baru->next = NULL;
        baru->prev = NULL;

    if(fscanf(projek, "%[^;];%[^;];%[^;];%d;%d\n", 
                 baru->judul, baru->penulis, baru->penerbit,
                 &baru->tahun, &baru->stock) != EOF) {
                sisipNodeJudul(baru);}
    }
    fclose(projek);
}

void tambahbuku(){
    int jumlahbaru;
    projek = fopen("projek.txt", "a");
        if (projek == NULL) {
            cout << "Error membuka file!" << endl;
            exit(1);
        }
        cout << "Jumlah buku yang diinput: ";
        cin >> jumlahbaru;
        cin.ignore();

        for (int i = 0; i < jumlahbaru; i++) {
            cout << endl;
            Buku *baru = new Buku;
            baru->prev = NULL;
            baru->next = NULL;

            cout << "Judul       : ";
            cin.getline(baru->judul, 100);
            cout << "Penulis     : ";
            cin.getline(baru->penulis, 100);
            cout << "Penerbit    : ";
            cin.getline(baru->penerbit, 100);
            cout << "Tahun terbit: ";
            cin >> baru->tahun;
            cin.ignore();
            cout << "Stock       : ";
            cin >> baru->stock;
            cin.ignore();
            baru->prev = NULL;
            baru->next = NULL;
            sisipNodeJudul(baru);

            fprintf(projek, "%s;%s;%s;%d;%d\n",
            baru->judul, baru->penulis, baru->penerbit,
            baru->tahun, baru->stock);
            sisipNodeJudul(baru);        
        }
        cout << "Data berhasil ditambahkan!" << endl;
        fclose(projek);
}

Buku* salinList(Buku* head) {
    if (!head) return nullptr;

    Buku* salinanKepala = new Buku(*head); // salin node pertama
    salinanKepala->prev = nullptr;
    salinanKepala->next = nullptr;

    Buku* currAsli = head->next;
    Buku* currSalin = salinanKepala;

    while (currAsli != nullptr) {
        Buku* baru = new Buku(*currAsli);  // salin data node
        baru->prev = currSalin;
        baru->next = nullptr;
        currSalin->next = baru;
        currSalin = baru;

        currAsli = currAsli->next;
    }

    return salinanKepala;
}

void cetaklist(Buku *head){
    int i = 1;
    for(Buku *temp = head; temp != NULL; temp = temp->next) {
        cout << "Buku ke-" << i++ << endl;
        cout << "Judul   : " << temp->judul << endl;
        cout << "Penulis : " << temp->penulis << endl;
        cout << "Penerbit: " << temp->penerbit << endl;
        cout << "Tahun   : " << temp->tahun << endl;
        cout << "Stock   : " << temp->stock << endl;
        cout << endl;
    }
}

void tampilkanBuku() {
    int pilihan;
    if (kepala == NULL) {
        cout << "Tidak ada data buku!" << endl;
        return;
    }
    cout<<"\nData Buku"<<endl;
    cout<<"1. Berdasarakan Judul (Ascending)"<<endl;
    cout<<"2. Berdasarakan Tahun Terbit (Descending)"<<endl;
    cout<<"Pilih: "; cin>>pilihan;
    system("cls");
    if (pilihan == 1) {
        cetaklist(kepala);
    } else if (pilihan == 2) {
        Buku* salinan = salinList(kepala);
        bubbleSortTahun(salinan);
        cetaklist(salinan);
    }
}

void caribuku(){
    char judul[100];
    cout << "Masukkan judul buku yang ingin dicari: ";
    cin.ignore();
    cin.getline(judul, 100);
    bool found = false;
    for (Buku *temp = kepala; temp != NULL; temp = temp->next) {
        if (strcmp(temp->judul, judul) == 0) {
            cout << "Buku ditemukan!" << endl;
            cout << "Judul   : " << temp->judul << endl;
            cout << "Penulis : " << temp->penulis << endl;
            cout << "Penerbit: " << temp->penerbit << endl;
            cout << "Tahun   : " << temp->tahun << endl;
            cout << "Stock   : " << temp->stock << endl;
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "Buku tidak ditemukan!" << endl;
    }
}

int main() {
    int menu;
    char ulang;
    do{
    cout<<"1. Input data buku"<<endl;
    cout<<"2. Tampilkan data buku"<<endl;
    cout<<"3. Cari buku"<<endl;
    cout<<"pilih menu: "; cin>>menu;
    system("cls");

    if(menu == 1){
        tambahbuku();
    } else if (menu == 2){
        bacadata();
        tampilkanBuku();
    } else if (menu == 3){
        caribuku();
        
    }
    
    cout << "Apakah Anda ingin melakukan transaksi lain? (y/n): ";
    cin >> ulang;
    system("cls");
    } while (ulang == 'y' || ulang == 'Y');
}
