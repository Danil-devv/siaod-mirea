#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <set>
#include <string>
#include <vector>
#include <random>

using namespace std;

vector<pair<int, int>> v; // ключ -> позиция в файле

struct student {
    int gradebook;
    int group;
    char surname[50];
};

void createBinFile(ifstream& fin, ofstream& fout) {
    student s;
    while (!fin.eof()) {
        fin >> s.gradebook;
        fin >> s.group;
        fin >> s.surname;
        fout.write((char*)&s, sizeof(student));
    }
}

void outBinFile(ifstream& fin, int count) {
    student s;
    int c = 0;
    while (!fin.eof() && c < count) {
        fin.read((char*)&s, sizeof(student));
        c++;
        cout << "{" << s.gradebook << " | " << s.group << " | " << s.surname << "}" << "\n";
    }
}

void GenerateTable(ifstream& fin, int count) {
    student s;
    int c = 0;
    while (!fin.eof() && c < count) {
        fin.read((char*)&s, sizeof(student));
        c++;
        v.push_back(make_pair(s.gradebook, (c - 1) * sizeof(student)));
    }
    sort(v.begin(), v.end());
}

void generateTxtFile(ofstream& fout, int count) {
    set<int> st;
    while (st.size() < count) {
        auto r = rand() % 1000000 + 100;
        st.insert(r);
    }

    vector<int> v;
    auto it = st.begin();
    while (it != st.end()) {
        v.push_back(*it);
        it++;
    }
    random_shuffle(v.begin(), v.end());

    for (int i = 0; i < v.size(); i++) {
        int u = v[i];
        fout << u << "\n";
        fout << u + rand() << "\n";
        fout << "test" + to_string(u);
        if (i + 1 < v.size()) fout << "\n";
    }
}

bool linearSearch(ifstream& fin, int count, int key, student *out) {
    student s;
    int c = 0;
    while (!fin.eof() && c < count) {
        fin.read((char*)&s, sizeof(student));
        c++;
        if (s.gradebook == key) {
            *out = s;
            return true;
        }
    }
    return false;
}

int binSearchInTable(int key) {
    int l = 0, r = v.size();
    while (r - l > 0) {
        int m = (l + r) / 2;
        if (v[m].first == key) {
            return v[m].second;
        }
        if (v[m].first < key) {
            l = m+1;
        }
        else {
            r = m;
        }
    }
    return -1;
}

bool binarySearchInFile(int key, student* out) {
    int pos = binSearchInTable(key);
    if (pos == -1) return false;
    FILE* ptrFile = fopen("in.dat", "r");
    fseek(ptrFile, pos, SEEK_SET);
    fread(out, sizeof(student), 1, ptrFile);
    fclose(ptrFile);
    return true;
}

int main() {
    srand(time(0));
    remove("in.txt");
    remove("in.dat");

    int n;
    cout << "Input table size:  ";
    cin >> n;

    ifstream fin, finBin;
    ofstream fout, foutBin;


    // генерируем .txt файл
    fout.open("in.txt");
    generateTxtFile(fout, n);
    fout.close();

    // заполняем бинарный файл данными из сгенерированного .txt файла
    fin.open("in.txt");
    foutBin.open("in.dat", ios::in | ios::binary | ios::app);
    createBinFile(fin, foutBin);
    fin.close();
    foutBin.close();

    // выводим бинарный файл
    /*
    finBin.open("in.dat", ios::out | ios::binary | ios::app);
    outBinFileAndGenerateTable(finBin, n);
    finBin.close();
    */

    // генерируем таблицу смещений
    finBin.open("in.dat", ios::out | ios::binary | ios::app);
    GenerateTable(finBin, n);
    finBin.close();

    cout << v[50].first << "\n";
    // Тест функции линейного поиска
    cout << "Input student gradebook to found: ";
    int key;
    cin >> key;
    student res;
    finBin.open("in.dat", ios::out | ios::binary | ios::app);
    if (linearSearch(finBin, n, key, &res)) {
        cout << "Student is found:\n" << res.gradebook << " " << res.group << " " << res.surname << "\n";
    }
    else {
        cout << "Student is not found!\n";
    }
    finBin.close();

    // Тест функции бинарного поиска
    cout << "Input student gradebook to found: ";
    cin >> key;
    if (binarySearchInFile(key, &res)) {
        cout << "Student is found:\n" << res.gradebook << " " << res.group << " " << res.surname << "\n";
    }
    else {
        cout << "Student is not found!\n";
    }
    finBin.close();
    return 0;
}
