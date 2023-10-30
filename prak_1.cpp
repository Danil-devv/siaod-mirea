// ConsoleApplication1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <stdlib.h>
#include <iostream>
#include <Windows.h>
#include <bitset>
#include <vector>
#include <fstream>
#include <ctime>

using namespace std;

void task1_a() {
    unsigned char x = 255;      //8-разрядное двоичное число 11111111
    unsigned char maska = 1;    //1=00000001 – 8-разрядная маска
    x = x & (~(maska << 4));
    cout << int(x);
}

void task1_b() {
    unsigned char x = 137;      //8-разрядное двоичное число 10001001
    unsigned char maska = 1;    //1=00000001 – 8-разрядная маска
    x = x | (maska << 6);      // установка 7-го бита в единицу
    cout << int(x);             // 11001001 == 201
}

void task1_c() {
    unsigned int x = 25; // 11001
    const int n = sizeof(x) * 8; // 32 - кол-во разрядов в числе типа int
    unsigned mask = (1 << (n - 1));
    cout << "Начальный вид маски: " << bitset<n>(mask) << "\n";
    cout << "Результат: ";
    for (int i = 1; i <= n; i++) {
        cout << ((x & mask) >> (n - i));
        mask >>= 1;
    }
}

void task2_a() {
    int n, x;
    cout << "Введите кол-во чисел в массиве (от 1 до 8): ";
    cin >> n;

    unsigned char mask = 0;

    cout << "Введите " << n << " чисел из диапазона [0; 7]\n";
    while (n--) {
        cin >> x;
        
        mask = mask | (1 << x);
    }
    
    cout << "Битовая маска: " << bitset<sizeof(mask)*8>(mask) << "\n";
    cout << "Результат: ";
    x = 0;
    while (mask > 0) {
        if (mask & 1) {
            cout << x << " ";
        }
        x++;
        mask >>= 1;
    }
   
}

void task2_b() {
    int n, x;
    cout << "Введите кол-во чисел в массиве (от 1 до 64): ";
    cin >> n;
    
    unsigned long long mask = 0;

    cout << "Введите " << n << " чисел из диапазона [0; 63]\n";
    while (n--) {
        cin >> x;
        mask |= (static_cast<unsigned long long>(1) << x);
    }
    cout << "Результат: ";
    x = 0;
    while (mask > 0) {
        if (mask & 1) {
            cout << x << " ";
        }
        x++;
        mask >>= 1;
    }
}

void task2_c() {
    int n, x;
    cout << "Введите кол-во чисел в массиве (от 1 до 64): ";
    cin >> n;

    vector<unsigned char> v(8);

    cout << "Введите " << n << " чисел из диапазона [0; 63]\n";
    while (n--) {
        cin >> x;
        v[x / 8] = v[x / 8] | (1 << x % 8);
    }
    cout << "Результат: ";
    for (int i = 0; i < v.size(); i++) {
        for (int j = 0; j < sizeof(v[i]) * 8; j++) {
            if (v[i] & (1 << j)) {
                cout << i * 8 + j << " ";
            }
        }
    }
}

void task3_a() {
    unsigned int startTime = clock();

    ifstream fin;
    ofstream fout;

    fin.open("in.txt");
    fout.open("out.txt");

    vector<bool> mask(1e7, false);
    int x;
    while (fin >> x) {
        mask[x] = true;
    }

    for (int i = 0; i < 1e7; i++) {
        if (mask[i]) {
            fout << i << " ";
        }
    }
    
    fin.close();
    fout.close();

    unsigned int endTime = clock();
    cout << "size: " << (double)sizeof(bool) * (double)mask.capacity() / (double)1024 / (double)1024 / 8 << "\n";
    cout << "time: " << (endTime - startTime) / 1000.0 << " s\n";
}

void fillFile() {
    ofstream fout;
    fout.open("in.txt");

    for (int i = 1e7 - 1; i >= 0; i--) {
        fout << i << " ";
    }
    fout.close();
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    task3_a();
}
