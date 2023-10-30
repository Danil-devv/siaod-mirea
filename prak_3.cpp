#include <iostream>
#include <string>
#include <vector>
#include <Windows.h>
#include <random>

using namespace std;


char fio[7][32] = { "DigitaDen", "TechnoDanya", "JoBuba", "Tuberg",
"BulboVginoz", "Weisplug", "Poetress" };

char adress[7][32] = { "PeshkovStreet", "Arbekovo", "YuzhnayaPolyana", "GidroStroy",
"GPZ", "Shuist", "CentralPlo" };

struct libraryCard {
	int id;
	string fio;
	string adress;
};

class HashTable {
private:
	vector<libraryCard> table;
	int sizeOfTable;
	int numberOfAbonements;
	int currentEntries = 0;
	const int c = 1;
	const int d = 2;
	const int e = 0;


	int quadraticProbing(int index) {
		int newIndex;
		for (int i = 0; ; i++) {
			newIndex = index + c * i + d * i * i;
			if (newIndex >= table.size())
				break;
			if (table[newIndex].id == 0)
				return newIndex;
		}
		for (int j = 0; ; j++) {
			newIndex = index + c * j + e * j * j;
			if (newIndex >= table.size()) {
				cout << "down" << endl;
				exit(0);
			}
			if (table[newIndex].id == 0)
				return newIndex;
		}
	}

public:
	HashTable(int numberOfAbonemets) {
		this->numberOfAbonements = numberOfAbonemets;
		this->sizeOfTable = numberOfAbonemets * 2;
		this->table = vector<libraryCard>(sizeOfTable);
	}
	int hashFunction(int number) {
		return number % this->numberOfAbonements;
	}

	void addElement(int index, libraryCard data) {
		if (currentEntries > table.size() * 3 / 4) {
			rehash();
		}
		if (table[index].id == 0) {
			table[index] = data;
		}
		else {
			table[quadraticProbing(index)] = data;
		}
		currentEntries++;
	}

	int findElement(int id) {
		if (table[hashFunction(id)].id == id) {
			int i = hashFunction(id);
			cout << "{ " << i << " | " << table[i].id << " | " << table[i].fio << " | " << table[i].adress << " }" << endl;
			return i;
		}
		else {
			int index = hashFunction(id);
			int newIndex;
			for (int i = 0; ; i++) {
				newIndex = index + c * i + d * i * i;
				if (newIndex >= table.size())
					break;
				if (table[newIndex].id == id) {
					cout << "{ " << newIndex << " | " << table[newIndex].id << " | " << table[newIndex].fio << " | " << table[newIndex].adress << " }" << endl;
					return newIndex;
				}
			}
			for (int i = 0; ; i++) {
				newIndex = index + e * i + c * i * i;
				if (newIndex >= table.size())
					break;
				if (table[newIndex].id == id) {
					cout << "{ " << newIndex << " | " << table[newIndex].id << " | " << table[newIndex].fio << " | " << table[newIndex].adress << " }" << endl;
					return newIndex;
				}
			}
		}
	}

	void deleteElement(int id) {
		int index = findElement(id);
		table[index].id = -1;
	}

	int getNumberOfAbonements() {
		return this->numberOfAbonements;
	}

	void printArr() {
		for (int i = 0; i < table.size(); i++) {
			if (table[i].id != 0 && table[i].id != -1) {
				cout << "{ " << i << " | " << table[i].id << " | " << table[i].fio << " | " << table[i].adress << " }" << endl;
			}
		}
	}

	void rehash() {
		vector<libraryCard> oldTable = table;
		this->numberOfAbonements = currentEntries * 1.25;
		currentEntries = 0;
		this->table = vector<libraryCard>(oldTable.size() * 2);

		for (int i = 0; i < oldTable.size(); i++) {
			if (oldTable[i].id == 0 || oldTable[i].id == -1)
				continue;
			else {
				libraryCard card;
				card.id = oldTable[i].id;
				card.fio = oldTable[i].fio;
				card.adress = oldTable[i].adress;
				addElement(hashFunction(oldTable[i].id), card);
			}
		}
	}
};


HashTable initTable(int numberOfAbonements) {
	HashTable table = HashTable(numberOfAbonements);
	return table;
}

void fillInfo(HashTable& table) {
	std::random_device rd;
	std::default_random_engine generator(rd());
	std::uniform_int_distribution<unsigned int> dis(10000, 99999);

	for (int i = 0; i < table.getNumberOfAbonements(); i++) {
		libraryCard card;
		card.id = dis(generator) % 100000;
		card.fio = fio[dis(generator) % 7];
		card.adress = adress[dis(generator) % 7];

		table.addElement(table.hashFunction(card.id), card);
	}
}

void addInfo(HashTable& table, int numberOfCards) {
	std::random_device rd;
	std::default_random_engine generator(rd());
	std::uniform_int_distribution<unsigned int> dis(10000, 99999);

	for (int i = 0; i < numberOfCards; i++) {
		libraryCard card;
		card.id = dis(generator) % 100000;
		card.fio = fio[dis(generator) % 7];
		card.adress = adress[dis(generator) % 7];

		table.addElement(table.hashFunction(card.id), card);
	}
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int numberOfAbonements;
	cout << "Введите требуемый размер базы читательских билетов: ";
	cin >> numberOfAbonements;
	HashTable table = initTable(numberOfAbonements);
	fillInfo(table);
	while (true) {
		int n = 0;
		int id = 0;
		int variant = 0;
		cout << "1: Добавить элементы\n2: Удалить элемент\n3: Найти элемент\n4: Вывести таблицу\n5: Выйти\nВыберите действие: ";
		cin >> variant;
		switch (variant) {
		case 1:
			cout << "Введите количество добавляемых читательских билетов: ";
			cin >> n;
			addInfo(table, n);
			break;
		case 2:
			cout << "Введите номер удаляемого билета: ";
			cin >> id;
			table.deleteElement(id);
			cout << "Билет был удалён!" << endl;
			break;
		case 3:
			cout << "Введите номер искомого билета: ";
			cin >> id;
			table.findElement(id);
			break;
		case 4:
			table.printArr();
			break;
		case 5:
			exit(0);
		}
	}
}