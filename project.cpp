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

FILE *projek;

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
      
    }
    // Tambah ke double linked list
        if (kepala == NULL) {
            kepala = ekor = baru;
        } else {
            ekor->next = baru;
            baru->prev = ekor;
            ekor = baru;
        }
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

                cout << "Judul buku: ";
                cin.getline(baru->judul, 100);
                cout << "Penulis: ";
                cin.getline(baru->penulis, 100);
                cout << "Penerbit: ";
                cin.getline(baru->penerbit, 100);
                cout << "Tahun terbit: ";
                cin >> baru->tahun;
                cin.ignore();
                cout << "Stock: ";
                cin >> baru->stock;
                cin.ignore();

                fprintf(projek, "%s;%s;%s;%d;%d\n",
                baru->judul, baru->penulis, baru->penerbit,
                baru->tahun, baru->stock);

                if (kepala == NULL) {
                kepala = ekor = baru;
                } else {
                ekor->next = baru;
                baru->prev = ekor;
                ekor = baru;}
            }
            
            cout << "Data berhasil ditambahkan!" << endl;
            fclose(projek);
}
void tampilkanBuku() {
    if (kepala == NULL) {
        cout << "Tidak ada data buku!" << endl;
        return;
    }

    Buku *temp = kepala;
    int no = 1;
    while (temp != NULL) {
        cout << "\nBuku ke-" << no++ << endl;
        cout << "Judul     : " << temp->judul << endl;
        cout << "Penulis   : " << temp->penulis << endl;
        cout << "Penerbit  : " << temp->penerbit << endl;
        cout << "Tahun     : " << temp->tahun << endl;
        cout << "Stock     : " << temp->stock << endl;
        temp = temp->next;
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
    }
    cout << "\nApakah Anda ingin melakukan transaksi lain? (y/n): ";
    cin >> ulang;
    system("cls");
    } while (ulang == 'y' || ulang == 'Y');
}
