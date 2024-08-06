#include <iostream>
#include <string.h>
#include <cmath>

using namespace std;

struct date
{
    int day, month, year;
};

struct dataSupir
{
    string ID_Supir;
    string nama;
    date TTL;
    char gender;
    string alamat;

    dataSupir *prev;
    dataSupir *next;
};
dataSupir *head, *tail, *cur, *del, *newNode, *after;

struct dataOrder
{
    string ID_Cust;
    string namaCust;
    string supir;
    string platNo;
    string tujuan;

    dataOrder *next;
};
dataOrder *headC, *tailC, *curC, *delC, *newNodeC;

struct dataMobil
{
    string platNo;
    string type;
    string brand;

    dataMobil *prev;
    dataMobil *next;
};
dataMobil *headM, *tailM, *curM, *delM, *newNodeM;

int countS = 0;
int countC = 0;
int countM = 0;
bool order;

int charToInt(char c)
{
    if (c >= 'A' && c <= 'Z')
    {
        return c - 'A' + 1;
    }
    else if (c >= 'a' && c <= 'z')
    {
        return c - 'a' + 1;
    }
    else
    {
        return -1;
    }
}

string generateSID(string nama, char gender, int tanggal, int bulan, int tahun)
{
    int digit1, digit2, digit3, digit4, digit5;
    int id;
    string IDstring;

    digit2 = abs(charToInt(nama[0]) - charToInt(nama[nama.length() - 1]));

    digit3 = (gender == 'L') ? 1 : 0;

    digit4 = ((tanggal % 10) + (bulan % 10) + (tahun % 10)) % 9;

    digit5 = 0;

    id = (digit2 * 1000) + (digit3 * 100) + (digit4 * 10) + (digit5);

    if (id < 10000)
    {
        IDstring = to_string(id);
        IDstring = "0" + IDstring;
    }
    else
    {
        IDstring = to_string(id);
    }

    return IDstring;
    // cur = head;
    // while (cur != tail)
    // {
    //     if (id != cur->ID_Supir)
    //     {
    //         return id;
    //     }
    //     else if (id == cur->ID_Supir)
    //     {
    //         if (digit5 == 9)
    //         {
    //             id = id * 10;
    //             digit5 = 0;
    //         }
    //         digit5++;
    //         id = (digit2 * 1000) + (digit3 * 100) + (digit4 * 10) + (digit5);
    //     }
    //     cur = cur->next;
    // }
}

void SupirLL(string ID, string nama, date TTL, char gender, string alamat)
{
    newNode = new dataSupir();
    newNode->ID_Supir = ID;
    newNode->nama = nama;
    newNode->TTL = TTL;
    newNode->gender = gender;
    newNode->alamat = alamat;

    if (head == NULL)
    {
        head = newNode;
        head->prev = head;
        head->next = head;
        tail = head;
    }
    else
    {
        tail->next = newNode;
        head->prev = newNode;
        newNode->prev = tail;
        newNode->next = head;
        tail = newNode;
    }
    tail->next = head;
    head->prev = tail;
    countS++;
    cur = tail;
}

void displaySupir()
{
    if (cur == NULL)
    {
        cout << "\n\nTambahkan data terlebih dahulu...!";
        return;
    }
    else if (cur != NULL)
    {
        cout << "\n|---------------------------------------|\n";
        cout << "|Nama\t\t: " << cur->nama << "\t\t|\n";
        cout << "|Id\t\t: " << cur->ID_Supir << "\t\t\t|\n";
        cout << "|Tgl Lahir\t: " << cur->TTL.day << "-" << cur->TTL.month << "-" << cur->TTL.year << "\t\t|\n";
        cout << "|Kelamin\t: " << (cur->gender == 'L' || 'l' ? "Laki-Laki" : "Perempuan") << "\t\t|\n";
        cout << "|Alamat\t\t: " << cur->alamat << "\t\t|\n";
        cout << "|---------------------------------------|\n";
    }
}

void nextSupir()
{
    if (cur != NULL && cur->next != NULL)
    {
        cur = cur->next;
    }
    else
    {
        cout << "Tidak ada data supir berikutnya.\n";
    }
}

void prevSupir()
{
    if (cur != NULL && cur->prev != NULL)
    {
        cur = cur->prev;
    }
    else
    {
        cout << "Tidak ada data supir sebelumnya.\n";
    }
}

void addSupir()
{
    dataSupir supir;

    cout << "Nama : > ";
    cin.ignore();
    getline(cin, supir.nama);

    cout << "Tgl Lahir (DD-MM-YY) : > ";
    cout << "\nTanggal (DD) : > ";
    cin >> supir.TTL.day;
    cout << "Bulan (MM) : > ";
    cin >> supir.TTL.month;
    cout << "Tahun (YYYY) : > ";
    cin >> supir.TTL.year;

    cout << "Kelamin (L/P) : > ";
    cin >> supir.gender;

    cout << "Alamat : > ";
    cin.ignore();
    getline(cin, supir.alamat);

    supir.ID_Supir = generateSID(supir.nama, supir.gender, supir.TTL.day, supir.TTL.month, supir.TTL.year);

    SupirLL(supir.ID_Supir, supir.nama, supir.TTL, supir.gender, supir.alamat);
    cout << "Data berhasil ditambahkan!\n\n";
}

dataSupir *FindID(string id)
{
    cur = head;
    while (cur != NULL)
    {
        if (cur->ID_Supir == id)
        {
            return cur;
        }
        cur = cur->next;
    }
    return NULL;
}

void editSupir()
{
    if (head == NULL)
    {
        cout << "DLL belum dibuat";
    }
    else
    {
        string ID;
        cout << "\nMasukkan ID Supir yang ingin diubah > ";
        cin >> ID;
        dataSupir *node = FindID(ID);
        if (node != NULL)
        {
            cout << "- Mengubah supir dengan Id " << ID << " -\n";
            cout << "1. Ubah Nama\n";
            cout << "2. Ubah Kelamin\n";
            cout << "3. Ubah Alamat\n";
            cout << "4. Ubah Tgl Lahir\n";
            cout << "> ";
            int pilihan;
            cin >> pilihan;
            switch (pilihan)
            {
            case 1:
                cout << "Masukkan Nama yang baru > ";
                cin.ignore();
                getline(cin, node->nama);
                break;
            case 2:
                cout << "Masukkan Kelamin yang baru (L/P) > ";
                cin >> node->gender;
                break;
            case 3:
                cout << "Masukkan Alamat yang baru > ";
                cin.ignore();
                getline(cin, node->alamat);
                break;
            case 4:
                cout << "Masukkan Tgl Lahir yang baru (DD-MM-YYYY) > ";
                cout << "\nMasukkan Tanggal (DD) > ";
                cin >> node->TTL.day;
                cout << "\nMasukkan Bulan (MM) > ";
                cin >> node->TTL.month;
                cout << "\nMasukkan Tahun (YYYY) > ";
                cin >> node->TTL.year;
                break;
            default:
                cout << "\nPilihan tidak valid!\n";
                break;
            }
            node->ID_Supir = generateSID(node->nama, node->gender, node->TTL.day, node->TTL.month, node->TTL.year);
            cout << "\nData supir dengan Id " << ID << " telah berhasil diubah!\n";
            displaySupir();
        }
    }
}

void deleteSupir()
{
    if (head == NULL)
    {
        cout << "Belum ada data supir yang dibuat.";
    }
    else
    {
        string ID;
        char choice;
        cout << "\nMasukkan ID Supir yang ingin dihapus > ";
        cin >> ID;
        dataSupir *node = FindID(ID);

        if (node != NULL)
        {
            cout << "Supir dengan data berikut akan dihapus :\n";
            displaySupir();
            cout << "Lanjutkan ? (y/n) > ";
            cin >> choice;
            if (choice == 'y' || choice == 'Y')
            {
                if (countS == 1)
                {
                    cur = head;
                    while (cur != NULL)
                    {
                        del = cur;
                        cur = cur->next;
                        del->next = NULL;
                        delete del;
                    }
                    head = NULL;
                    tail = NULL;
                }
                else
                {
                    del = cur;
                    after = del->next;
                    cur = del->prev;
                    cur->next = after;
                    after->prev = cur;
                    delete del;
                    cur = cur->next;

                    cout << "\nSupir dengan Id " << ID << " berhasil dihapus!\n";
                }
                countS--;
            }
            else if (choice == 'n' || choice == 'N')
            {
                cout << "\nSupir dengan Id " << ID << " tidak jadi dihapus!\n";
            }
        }
        else
        {
            cout << "\nSupir dengan Id " << ID << " tidak ditemukan!\n";
        }
    }
}

// _______________________________________________ //
// =============================================== //
//             PRAKTIKUM 3 - STACK MOBIL           //
// =============================================== //
// _______________________________________________ //

void mobilLL(string platNo, string type, string brand)
{
    if (headM == NULL)
    {
        headM = new dataMobil();
        headM->platNo = platNo;
        headM->type = type;
        headM->brand = brand;

        headM->prev = NULL;
        headM->next = NULL;
        tailM = headM;
    }
    else
    {
        newNodeM = new dataMobil();
        newNodeM->platNo = platNo;
        newNodeM->type = type;
        newNodeM->brand = brand;

        newNodeM->prev = tailM;
        tailM->next = newNodeM;
        newNodeM->next = NULL;
        tailM = newNodeM;
    }
    countM++;
}

void addMobil()
{
    dataMobil car;
    char choice;

    do
    {
        cout << "\n\nMasukkan plat nomor mobil > ";
        cin.ignore();
        getline(cin, car.platNo);
        cout << "Masukkan jenis mobil > ";
        cin >> car.type;
        cout << "Masukkan brand mobil > ";
        cin >> car.brand;

        mobilLL(car.platNo, car.type, car.brand);
        cout << "\nData berhasil dimasukkan !!\n";
        cout << "Ingin menambahkan unit lain? (y/n) > ";
        cin >> choice;
    } while (choice == 'Y' || choice == 'y');
}

void displayMobil()
{
    if (headM == NULL)
    {
        cout << "\nTidak ada mobil.\n";
    }
    else
    {
        curM = tailM;

        if (curC != NULL)
        {
            cout << "Plat Nomor\t: " << curM->platNo << endl;
            cout << "Jenis mobil\t: " << curM->type << endl;
            cout << "Merk mobil\t: " << curM->brand << endl;
        }
    }
    cout << "\n";
}

void popMobil()
{
    if (countM == 1)
    {
        curM = headM;
        while (curM != NULL)
        {
            delM = curM;
            headM = headM->next;
            delete delM;
            curM = curM->next;
        }
    }
    else
    {
        delM = tailM;
        tailM = tailM->prev;
        tailM->next = NULL;
        delete delM;
    }

    countM--;
}

// _______________________________________________ //
// =============================================== //
//             PRAKTIKUM 2 - QUEUE ORDER           //
// =============================================== //
// _______________________________________________ //

string generateOID(string platNo, string ID_Supir, string tujuan, string namaCust)
{
    int digit1_2 = charToInt(platNo[0]);
    string digit3_7s = ID_Supir;
    int digit8_9 = charToInt(toupper(tujuan[tujuan.length() - 1])) + charToInt(toupper(tujuan[tujuan.length() - 2]));
    int digit10 = 0;

    for (int i = 0; i < namaCust.length(); i++)
    {
        digit10 = digit10 + charToInt(namaCust[i]);
    }
    digit10 = digit10 % 10;

    string digit10s = to_string(digit10);
    string digit8_9s = to_string(digit8_9);
    string digit1_2s = to_string(digit1_2);
    string IDstring = digit1_2s + digit3_7s + digit8_9s + digit10s;

    return IDstring;
}

void OrderLL(string ID, string nama, string supir, string platNo, string tujuan)
{
    if (headC == NULL)
    {
        headC = new dataOrder();
        headC->ID_Cust = ID;
        headC->namaCust = nama;
        headC->supir = cur->nama;
        headC->platNo = tailM->platNo;
        headC->tujuan = tujuan;

        headC->next = NULL;
        tailC = headC;
    }
    else
    {
        newNodeC = new dataOrder();
        newNodeC->ID_Cust = ID;
        newNodeC->namaCust = nama;
        newNodeC->supir = cur->nama;
        newNodeC->platNo = tailM->platNo;
        newNodeC->tujuan = tujuan;

        newNodeC->next = NULL;
        tailC->next = newNodeC;
        tailC = newNodeC;
    }
    countC++;
}

void displayOrder()
{
    if (headC == NULL)
    {
        cout << "\nTidak ada Pesanan.\n";
    }
    else
    {
        curC = tailC;

        if (curC != NULL)
        {
            cout << "ID\t\t: " << curC->ID_Cust << endl;
            cout << "Nama\t\t: " << curC->namaCust << endl;
            cout << "Supir\t\t: " << curC->supir << endl;
            cout << "Plat Nomor\t: " << curC->platNo << endl;
            cout << "Tujuan\t\t: " << curC->tujuan << endl;
        }
    }
    cout << "\n";
}

int orderDisp = 1;

void displayOrderProc()
{
    if (headC == NULL)
    {
        cout << "\nTidak ada Pesanan.\n";
    }
    else
    {
        if (headC != NULL)
        {
            cout << "\n\n---- Pesanan ke-" << orderDisp << " ----\n";
            cout << "ID\t\t: " << headC->ID_Cust << endl;
            cout << "Nama\t\t: " << headC->namaCust << endl;
            cout << "Supir\t\t: " << headC->supir << endl;
            cout << "Plat Nomor\t: " << headC->platNo << endl;
            cout << "Tujuan\t\t: " << headC->tujuan << endl;
            orderDisp++;
        }
    }
    cout << "\n";
}

void addOrder()
{
    dataOrder cust;
    char choice;

    if (headM == NULL)
    {
        cout << "\nUnit mobil sedang kosong harap menunggu...\n";
        order = false;
        return;
    }
    else
    {
        cout << "Masukkan nama pelanggan > ";
        cin >> cust.namaCust;
        cout << "Tujuan pelanggan > ";
        cin >> cust.tujuan;
        cust.supir = cur->nama;
        cust.platNo = tailM->platNo;
        cust.ID_Cust = generateOID(cust.platNo, cur->ID_Supir, cust.tujuan, cust.namaCust);
        OrderLL(cust.ID_Cust, cust.namaCust, cust.supir, cust.platNo, cust.tujuan);

        cout << "\nOrder telah dilakukan !!!\n";
        displayOrder();
        popMobil();
        order = true;
    }
}

void deQueueOrder()
{
    if (headC == NULL)
    {
        cout << "\nTidak ada Pesanan.\n";
    }
    else
    {
        delC = headC;
        headC = headC->next;
        delC->next = NULL;
        delete delC;

        countC--;
    }
}

void nextOrder()
{
    if (curC != NULL && curC->next != NULL)
    {
        curC = curC->next;
    }
}

void OrderProcess()
{
    int choice;

    do
    {
        displayOrderProc();
        cout << "1. Accept\n";
        cout << "2. Reject\n";
        cout << "3. Exit\n";
        cout << "> ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            if (countC > 0)
            {
                cout << "Pesanan dengan ID " << headC->ID_Cust << " telah diproses.\n";
                deQueueOrder();
            }
            else if (countC <= 0)
            {
                break;
            }
            break;

        case 2:
            if (countC > 0)
            {
                cout << "Pesanan dengan ID " << headC->ID_Cust << " ditolak.\n";
                deQueueOrder();
            }
            else if (countC <= 0)
            {
                break;
            }
            break;
        case 3:
            break;
        default:
            cout << "\nPilihan tidak valid!!\n";
            break;
        }
    } while (choice != 3);
}

// _______________________________________________ //
// =============================================== //
//                      MAIN MENU                  //
// =============================================== //
// _______________________________________________ //

void findSupir()
{
    int choice;
    do
    {
        displaySupir();
        cout << "1. Next\n";
        cout << "2. Previous\n";
        cout << "3. Exit\n";
        cout << "> ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            nextSupir();
            break;
        case 2:
            prevSupir();
            break;
        case 3:
            break;
        default:
            cout << "\nPilihan tidak valid.\n";
        }
    } while (choice != 3);
}

int main()
{
    int menu = 0;

    do
    {
        cout << "\n\n=======================\n";
        cout << "   Selamat Datang !!   \n";
        cout << "=======================\n";
        cout << "1. Masuk Sebagai Admin\n";
        cout << "2. Masuk Sebagai User\n";
        cout << "> ";
        cin >> menu;

        switch (menu)
        {
        case 1:
        {
            int choice;
            do
            {
                cout << "\n\n==== Dashboard Admin ====\n";
                cout << "1. Mencari Data Supir\n";
                cout << "2. Menghapus Data Supir\n";
                cout << "3. Mengubah Data Supir\n";
                cout << "4. Menambah Data Supir\n";
                cout << "5. Proses Pesanan\n";
                cout << "6. Tambah unit Mobil\n";
                cout << "0. Exit\n";
                cout << "> ";
                cin >> choice;

                switch (choice)
                {
                case 1:
                    findSupir();
                    break;
                case 2:
                    deleteSupir();
                    break;
                case 3:
                    editSupir();
                    break;
                case 4:
                    addSupir();
                    break;
                case 5:
                    OrderProcess();
                    break;
                case 6:
                    addMobil();
                    break;
                case 0:
                    break;
                default:
                    cout << "Pilihan tidak valid!\n";
                    break;
                }
            } while (choice != 0);
            break;
        }

        case 2:
        {
            int choice2;
            char choice;

            do
            {
                displaySupir();
                cout << "\n\n==== Dashboard User ====\n";
                cout << "1. Next\n";
                cout << "2. Previous\n";
                cout << "3. Order\n";
                cout << "4. Exit\n";
                cout << "> ";
                cin >> choice2;
                switch (choice2)
                {
                case 1:
                    nextSupir();
                    break;
                case 2:
                    prevSupir();
                    break;
                case 3:

                    addOrder();
                    if (order == true)
                    {

                        cout << "Ingin melakukan order lagi? (y/n) > ";
                        cin >> choice;
                        if (choice == 'Y' || choice == 'y')
                        {
                            choice2 = 3;
                        }
                        else if (choice == 'N' || choice == 'n')
                        {
                            choice2 = 4;
                        }
                    }
                    else
                    {
                        break;
                    }

                    break;

                    break;
                case 4:
                    cout << "\n\nKeluar dari mode user.\n";
                    break;
                default:
                    cout << "Pilihan tidak valid.\n";
                }
            } while (choice2 != 4);
            break;
        }

        case 3:
            cout << "Good Bye !! \n";
            break;

        default:
            cout << "Pilih sesuai pilihan diatas !!\n";
            break;
        }
    } while (menu != 3);

    return 0;
}

// error :
// DONE || after OrderProcess next/prev if(data = NULL)