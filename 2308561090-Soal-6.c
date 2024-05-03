#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 100
#define MAX_NOMOR_TELEPON 20
#define MAX_NAMA 50
#define MAX_ALAMAT 100

typedef struct {
    char nomor_telepon[MAX_NOMOR_TELEPON];
    char nama[MAX_NAMA];
    char alamat[MAX_ALAMAT];
} Pelanggan;

typedef struct pelanggan_baru {
    Pelanggan data;
    struct pelanggan_baru *next;
} pelanggan_baru;

pelanggan_baru *hashTable[TABLE_SIZE];

int membuat_hash(char *nomor_telepon)
{
    int hash = 0;
    for (int i = 0; i < strlen(nomor_telepon); i++)
    {
        hash = hash + nomor_telepon[i];
    }
    return hash % TABLE_SIZE;
}

void masukkan_data_pelanggan(Pelanggan *Pelanggan)
{
    int index_hash = membuat_hash(Pelanggan->nomor_telepon);

    pelanggan_baru *data_baru = (pelanggan_baru *)malloc(sizeof(pelanggan_baru));
    data_baru->data = *Pelanggan;
    data_baru->next = NULL;

    if (hashTable[index_hash] == NULL)
    {
        hashTable[index_hash] = data_baru;
    }
    else
    {
        data_baru->next = hashTable[index_hash];
        hashTable[index_hash] = data_baru;
    }
}

void hapus_pelanggan(char *nomor_telepon)
{
    int index_hash = membuat_hash(nomor_telepon);
    pelanggan_baru **ptr_penghapus = &hashTable[index_hash];

    while (*ptr_penghapus != NULL)
    {
        if (strcmp((*ptr_penghapus)->data.nomor_telepon, nomor_telepon) == 0)
        {
            pelanggan_baru *temp = *ptr_penghapus;
            *ptr_penghapus = (*ptr_penghapus)->next;
            free(temp);
            printf("Pelanggan dengan nomor telepon %s berhasil dihapus.\n", nomor_telepon);
            return;
        }
        ptr_penghapus = &(*ptr_penghapus)->next;
    }

    printf("Pelanggan dengan nomor telepon %s tidak ditemukan.\n", nomor_telepon);
}

void tampilkan_pelanggan()
{
    printf("\n+----------------------------+\n");
    printf("| Daftar Pelanggan di Telkom |\n");
    printf("+----------------------------+\n");

    for (int i = 0; i < TABLE_SIZE; i++)
    {
        pelanggan_baru *entry = hashTable[i];
        while (entry != NULL)
        {
            printf("Nomor Telepon: %s\nNama: %s\nAlamat: %s\n\n", entry->data.nomor_telepon, entry->data.nama, entry->data.alamat);
            entry = entry->next;
        }
    }
}

void tambahkan_data_dummy()
{
    Pelanggan dummy1 = {"085123456555", "Diva Ananda", "Jalan Raya Uluwatu No. 1000"};
    Pelanggan dummy2 = {"085123456456", "Jevan Bernard", "Jalan Raya Ngurah Rai No. 1000"};
    Pelanggan dummy3 = {"085123456357", "Galih Agustan", "Jalan Raya Kepakisan No. 1000"};

    masukkan_data_pelanggan(&dummy1);
    masukkan_data_pelanggan(&dummy2);
    masukkan_data_pelanggan(&dummy3);

    printf("Data dummy berhasil ditambahkan.\nSecara default ada 3 data dummy yang bercollision\n");
}

int main()
{
    while (1)
    {
        system("cls");
        printf("+-----------------------------------------+\n");
        printf("| Program Mapping Nomor Telepon di Telkom |\n");
        printf("+-----------------------------------------+\n");
        printf("Pilihan Menu:\n");
        printf("1. Tampilkan Data Pelanggan\n");
        printf("2. Tambah Data Pelanggan\n");
        printf("3. Hapus Data Pelanggan\n");
        printf("4. Otomatis Tambahkan Data Dummy\n");
        printf("5. Keluar\n");
        printf("Pilihan: ");
    
        int pilihan;
        scanf("%d", &pilihan);

        switch (pilihan)
        {
            case 1:
                {
                    int isEmpty = 1;
                    for (int i = 0; i < TABLE_SIZE; i++)
                    {
                        if (hashTable[i] != NULL)
                        {
                            isEmpty = 0;
                            break;
                        }
                    }
                    if (isEmpty)
                    {
                        printf("Tidak ada data yang tersimpan.\n");
                    }
                    else
                    {
                        tampilkan_pelanggan();
                    }
                    system("pause");
                    break;
                }
                break;
            case 2:
                {
                    Pelanggan pelanggan_baru;
                    char temp[0];
                    printf("Masukkan Nomor Telepon Pelanggan Baru: ");
                    gets(temp);
                    gets(pelanggan_baru.nomor_telepon);
                    printf("Masukkan Nama Pelanggan Baru: ");
                    gets(pelanggan_baru.nama);
                    printf("Masukkan Alamat Pelanggan Baru: ");
                    gets(pelanggan_baru.alamat);
                    masukkan_data_pelanggan(&pelanggan_baru);
                    printf("Pelanggan berhasil ditambahkan.\n");
                }
                system ("pause");
                break;
            case 3:
                {
                    char nomor_telepon[MAX_NOMOR_TELEPON];
                    printf("Masukkan Nomor Telepon Pelanggan yang Ingin Dihapus: ");
                    scanf("%s", nomor_telepon);
                    hapus_pelanggan(nomor_telepon);
                }
                system ("pause");
                break;
            case 4:
                tambahkan_data_dummy();
                system ("pause");
                break;
            case 5:
                printf("Program Selesai.\n");
                system ("pause");
                exit(0);
            default:
                printf("Pilihan tidak valid, Silahkan coba lagi\n");
                system ("pause");
                break;
        }
    }

    return 0;
}