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
    int dipinjem;
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
                // tukar semua data
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
    kepala = ekor = NULL;
    while (!feof(projek)) {
    Buku *baru = new Buku;
        baru->next = NULL;
        baru->prev = NULL;

    if(fscanf(projek, "%[^;];%[^;];%[^;];%d;%d;%d\n",
                   baru->judul, baru->penulis, baru->penerbit,
                   &baru->tahun, &baru->stock, &baru->dipinjem) != EOF) {
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
            baru->dipinjem = 0;


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

            fprintf(projek, "%s;%s;%s;%d;%d;%d\n", 
            baru->judul, baru->penulis, baru->penerbit,
            baru->tahun, baru->stock, baru->dipinjem);    
        }
        cout << "Data berhasil ditambahkan!" << endl;
        fclose(projek);
}

Buku* salinList(Buku* head) {
    if (!head) return nullptr;

    Buku* salinanKepala = new Buku(*head);
    salinanKepala->prev = nullptr;
    salinanKepala->next = nullptr;

    Buku* currAsli = head->next;
    Buku* currSalin = salinanKepala;

    while (currAsli != nullptr) {
        Buku* baru = new Buku(*currAsli);
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
        cout << "Judul    : " << temp->judul << endl;
        cout << "Penulis  : " << temp->penulis << endl;
        cout << "Penerbit : " << temp->penerbit << endl;
        cout << "Tahun    : " << temp->tahun << endl;
        cout << "Stock    : " << temp->stock << endl;
        cout << "Dipinjam : " << temp->dipinjem << endl;
        cout << endl;
    }
}

void tampilkanBuku() {
    int pilihan;
    if (kepala == NULL) {
        cout << "Tidak ada data buku!" << endl;
        return;
    }
    cout<<"\n==========================================="<<endl;
    cout<<"|               Data Buku                 |"<<endl;
    cout<<"==========================================="<<endl;
    cout<<"|1. Berdasarakan Judul (Ascending)        |"<<endl;
    cout<<"|2. Berdasarakan Tahun Terbit (Descending)|"<<endl;
    cout<<"==========================================="<<endl;
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

void editBuku() {
    char judul[100];
    bacadata();
    cout << "Masukkan judul buku yang ingin diedit: ";
    cin.ignore();
    cin.getline(judul, 100);

    bool found = false;
    for (Buku *temp = kepala; temp != NULL; temp = temp->next) {
        if (strcmp(temp->judul, judul) == 0) {
            if (temp->dipinjem > 0) {
                cout << "Buku sedang dipinjam (" << temp->dipinjem << "x), tidak bisa diedit!\n";
                return;
            }
            cout << "Buku ditemukan! Masukkan data baru:\n";
            cout << "Judul Baru       : ";
            cin.getline(temp->judul, 100);
            cout << "Penulis Baru     : ";
            cin.getline(temp->penulis, 100);
            cout << "Penerbit Baru    : ";
            cin.getline(temp->penerbit, 100);
            cout << "Tahun Terbit Baru: ";
            cin >> temp->tahun;
            cin.ignore();
            cout << "Stock Baru       : ";
            cin >> temp->stock;
            cin.ignore();
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Buku tidak ditemukan!" << endl;
        return;
    }

    projek = fopen("projek.txt", "w");
    for (Buku *temp = kepala; temp != NULL; temp = temp->next) {
        fprintf(projek, "%s;%s;%s;%d;%d;%d\n", 
        temp->judul, temp->penulis, temp->penerbit,
        temp->tahun, temp->stock, temp->dipinjem);
    }
    fclose(projek);

    cout << "Data buku berhasil diubah!\n";
}

void pinjamBuku() {
    char judul[100];
    int jumlahPinjam;
    bacadata();

    cout << "Masukkan judul buku yang ingin dipinjam: ";
    cin.ignore();
    cin.getline(judul, 100);

    for (Buku *temp = kepala; temp != NULL; temp = temp->next) {
        if (strcmp(temp->judul, judul) == 0) {
            cout << "Masukkan jumlah yang ingin dipinjam: ";
            cin >> jumlahPinjam;

            if (jumlahPinjam <= 0) {
                cout << "Jumlah pinjam harus lebih dari 0.\n";
                return;
            }

            if (temp->stock >= jumlahPinjam) {
                temp->stock -= jumlahPinjam;
                temp->dipinjem += jumlahPinjam;
                cout << "Berhasil meminjam " << jumlahPinjam << " buku.\n";
            } else {
                cout << "Stok tidak mencukupi. Stok tersedia: " << temp->stock << "\n";
            }

            projek = fopen("projek.txt", "w");
            for (Buku *tulis = kepala; tulis != NULL; tulis = tulis->next) {
                fprintf(projek, "%s;%s;%s;%d;%d;%d\n",
                    tulis->judul, tulis->penulis, tulis->penerbit,
                    tulis->tahun, tulis->stock, tulis->dipinjem);
            }
            fclose(projek);
            return;
        }
    }

    cout << "Buku tidak ditemukan!\n";
}

void kembaliBuku() {
    char judul[100];
    int jumlahKembali;
    bacadata();

    cout << "Masukkan judul buku yang ingin dikembalikan: ";
    cin.ignore();
    cin.getline(judul, 100);

    for (Buku *temp = kepala; temp != NULL; temp = temp->next) {
        if (strcmp(temp->judul, judul) == 0) {
            if (temp->dipinjem > 0) {
                cout << "Masukkan jumlah yang ingin dikembalikan: ";
                cin >> jumlahKembali;

                if (jumlahKembali <= 0) {
                    cout << "Jumlah harus lebih dari 0.\n";
                    return;
                }

                if (jumlahKembali <= temp->dipinjem) {
                    temp->stock += jumlahKembali;
                    temp->dipinjem -= jumlahKembali;
                    cout << "Berhasil mengembalikan " << jumlahKembali << " buku.\n";
                } else {
                    cout << "Jumlah yang dikembalikan melebihi jumlah yang dipinjam!\n";
                    cout << "Jumlah yang sedang dipinjam: " << temp->dipinjem << "\n";
                }
            } else {
                cout << "Tidak ada peminjaman aktif untuk buku ini.\n";
            }

            projek = fopen("projek.txt", "w");
            for (Buku *tulis = kepala; tulis != NULL; tulis = tulis->next) {
                fprintf(projek, "%s;%s;%s;%d;%d;%d\n", 
                        tulis->judul, tulis->penulis, tulis->penerbit,
                        tulis->tahun, tulis->stock, tulis->dipinjem);
            }
            fclose(projek);
            return;
        }
    }

    cout << "Buku tidak ditemukan!\n";
}

void tampilkanBukuDipinjam() {
    bacadata();
    bool ada = false;
    int i = 1;

    cout << "Daftar Buku yang Sedang Dipinjam:\n";
    cout << "---------------------------------\n";
    for (Buku *temp = kepala; temp != NULL; temp = temp->next) {
        if (temp->dipinjem > 0) {
            ada = true;
            cout << "Buku ke-" << i++ << endl;
            cout << "Judul    : " << temp->judul << endl;
            cout << "Penulis  : " << temp->penulis << endl;
            cout << "Penerbit : " << temp->penerbit << endl;
            cout << "Tahun    : " << temp->tahun << endl;
            cout << "Stock    : " << temp->stock << endl;
            cout << "Dipinjam : " << temp->dipinjem << endl;
            cout << endl;
        }
    }

    if (!ada) {
        cout << "Tidak ada buku yang sedang dipinjam.\n";
    }
}

int main() {
    int menu;
    char ulang;
    do{
    cout<<"================================================"<<endl;
    cout<<"|          Perpustakaan Kecil-Kecilan          |"<<endl;
    cout<<"================================================"<<endl;
    cout<<"|1. Input data buku                            |"<<endl;
    cout<<"|2. Tampilkan data buku                        |"<<endl;
    cout<<"|3. Tampilkan data buku yang sedang dipinjam   |"<<endl;
    cout<<"|4. Cari buku                                  |"<<endl;
    cout<<"|5. Edit buku                                  |"<<endl;
    cout<<"|6. Peminjaman buku                            |"<<endl;
    cout<<"|7. Pengembalian buku                          |"<<endl;
    cout<<"|8. Exit                                       |"<<endl;
    cout<<"================================================"<<endl;
    cout<<"pilih menu: "; cin>>menu;
    system("cls");

    if(menu == 1){
        tambahbuku();
    } else if (menu == 2){
        bacadata();
        tampilkanBuku();
    } else if (menu == 3) {
        tampilkanBukuDipinjam();
    } else if (menu == 4){
        caribuku();
    } else if (menu == 5) {
        editBuku();
    } else if (menu == 6) {
        pinjamBuku();
    } else if (menu == 7) {
        kembaliBuku();
    } else if (menu == 8) {
        cout<<"Terima kasih!";
        exit(0);
    }

    
    cout << "Apakah Anda ingin melakukan transaksi lain? (y/n): ";
    cin >> ulang;
    system("cls");
    } while (ulang == 'y' || ulang == 'Y');
}
