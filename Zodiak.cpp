#include <iostream>
#include <ctime>
#include <fstream>
#include <conio.h>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <random>
using namespace std;

struct dataUser
{
    string zodiak, nama;
    int tanggal, bulan;
    bool cek = false;
};

// Mengatur Date dan Time agar dapat digunakan secara Global
// menggunakan Library ctime
time_t currentTime = time(nullptr);
struct tm *timeinfo = localtime(&currentTime);

int year = timeinfo->tm_year + 1900;
int month = timeinfo->tm_mon + 1;
int day = timeinfo->tm_mday;
int hour = timeinfo->tm_hour;
int minute = timeinfo->tm_min;
int second = timeinfo->tm_sec;

// Warna (ANSI Escape Sequence)
string black = "\033[30m";
string red = "\033[31m";
string green = "\033[32m";
string yellow = "\033[33m";
string blue = "\033[34m";
string magenta = "\033[35m";
string cyan = "\033[36m";
string grey = "\033[1;30m";
string orange = "\033[38;5;208m";
string brown = "\033[38;2;139;69;19m";
string pink = "\033[38;5;218m";
string cream = "\033[38;2;255;253;208m";

// Function
void outputFunfactZodiak(string file, string word, string warna);
void outputRamalanZodiak(string file, string word, string warna);
void outputHighlight(string file, string word, string warna);
void inputData(string file, string data);
void inputChecker(int &var);
string zodiakChecker(int tanggal, int bulan);
void bubbleSort(string arr[], int n);
int binarySearch(string arr[], int low, int high, string key);

// Tampilan Menu (Interface)
void menu(); // Tampilan Menu Utama
void printSetFill(string x, int points);
void dateTime();  // Menampilkan Tanggal dan Waktu pada Menu
void highlight(); // Higlight Zodiak pada Menu

// Additional
dataUser user; // Menampung Informasi User
char input;    // Input User pada Menu
int cp = 1;    // Penghitungan Input agar sesuai dengan Interface

// Fitur 1
void cekProfile();
void cekZodiak();

// Fitur 2
void funfactZodiak();

// Fitur 3
void ramalanZodiak();

string zodiak[12] = {"Aries", "Taurus", "Gemini", "Cancer", "Leo", "Virgo", "Libra", "Scorpio", "Sagitarius", "Capricorn", "Aquarius", "Pisces"};

int main()
{
    // Sorting Data Zodiak
    int n = sizeof(zodiak) / sizeof(zodiak[0]);
    bubbleSort(zodiak, n);
    menu();
    return 0;
}

void bubbleSort(string arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j].compare(arr[j + 1]) > 0)
            {
                // Swap elemen jika elemen saat ini lebih besar dari elemen berikutnya
                string temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void dateTime()
{
    cout << "Date : " << green << day << '/' << month << '/' << year << "\033[0m" << endl;
    cout << "Time : " << green << hour << ':' << minute << ':' << second << "\033[0m" << endl
         << endl;
}

void outputHighlight(string file, int baris)
{
    // Membuka File
    ifstream filex(file);

    // Check if the file is open
    if (!filex.is_open())
    {
        cout << "Error opening file." << endl;
        exit(0);
    }

    // Variabel Penampung
    string x;
    int count = 0;

    // Membaca dan mencetak baris kedua dari file
    while (getline(filex, x))
    {
        count++;
        if (count == baris)
        {
            cout << x << endl; // Mencetak baris ke layar
            break;             // Keluar dari loop setelah mencetak baris
        }
    }

    // Menutup File
    filex.close();
}

void highlight()
{
    int randomNumber = rand() % 5;
    string warna; // menampung warna random
    int baris;    // menampung baris yang ingin diambil secara random

    if (randomNumber == 0)
    {
        baris = 1;
        warna = magenta;
    }
    else if (randomNumber == 1)
    {
        baris = 2;
        warna = red;
    }
    else if (randomNumber == 2)
    {
        baris = 3;
        warna = pink;
    }
    else if (randomNumber == 3)
    {
        baris = 4;
        warna = yellow;
    }
    else if (randomNumber == 4)
    {
        baris = 5;
        warna = blue;
    }

    // Cek Zodiak Hari ini
    string zodiakNow = zodiakChecker(day, month);
    cout << "Zodiak Hari ini " << warna << zodiakNow << "\033[0m" << endl;
    string file = "zodiak/";
    file.append(zodiakNow);
    file.append("/highlight.txt");
    outputHighlight(file, baris);
}

// Menu / Interface
void menu()
{
    int fiturMenu = 3; // Berisi Jumlah Opsi pada Menu
    cp = 1;
    for (int i = 0; i < 1; i++)
    {
        system("cls");
        dateTime();
        cout << "---- Zodiak ----" << endl;
        if (user.cek == false)
            printSetFill("Check Zodiak", 1);
        else
            printSetFill("Profile", 1);

        printSetFill("Funfact Zodiak", 2);
        printSetFill("Ramalan Zodiak", 3);
        cout << endl;
        highlight();
        input = getch();
        if ((input == 'w' || input == 'W') && cp != 1)
        {
            cp--;
            i--;
        }
        else if ((input == 's' || input == 'S') && cp != fiturMenu)
        {
            cp++;
            i--;
        }
        else if ((input == 'w' || input == 'W') && cp == 1)
        {
            cp = fiturMenu;
            i--;
        }
        else if ((input == 's' || input == 'S') && cp == fiturMenu)
        {
            cp = 1;
            i--;
        }
        else if (input == '\r')
        {
            if (cp == 1 && user.cek == false)
                cekZodiak();
            else if (cp == 1 && user.cek == true)
                cekProfile();
            else if (cp == 2)
                funfactZodiak();
            else if (cp == 3)
                ramalanZodiak();
            else
                cout << "Error" << endl;
        }
        else
            i--;
    }
}

void printSetFill(string x, int point) // Mengatur Jarak Agar Output Lebih Rapih
{
    if (cp == point)
        cout << setfill(' ') << "<*> " << x << setw(30 - x.length()) << "<--" << endl;
    // setFill =  Jarak yang kosong di-isi dengan apa
    // setw()  =  Total Jarak / Lebar
    else
        cout << "<*> " << x << endl;
}

string zodiakChecker(int tanggal, int bulan)
{
    string searchZodiac;
    if ((bulan == 3 && tanggal >= 21) || (bulan == 4 && tanggal <= 19)) // 21 Maret-19 April
        searchZodiac = "Aries";
    else if ((bulan == 4 && tanggal >= 20) || (bulan == 5 && tanggal <= 20)) // 20 April-20 Mei
        searchZodiac = "Taurus";
    else if ((bulan == 5 && tanggal >= 21) || (bulan == 6 && tanggal <= 20)) // 21 Mei-20 Juni
        searchZodiac = "Gemini";
    else if ((bulan == 6 && tanggal >= 21) || (bulan == 7 && tanggal <= 22)) // 21 Juni-22 Juli
        searchZodiac = "Cancer";
    else if ((bulan == 7 && tanggal >= 23) || (bulan == 8 && tanggal <= 22)) // 23 Juli-22 Agustus
        searchZodiac = "Leo";
    else if ((bulan == 8 && tanggal >= 23) || (bulan == 9 && tanggal <= 22)) // 23 Agustus-22 September
        searchZodiac = "Virgo";
    else if ((bulan == 9 && tanggal >= 23) || (bulan == 10 && tanggal <= 22)) // 23 September-22 Oktober
        searchZodiac = "Libra";
    else if ((bulan == 10 && tanggal >= 23) || (bulan == 11 && tanggal <= 21)) // 23 Oktober-21 November
        searchZodiac = "Scorpio";
    else if ((bulan == 11 && tanggal >= 22) || (bulan == 12 && tanggal <= 21)) // 22 November-21 December
        searchZodiac = "Sagittarius";
    else if ((bulan == 12 && tanggal >= 22) || (bulan == 1 && tanggal <= 19)) // 22 December-19 January
        searchZodiac = "Capricorn";
    else if ((bulan == 1 && tanggal >= 20) || (bulan == 2 && tanggal <= 18)) // 20 January-18 February
        searchZodiac = "Aquarius";
    else if ((bulan == 2 && tanggal >= 19) || (bulan == 3 && tanggal <= 20)) // 19 February-20 Maret
        searchZodiac = "Pisces";
    else
        searchZodiac = "Tidak ditemukan";

    return searchZodiac;
}

void cekZodiak()
{
    system("cls");
    // Penampungan
    string nama;
    int tanggal, bulan;

    cout << "Nama User     : ";
    cin >> nama;
    cout << "Tanggal Lahir : ";
    inputChecker(tanggal);
    cout << "Bulan (Angka) : ";
    inputChecker(bulan);
    string hasil = zodiakChecker(tanggal, bulan);

    if (hasil == "Tidak ditemukan")
        cout << "Zodiak Kamu " << hasil << endl;
    else
    {
        cout << "Zodiak Kamu " << hasil << endl;
        // Masukan data penampungan ke data real
        user.zodiak = hasil;
        user.nama = nama;
        user.tanggal = tanggal;
        user.bulan = bulan;
        user.cek = true;
    }
    system("pause");
    menu();
}

void inputChecker(int &var)
{
    if (!(cin >> var))
    {
        cout << "Input Error, Harap Masukan Angka" << endl;
        // handle input errors and clear the input buffer before attempting to read new input.
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        system("pause");
        menu();
    }
}

// Fitur Cek Profile
void cekProfile()
{
    int fiturCekProfile = 2; // Berisi jumlah Opsi pada Menu Cek Profile
    cp = 1;
    for (int i = 0; i < 1; i++)
    {
        system("cls");
        cout << "Nama User     : "
             << green << user.nama << "\033[0m" << endl;
        cout << "Tanggal Lahir : "
             << user.tanggal << endl;
        cout << "Bulan (Angka) : "
             << user.bulan << endl;
        cout << "Zodiak        : " << magenta << user.zodiak << "\033[0m" << endl;
        printSetFill("Cek Zodiak", 1);
        printSetFill("Back to Menu", 2);
        input = getch();
        if ((input == 'w' || input == 'W') && cp != 1)
        {
            cp--;
            i--;
        }
        else if ((input == 's' || input == 'S') && cp != fiturCekProfile)
        {
            cp++;
            i--;
        }
        else if ((input == 'w' || input == 'W') && cp == 1)
        {
            cp = fiturCekProfile;
            i--;
        }
        else if ((input == 's' || input == 'S') && cp == fiturCekProfile)
        {
            cp = 1;
            i--;
        }
        else if (input == '\r')
        {
            if (cp == 1)
                cekZodiak();
            else if (cp == 2)
                menu();
            else
                cout << "Error" << endl;
        }
        else
            i--;
    }
}

// Fitur funfact Zodiak
void funfactZodiak()
{
    int fiturFunFact = 13; // Berisi Jumlah Opsi pada Menu FunFact
    cp = 1;
    for (int i = 0; i < 1; i++)
    {
        system("cls");
        cout << "---- Funfact Zodiak ----" << endl;
        for (int i = 0; i < 12; i++)
            printSetFill(zodiak[i], i + 1);
        printSetFill("Back to Menu", 13);

        input = getch();
        if ((input == 'w' || input == 'W') && cp != 1)
        {
            cp--;
            i--;
        }
        else if ((input == 's' || input == 'S') && cp != fiturFunFact)
        {
            cp++;
            i--;
        }
        else if ((input == 'w' || input == 'W') && cp == 1)
        {
            cp = fiturFunFact;
            i--;
        }
        else if ((input == 's' || input == 'S') && cp == fiturFunFact)
        {
            cp = 1;
            i--;
        }
        else if (input == '\r')
        {
            for (int i = 0; i < 12; i++)
            {
                if (cp == i + 1)
                {
                    string zod = "zodiak/";
                    zod.append(zodiak[i]);
                    zod.append("/umum.txt");

                    int randomNumber = rand() % 5;
                    string warna; // menampung warna random

                    if (randomNumber == 0)
                        warna = magenta;
                    else if (randomNumber == 1)
                        warna = red;
                    else if (randomNumber == 2)
                        warna = pink;
                    else if (randomNumber == 3)
                        warna = yellow;
                    else if (randomNumber == 4)
                        warna = blue;
                    outputFunfactZodiak(zod, zodiak[i], warna);
                }
            }
            if (cp == 13)
                menu();
            else
                cout << "Error" << endl;
        }
        else
            i--;
    }
}
// Fungsi untuk melakukan pencarian binary
int binarySearch(string arr[], int low, int high, string key)
{
    while (low <= high)
    {
        int mid = low + (high - low) / 2;
        if (arr[mid] == key)
        {
            return mid;
        }
        else if (arr[mid] < key)
        {
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }
    return -1; // Return -1 jika tidak ditemukan
}
void ramalanZodiak()
{
    system("cls");
    string getZodiak; // untuk menampung input Zodiak user
    cout << magenta << "Tulis (-) untuk kembali ke Menu!!"
         << "\033[0m" << endl;
    cout << red << "Note : gunakan huruf kapital didepan (ex : Libra)"
         << "\033[0m" << endl;
    cout << cyan << "Input 'List' untuk menampilkan ke-12 Zodiak!!"
         << "\033[0m" << endl;
    cout << "Masukan Zodiak yang ingin kamu cek : ";
    cin >> getZodiak;
    cout << endl;

    int n = sizeof(zodiak) / sizeof(zodiak[0]);

    int index = binarySearch(zodiak, 0, n - 1, getZodiak);
    if (index != -1)
    {
        string zodiakFile = "zodiak/" + zodiak[index] + "/ramalan.txt";
        string zodiakColor;

        // Menentukan warna berdasarkan indeks zodiak
        if (index % 2 == 0)
        {
            zodiakColor = red;
        }
        else
        {
            zodiakColor = blue;
        }

        outputRamalanZodiak(zodiakFile, zodiak[index], zodiakColor);
    }
    else if (getZodiak == "-")
    {
        menu();
    }
    else if (getZodiak == "List")
    {
        for (int i = 0; i < 12; i++)
            cout << cyan << zodiak[i] << "\033[0m" << endl;
        system("pause");
        ramalanZodiak();
    }
    else
    {
        cout << red << "Zodiak Tidak ditemukan!!"
             << "\033[0m" << endl;
        system("pause");
        ramalanZodiak();
    }
}

void outputRamalanZodiak(string file, string word, string warna)
{
    // Membuka File
    ifstream filex(file);

    // Check if the file is open
    if (!filex.is_open())
    {
        cout << "Error opening file." << endl;
        exit(0);
    }

    // Variabel Penampung
    string x;
    string word2 = "Umum";
    string word3 = "Love";
    string word4 = "Karir";
    string word5 = "Keuangan";

    // Cek perbaris
    while (getline(filex, x))
    {
        // Jika dalam suatu baris ada kata word
        if (x.find(word) != string::npos)
        {
            // Jika ada, highlight kata word
            int pos = x.find(word);
            cout << x.substr(0, pos);              // Cetak sebelum kata tersebut
            cout << warna                          // Warna Higlight
                 << word                           // Cetak kata tersebut
                 << "\033[0m";                     // Standar Escape Sequence
            cout << x.substr(pos + word.length()); // word adalah total char yang ada didalam string
            cout << endl;
        }
        else if (x.find(word2) != string::npos)
        {
            // Jika ada, highlight kata word
            int pos = x.find(word2);
            cout << x.substr(0, pos);               // Cetak sebelum kata tersebut
            cout << green                           // Warna Higlight
                 << word2                           // Cetak kata tersebut
                 << "\033[0m";                      // Standar Escape Sequence
            cout << x.substr(pos + word2.length()); // 14 adalah total char yang ada didalam string
            cout << endl;
        }
        else if (x.find(word3) != string::npos)
        {
            // Jika ada, highlight kata word
            int pos = x.find(word3);
            cout << x.substr(0, pos);               // Cetak sebelum kata tersebut
            cout << red                             // Warna Higlight
                 << word3                           // Cetak kata tersebut
                 << "\033[0m";                      // Standar Escape Sequence
            cout << x.substr(pos + word3.length()); // 14 adalah total char yang ada didalam string
            cout << endl;
        }
        else if (x.find(word4) != string::npos)
        {
            // Jika ada, highlight kata word
            int pos = x.find(word4);
            cout << x.substr(0, pos);               // Cetak sebelum kata tersebut
            cout << orange                          // Warna Higlight
                 << word4                           // Cetak kata tersebut
                 << "\033[0m";                      // Standar Escape Sequence
            cout << x.substr(pos + word4.length()); // 14 adalah total char yang ada didalam string
            cout << endl;
        }
        else if (x.find(word5) != string::npos)
        {
            // Jika ada, highlight kata word
            int pos = x.find(word5);
            cout << x.substr(0, pos);               // Cetak sebelum kata tersebut
            cout << magenta                         // Warna Higlight
                 << word5                           // Cetak kata tersebut
                 << "\033[0m";                      // Standar Escape Sequence
            cout << x.substr(pos + word5.length()); // 14 adalah total char yang ada didalam string
            cout << endl;
        }
        else
            // Jika tidak ada kata tersebut, Maka cetak seperti biasa
            cout << x << endl;
    }

    cout << endl;
    system("pause");
    // Menutup File
    filex.close();
    ramalanZodiak();
}

void outputFunfactZodiak(string file, string word, string warna)
{
    system("cls");
    // Membuka File
    ifstream filex(file);

    // Check if the file is open
    if (!filex.is_open())
    {
        cout << "Error opening file." << endl;
        exit(0);
    }

    // Variabel Penampung
    string x;
    string word2 = "Funfact Zodiak";
    string word3 = "Asmara";

    // Cek perbaris
    while (getline(filex, x))
    {
        // Jika dalam suatu baris ada kata word
        if (x.find(word) != string::npos)
        {
            // Jika ada, highlight kata word
            int pos = x.find(word);
            cout << x.substr(0, pos);              // Cetak sebelum kata tersebut
            cout << warna                          // Warna Higlight
                 << word                           // Cetak kata tersebut
                 << "\033[0m";                     // Standar Escape Sequence
            cout << x.substr(pos + word.length()); // word adalah total char yang ada didalam string
            cout << endl;
        }
        else if (x.find(word2) != string::npos)
        {
            // Jika ada, highlight kata word
            int pos = x.find(word2);
            cout << x.substr(0, pos);               // Cetak sebelum kata tersebut
            cout << cyan                            // Warna Higlight
                 << word2                           // Cetak kata tersebut
                 << "\033[0m";                      // Standar Escape Sequence
            cout << x.substr(pos + word2.length()); // 14 adalah total char yang ada didalam string
            cout << endl;
        }
        else if (x.find(word3) != string::npos)
        {
            // Jika ada, highlight kata word
            int pos = x.find(word3);
            cout << x.substr(0, pos);               // Cetak sebelum kata tersebut
            cout << cyan                            // Warna Higlight
                 << word3                           // Cetak kata tersebut
                 << "\033[0m";                      // Standar Escape Sequence
            cout << x.substr(pos + word3.length()); // 14 adalah total char yang ada didalam string
            cout << endl;
        }
        else
            // Jika tidak ada kata tersebut, Maka cetak seperti biasa
            cout << x << endl;
    }

    cout << endl;
    system("pause");
    // Menutup File
    filex.close();
    funfactZodiak();
}

// Fitur inputData (Belum diaplikasikan)
void inputData(string file, string data)
{
    // Membuka File , ios::app digunakan untuk menimpa data
    // Pastikan file sudah dibuat , apabila belum maka ios::app otomatis membuat file baru
    ofstream filex(file, ios::app);

    // Menginput Data kedalam File
    filex << data << endl;

    // Menutup File
    filex.close();
}
