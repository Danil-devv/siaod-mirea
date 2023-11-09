#include <iostream>
#include <string>
#include <vector>
#include <Windows.h>
#include <random>

using namespace std;
char telephoneNumber[7][10] = { "951217722", "951267722", "751200021", "123456788",
"224477244", "950177805", "555355553" };

char adress[7][32] = { "Mozhga", "Moscow", "Nizhniye", "Piter",
"Kazan", "Ryazan", "Novosibirsk" };


struct phoneOwner {
	int index;
	string telephoneNumber;
	string adress;
};

class HashTable {
private:
	vector<phoneOwner> table;
	int size;
	int cnt;
	int entities = 0;
	const int c = 1;
	const int d = 2;
	const int e = 0;


public:
	HashTable(int cnt) {
		this->cnt = cnt;
		this->size = cnt * 2;
		this->table = vector<phoneOwner>(size);
	}

	int probing(int index) {
		int newIndex;
		for (int i = 0; ; i++) {
			newIndex = index + c * i + d * i * i;
			if (newIndex >= table.size())
				break;
			if (table[newIndex].index == 0)
				return newIndex;
		}
		for (int j = 0; ; j++) {
			newIndex = index + c * j + e * j * j;
			if (newIndex >= table.size()) {
				cout << "down" << endl;
				exit(0);
			}
			if (table[newIndex].index == 0)
				return newIndex;
		}
	}

	void addElement(int index, phoneOwner data) {
		if (entities > table.size() * 3 / 4) {
			rehash();
		}
		if (table[index].index == 0) {
			table[index] = data;
		}
		else {
			table[probing(index)] = data;
		}
		entities++;
	}

	int findElement(int ind) {
		if (table[hash(ind)].index == ind) {
			int i = hash(ind);
			cout << "{ " << i << " | " << table[i].index << " | " << table[i].telephoneNumber << " | " << table[i].adress << " }" << endl;
			return i;
		}
		else {
			int index = hash(ind);
			int newIndex;
			for (int i = 0; ; i++) {
				newIndex = index + c * i + d * i * i;
				if (newIndex >= table.size())
					break;
				if (table[newIndex].index == ind) {
					cout << "{ " << newIndex << " | " << table[newIndex].index << " | " << table[newIndex].telephoneNumber << " | " << table[newIndex].adress << " }" << endl;
					return newIndex;
				}
			}
			for (int i = 0; ; i++) {
				newIndex = index + e * i + c * i * i;
				if (newIndex >= table.size())
					break;
				if (table[newIndex].index == ind) {
					cout << "{ " << newIndex << " | " << table[newIndex].index << " | " << table[newIndex].telephoneNumber << " | " << table[newIndex].adress << " }" << endl;
					return newIndex;
				}
			}
		}
	}

	int hash(int number) {
		return number % this->cnt;
	}

	void deleteElement(int index) {
		int id = findElement(index);
		table[id].index = -1;
	}

	void rehash() {
		vector<phoneOwner> oldTable = table;
		this->cnt = entities * 1.25;
		entities = 0;
		this->table = vector<phoneOwner>(oldTable.size() * 2);

		for (int i = 0; i < oldTable.size(); i++) {
			if (oldTable[i].index == 0 || oldTable[i].index == -1)
				continue;
			else {
				phoneOwner card;
				card.index = oldTable[i].index;
				card.telephoneNumber = oldTable[i].telephoneNumber;
				card.adress = oldTable[i].adress;
				addElement(hash(oldTable[i].index), card);
			}
		}
	}

	int getNumberOfAbonements() {
		return this->cnt;
	}

	void printTable() {
		cout << "{  хеш  |   номер   |  город  }\n";
		for (int i = 0; i < table.size(); i++) {
			if (table[i].index != 0 && table[i].index != -1) {
				cout << "{ " << table[i].index << " | " << table[i].telephoneNumber << " | " << table[i].adress << " }\n";
			}
		}
	}
};

HashTable createTable(int cnt) {
	HashTable t = HashTable(cnt);
	return t;
}

void autoFillTable(HashTable& table) {
	random_device rd;
	default_random_engine g(rd());
	uniform_int_distribution<unsigned int> d(10000, 99999);

	for (int i = 0; i < table.getNumberOfAbonements(); i++) {
		phoneOwner card;
		card.index = d(g) % 100000;
		card.telephoneNumber = telephoneNumber[d(g) % 7];
		card.adress = adress[d(g) % 7];

		table.addElement(table.hash(card.index), card);
	}
}

// Функция добавляет строки в хеш таблицу в рандомном порядке
void addRows(HashTable& table, int numberOfCards) {
	random_device rd;
	default_random_engine generator(rd());
	uniform_int_distribution<unsigned int> dis(10000, 99999);

	for (int i = 0; i < numberOfCards; i++) {
		phoneOwner card;
		card.index = dis(generator) % 100000;
		card.telephoneNumber = telephoneNumber[dis(generator) % 7];
		card.adress = adress[dis(generator) % 7];

		table.addElement(table.hash(card.index), card);
	}
}


int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int cnt;
	cout << "Введите размер таблицы телефонных номеров: ";
	cin >> cnt;
	HashTable table = createTable(cnt);
	autoFillTable(table);

	int n = 0;
	int hash = 0;
	int command = 0;

	while (true) {
		cout << "1: Вывести таблицу\n2: Добавить элемент\n3: Найти элемент\n4: Удалить элемент\n5: Выйти\nВведите комманду: ";

		cin >> command;
		switch (command) {
		case 1:
			table.printTable();
			break;
		case 2:
			cout << "Введите количество добавляемых телефонных номеров: ";
			cin >> n;
			addRows(table, n);
			break;
		case 3:
			cout << "Введите хеш искомого телефонного номера: ";
			cin >> hash;
			table.findElement(hash);
			break;
		case 4:
			cout << "Введите хеш удаляемого телефонного номера: ";
			cin >> hash;
			table.deleteElement(hash);
			cout << "Телефонный номер был удалён!" << endl;
			break;
		case 5:
			exit(0);
		}
	}
}