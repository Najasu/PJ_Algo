#include<iostream>
#include <cstdlib> 
#include <stdio.h>
#include <cstring>
using namespace std;

struct buku{
    char judul[100];
    char penulis[100];
    char penerbit[100];
    int* tahun;
    int* stock;
    buku *prev;
    buku *next;
};

buku *kepala = NULL;
buku *ekor = NULL;

void bubbleSort(buku arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (strcmp(arr[j].judul, arr[j + 1].judul) > 0) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// Fungsi untuk memuat data dari file ke array lagu
void simpanData(buku arr[], int &jumlah) {
    FILE *projek = fopen("projek.txt", "r");
    if (projek == NULL) {
        cout << "File tidak ditemukan atau tidak bisa dibuka!" << endl;
        return;
    }

    jumlah = 0; // reset jumlah sebelum memuat data
    while (fscanf(projek, "%[^;];%[^;];%[^;];%d;%d\n", 
                 arr[jumlah].judul, arr[jumlah].penulis, 
                 arr[jumlah].penerbit, arr[jumlah].tahun, 
                 arr[jumlah].stock) != EOF) {
        jumlah++;
    }
    fclose(projek);
}

void tambahbuku(){
    string judul, penulis, penerbit;
    int tahun, stock;
    // buku *baru = new buku;
    cout << "Judul Buku: ";
    getline(cin, judul);
    cin.ignore();
    cout << "Penulis Buku: ";
    getline(cin, penulis);
    cin.ignore();
    cout << "Penerbit Buku: ";
    getline(cin, penerbit);
    cin.ignore();
    cout << "Tahun Terbit: ";
    cin >> tahun;
    cin.ignore();
    cout << "Stock Buku: ";
    cin >> stock;
    
}

int main() {
    int menu;
    cout<<"1. Input data buku"<<endl;
    cout<<"2. Tampilkan data buku"<<endl;
    cout<<"3. Cari buku"<<endl;
    cout<<"pilih menu; "; cin>>menu;
    system("cls");

    if(menu == 1){
        tambahbuku();
    }
    

    return 0;}
