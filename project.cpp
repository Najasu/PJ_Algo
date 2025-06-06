#include <iostream>
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

struct Peminjaman {
    char NIK[20];
    char nama[100];
    char judul[100];
    int jumlah;
    Peminjaman* next;
};

Buku *kepala = NULL;
Buku *ekor = NULL; 
FILE *projek;

Peminjaman* daftarPinjam = NULL;

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
                swap(current->dipinjem, current->next->dipinjem);
                swapped = true;
            }
            current = current->next;
        }
    } while (swapped);
}

void sisipNodeJudul(Buku *baru) { // fungsi untuk sisip node based on judul
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
                   sisipNodeJudul(baru);} // agar list yg udah urut berdasarkan judul disimpan di file
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
            sisipNodeJudul(baru); // memproses buku yg diinput agar diurut berdasarkan judul

            fprintf(projek, "%s;%s;%s;%d;%d;%d\n", 
            baru->judul, baru->penulis, baru->penerbit,
            baru->tahun, baru->stock, baru->dipinjem);    
        }
        cout << "Data berhasil ditambahkan!" << endl;
        fclose(projek);
}

Buku* salinList(Buku* head) { // untuk membuat salinan dari linked list
    if (!head) return nullptr;

    Buku* salinanHead = new Buku(*head); // buat node baru isinya sama dengan head
    salinanHead->prev = nullptr;
    salinanHead->next = nullptr;

    Buku* currAsli = head->next; // list lama
    Buku* currSalin = salinanHead; // list baru

    while (currAsli != nullptr) {
        Buku* baru = new Buku(*currAsli); //buat node baru dengan data yg ditunjuk oleh currAsli
        baru->prev = currSalin; // set prev node baru ke currSalin
        baru->next = nullptr; 
        currSalin->next = baru; // set next node currSalin ke node baru
        currSalin = baru; 

        currAsli = currAsli->next;
    }

    return salinanHead;
}

void cetaklist(Buku *head){ //cetak yg ada di list
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
    cout<<"\n========================================="<<endl;
    cout<<"|               Data Buku                 |"<<endl;
    cout<<"==========================================="<<endl;
    cout<<"|1. Berdasarkan Judul (Ascending)         |"<<endl;
    cout<<"|2. Berdasarkan Tahun Terbit (Descending) |"<<endl;
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

void caribuku(){ // fungsi untuk mencari buku yang tersedia
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

void editBuku() { // fungsi untuk mengedit data buku
    char judul[100];
    bacadata();
    cout << "Masukkan judul buku yang ingin diedit: ";
    cin.ignore();
    cin.getline(judul, 100);

    bool found = false;
    for (Buku *temp = kepala; temp != NULL; temp = temp->next) {
        if (strcmp(temp->judul, judul) == 0) {
            if (temp->dipinjem > 0) {
                cout << "Buku sedang dipinjam (" << temp->dipinjem << "x), tidak bisa diedit!\n"; // buku hanya bisa diedit jika sedang tidak dipinjam
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

void hapusBuku() { // fungsi untuk menghapus data buku
    char judul[100];
    bacadata();
    cout << "Masukkan judul buku yang ingin dihapus: ";
    cin.ignore();
    cin.getline(judul, 100);

    Buku* temp = kepala;
    while (temp != NULL) {
        if (strcmp(temp->judul, judul) == 0) {
            if (temp->dipinjem > 0) {
                cout << "Buku sedang dipinjam, tidak bisa dihapus!\n";
                return;
            }

            // update pointer prev dan next
            if (temp->prev != NULL)
                temp->prev->next = temp->next;
            else
                kepala = temp->next;

            if (temp->next != NULL)
                temp->next->prev = temp->prev;

            delete temp;
            projek = fopen("projek.txt", "w");
            for (Buku* curr = kepala; curr != NULL; curr = curr->next) {
                fprintf(projek, "%s;%s;%s;%d;%d;%d\n",
                        curr->judul, curr->penulis, curr->penerbit,
                        curr->tahun, curr->stock, curr->dipinjem);
            }
            fclose(projek);

            cout << "Buku berhasil dihapus.\n";
            return;
        }
        temp = temp->next;
    }

    cout << "Buku tidak ditemukan.\n";
}

void bacaPeminjam() { // fungsi untuk membaca data dari file peminjam.txt 
    FILE *file = fopen("peminjam.txt", "r");
    if (!file) {
        daftarPinjam = NULL;
        return;
    }
    
    daftarPinjam = NULL; // reset linked list peminjam
    char baris[256];

    // Baca file baris per baris dan simpan ke linked list
    while (fgets(baris, sizeof(baris), file)) {
        Peminjaman* baru = new Peminjaman;
        baru->next = NULL;

        sscanf(baris, "%[^;];%[^;];%[^;];%d", baru->NIK, baru->nama, baru->judul, &baru->jumlah);

        // Masukkan ke awal linked list
        baru->next = daftarPinjam;
        daftarPinjam = baru;
    }
    fclose(file);
}

bool validasiNIK(const char* nik) { // untuk memaksa NIK harus 16 digit
    int length = strlen(nik);
    if (length != 16) return false;
    for (int i = 0; i < length; i++) {
        if (!isdigit(nik[i])) return false;
    }
    return true;
}

void pinjamBuku() { // fungsi untuk peminjam buku dengan menginput NIK, nama peminjam, dan judul buku yang dipinjam
    char judul[100], nik[20], nama[100];
    int jumlahPinjam;
    bacadata();

    cout << "Masukkan NIK peminjam (16 digit angka): ";
    cin.ignore();
    do {
        cin.getline(nik, 20);
        if (!validasiNIK(nik)) {
            cout << "NIK tidak valid! Masukkan NIK yang benar (16 digit angka): ";
        } else break;
    } while (true);
    cout << "Masukkan Nama peminjam: ";
    cin.getline(nama, 100);
    cout << "Masukkan judul buku yang ingin dipinjam: ";
    cin.getline(judul, 100);

    for (Buku *temp = kepala; temp != NULL; temp = temp->next) {
        if (strcmp(temp->judul, judul) == 0) {
            cout << "Masukkan jumlah yang ingin dipinjam (maks. 3): ";
            cin >> jumlahPinjam;

            if (jumlahPinjam <= 0 || jumlahPinjam > 3) {
                cout << "Jumlah pinjam harus antara 1 sampai 3.\n";
                return;
            }

            if (temp->stock >= jumlahPinjam) {
                // update data stok dan jumlah dipinjam
                temp->stock -= jumlahPinjam;
                temp->dipinjem += jumlahPinjam;

                // simpan data ke file peminjam.txt
                FILE *peminjamFile = fopen("peminjam.txt", "a"); 
                if (peminjamFile != NULL) {
                    fprintf(peminjamFile, "%s;%s;%s;%d\n", nik, nama, judul, jumlahPinjam);
                    fclose(peminjamFile);
                }
                // update file projek.txt dengan data terbaru
                projek = fopen("projek.txt", "w");
                for (Buku *tulis = kepala; tulis != NULL; tulis = tulis->next) {
                    fprintf(projek, "%s;%s;%s;%d;%d;%d\n",
                        tulis->judul, tulis->penulis, tulis->penerbit,
                        tulis->tahun, tulis->stock, tulis->dipinjem);
                }
                fclose(projek);

                cout << "Berhasil meminjam " << jumlahPinjam << " buku.\n";
            } else {
                cout << "Stok tidak mencukupi. Stok tersedia: " << temp->stock << "\n";
            }
            return;
        }
    }

    cout << "Buku tidak ditemukan!\n";
}

void kembaliBuku() { // pengembalian buku yang sudah di pinjam
    char nik[20], judul[100];
    int jumlahKembali;

    bacaPeminjam(); // mengambil data dari 2 file
    bacadata();

    cout << "Masukkan NIK peminjam (16 digit angka): ";
    cin.ignore();
    do {
        cin.getline(nik, 20);
        if (!validasiNIK(nik)) {
            cout << "NIK tidak valid! Masukkan NIK yang benar (16 digit angka): " <<endl;
        } else break;
    } while (true);

    cout << "Masukkan judul buku yang ingin dikembalikan: ";
    cin.getline(judul, 100);

    cout << "Masukkan jumlah yang ingin dikembalikan: ";
    cin >> jumlahKembali;

    if (jumlahKembali <= 0) {
        cout << "Jumlah harus lebih dari 0.\n";
        return;
    }

    // cari data peminjam berdasarkan NIK dan judul buku
    Peminjaman* prevPinjam = nullptr;
    Peminjaman* currPinjam = daftarPinjam;
    bool peminjamanDitemukan = false;

    while (currPinjam != nullptr) {
        if (strcmp(currPinjam->NIK, nik) == 0 && strcmp(currPinjam->judul, judul) == 0) {
            peminjamanDitemukan = true;
            break;
        }
        prevPinjam = currPinjam;
        currPinjam = currPinjam->next;
    }

    if (!peminjamanDitemukan) {
        cout << "Data peminjaman dengan NIK dan judul buku tersebut tidak ditemukan.\n";
        return;
    }

    if (jumlahKembali > currPinjam->jumlah) {
        cout << "Jumlah yang dikembalikan melebihi jumlah yang dipinjam oleh peminjam tersebut.\n";
        cout << "Jumlah yang dipinjam: " << currPinjam->jumlah << endl;
        return;
    }

    currPinjam->jumlah -= jumlahKembali;

    // menghapus data jika jumlah pinjaman jadi 0
    if (currPinjam->jumlah == 0) {
        if (prevPinjam == nullptr) {
            daftarPinjam = currPinjam->next;
        } else {
            prevPinjam->next = currPinjam->next;
        }
        delete currPinjam;
    }

    // update stok buku
    bool bukuDitemukan = false;
    for (Buku* temp = kepala; temp != NULL; temp = temp->next) {
        if (strcmp(temp->judul, judul) == 0) {
            bukuDitemukan = true;
            temp->stock += jumlahKembali;
            temp->dipinjem -= jumlahKembali;
            break;
        }
    }

    if (!bukuDitemukan) {
        cout << "Buku tidak ditemukan di database.\n";
        return;
    }

    projek = fopen("projek.txt", "w");
    for (Buku* temp = kepala; temp != NULL; temp = temp->next) {
        fprintf(projek, "%s;%s;%s;%d;%d;%d\n",
                temp->judul, temp->penulis, temp->penerbit,
                temp->tahun, temp->stock, temp->dipinjem);
    }
    fclose(projek);

    FILE* peminjamFile = fopen("peminjam.txt", "w");
    Peminjaman* curr = daftarPinjam;
    while (curr != nullptr) {
        fprintf(peminjamFile, "%s;%s;%s;%d\n", curr->NIK, curr->nama, curr->judul, curr->jumlah);
        curr = curr->next;
    }
    fclose(peminjamFile);

    cout << "Berhasil mengembalikan " << jumlahKembali << " buku.\n";
} 

void tampilkanPeminjam() { // fungsi untuk menampilkan data orang yang sedang meminjam
    bacaPeminjam();
    
    if (daftarPinjam == NULL) {
        cout << "Belum ada data peminjam.\n";
        return;
    }

    cout << "Daftar Peminjam:\n\n";
    for (Peminjaman* temp = daftarPinjam; temp != NULL; temp = temp->next) {
        cout << "NIK     : " << temp->NIK << endl;
        cout << "Nama    : " << temp->nama << endl;
        cout << "Judul   : " << temp->judul << endl;
        cout << "Jumlah  : " << temp->jumlah << endl;
        cout << endl;
    }
}

int main() {
    int menu;
    char ulang;
    do{
    cout<<"===================================="<<endl;
    cout<<"|    Perpustakaan Kecil-Kecilan    |"<<endl;
    cout<<"===================================="<<endl;
    cout<<"|1. Tambah buku                    |"<<endl;
    cout<<"|2. Tampilkan data buku            |"<<endl;
    cout<<"|3. Cari buku                      |"<<endl;
    cout<<"|4. Edit buku                      |"<<endl;
    cout<<"|5. Hapus buku                     |"<<endl;
    cout<<"|6. Peminjaman buku                |"<<endl;
    cout<<"|7. Tampilkan data peminjam        |"<<endl;
    cout<<"|8. Pengembalian buku              |"<<endl;
    cout<<"|9. Exit                           |"<<endl;
    cout<<"===================================="<<endl;
    cout<<"pilih menu: "; cin>>menu;
    system("cls");
    
    switch (menu) {

        case 1 :
            tambahbuku();
        break;
        
        case 2 :
            bacadata();
            tampilkanBuku();
        break;
        
        case 3 :
            caribuku();
        break;
        
        case 4 :
            editBuku();
        break;

        case 5 :
            hapusBuku();
        break;
        
        case 6 :
            pinjamBuku();
        break;
        
        case 7 :
            tampilkanPeminjam();
        break;
        
        case 8 :
            kembaliBuku();
        break;
        
        case 9 :
            cout<<"Terima kasih!";
            exit(0);
        break;
        
        default :
            cout << "Pilihan tidak valid!\n";
    }

    cout << "Apakah Anda ingin melakukan transaksi lain? (y/n): ";
    cin >> ulang;
    system("cls");
    } 
    while (ulang == 'y' || ulang == 'Y');
}