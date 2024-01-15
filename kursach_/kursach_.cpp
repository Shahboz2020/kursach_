#include <iostream>
#include <conio.h>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

const int  SIZE = 16; //максимальный размер стека



class Node {

private:

	int key;
	Node* pointer;

public:

	int getKey() { //геттер

		return this->key;

	}

	Node* getPointer() { //геттер

		return this->pointer;
	}

	void setNode(Node* pointer) { //сеттер 

		this->pointer = pointer;
	}

	Node() : key{ 0 }, pointer{ nullptr } {} //дефолтный конструктор

	Node(int k) { //первая перегрузка

		this->key = k;
		this->pointer = nullptr;

	}

	Node(int c, Node* pointer2) : key{ c }, pointer{ pointer2 } {} //вторая перегрузка

	~Node() { delete pointer; }
};

class Stack {
private:

	Node* lastOne; //последний элемент стека

public:

	Stack() : lastOne{ nullptr } {} //дефолтный указатель

	~Stack() { delete lastOne; } //деструктор

	Node* getlastOne() { //геттер

		return this->lastOne;

	}

	void setlastOne(Node* lastOne) { //сеттер

		this->lastOne = lastOne;

	}

	bool isEmpty() {

		if (this->amount() == 0) {

			return true;                 //проверяем стек на пустоту
		}
		else {

			return false;
		}
	}

	bool isFull() {

		if (this->amount() == SIZE) {

			return true;
		}

		else {

			return false;
		}


	}

	int amount() {

		int i = 1;
		Node* current;

		if (this->lastOne == nullptr) {

			return 0;
		}
		else {

			current = this->lastOne;

			while (current->getPointer() != nullptr) {

				i++;
				current = current->getPointer();

			}

			return i;
		}


	}

	void push(int e) { //добавляем элемент

		if (isFull()) {

			cout << "Больше не влезет" << endl;   //проверка на переполнение стека
			return;
		}

		Node* bufer = new Node(e, this->lastOne); //добавляем элмент в стек
		this->lastOne = bufer;


	}

	void pop() {

		if (isEmpty()) {

			cout << "Стек пустой" << endl; //проверка на пустоту
			return;
		}

		Node* buf = this->lastOne;
		this->lastOne = buf->getPointer();
		buf->setNode(nullptr); //вывести стек
		cout << buf->getKey() << endl;
		delete buf;

	}

	void removeStack() {

		if (isEmpty()) {

			cout << "Стек пустой" << endl; //проверка на пустоту
			return;
		}

		delete this->lastOne;
		this->lastOne = nullptr;
	}

	void print() {

		if (isEmpty()) {

			cout << "Стек пустой" << endl; //проверка на пустоту
			return;
		}

		Node* buf = this->lastOne;
		while (buf->getPointer() != nullptr) {   //выводим значение буфера

			cout << buf->getKey() << "\t";
			buf = buf->getPointer();


		}
		cout << buf->getKey() << "\t" << endl;
		cout << "Последний элемент стека самый левый" << endl;
	}

	Stack* copy() {

		Stack* bufer = new Stack();
		if (this->isEmpty()) {

			return bufer;
		}

		vector <Node*> legion; //создаем вектор
		Node* current = this->lastOne; //копия указателя на последний элемент стека
		while (current->getPointer() != nullptr) {

			legion.push_back(current);
			current = current->getPointer();

		}

		legion.push_back(current);
		for (int i = legion.size() - 1; i >= 0; i--) {

			bufer->push(legion.at(i)->getKey());

		}
		return bufer;
	}

	void inventor() {

		if (isEmpty()) {

			cout << "Стек пустой" << endl; //проверка на пустоту
			return;

		}

		vector <Node*> legion;
		Node* bufer = this->lastOne; //буфер равен последнему элементу
		while (bufer->getPointer() != nullptr) {

			legion.push_back(bufer);
			bufer = bufer->getPointer();

		}

		legion.push_back(bufer);
		reverse(legion.begin(), legion.end());
		for (int i = 0; i < legion.size() - 1; i++) {

			legion[i]->setNode(legion[i + 1]);

		}

		legion[legion.size() - 1]->setNode(nullptr);
		this->lastOne = legion.at(0);

	}

	void sumStack(Stack* newOne) {
		if (newOne->isEmpty()) {

			cout << "пустой стек" << endl; //проверка на пустоту
			return;
		}

		Stack* sumCopy = newOne->copy();
		Node* bufer = this->lastOne;
		while (bufer->getPointer() != nullptr) {

			bufer = bufer->getPointer();

		}
		bufer->setNode(this->lastOne);
		sumCopy->setlastOne(nullptr);
		delete sumCopy;
	}

	void deleteDoppelganger() {

		if (this->isEmpty()) {

			printf("Стек пуст");
			return;
		}

		vector<Node*> nodes;		//копируем ссылки на элементы в вектор
		Node* bufer = this->lastOne;
		while (bufer->getPointer() != nullptr) {
			nodes.push_back(bufer);
			bufer = bufer->getPointer();
		}

		nodes.push_back(bufer);
		bool popped = false;				//удаляем неуникальные элементы
		while (true)
		{
			std::set<int> nums;
			popped = false;
			for (int i = 0; i < nodes.size(); i++) {

				if (nums.contains(nodes[i]->getKey())) { //нашли неуникальный

					popped = true;
					nodes.erase(nodes.begin() + i);
					break;

				}

				nums.insert(nodes[i]->getKey());

			}

			if (!popped) break;

		}

		for (int i = 0; i < nodes.size() - 1; i++) {				//правим связи элементов

			nodes[i]->setNode(nodes[i + 1]);
		}

		nodes[nodes.size() - 1]->setNode(nullptr);
		this->lastOne = nodes[0];					//устанавливаем новый последний элемент стека
	}

};

int main()
{
	setlocale(LC_ALL, "rus");
	Stack* stack = new Stack();
	while (true) {
		system("cls");
		printf(
			"Размер стека: %i\n"
			"Выберите операцию:\n\n"
			"1 - удалить верхний элемент стека\n"
			"2 - вывести стек на экран\n"
			"3 - Добавить элемент в стек\n"
			"4 - инвертировать стек\n"
			"5 - очистить стек\n"
			"6 - добавить стек\n"
			"7 - удалить дубликаты\n"
			"0 - выход\n"
			"Введите ваш выбор: "
			, stack->amount());
		char choice;
		std::cin >> choice;
		if (!('0' <= choice <= '7')) continue;
		printf("\n");
		int i = choice - '0';
		switch (i) {
		case 0:
			delete stack;
			return 0;
		case 1:
			stack->pop();
			break;
		case 2:
			stack->print();
			break;
		case 3:
			printf("Введите новый элемент стека: ");
			int buf;
			std::cin >> buf;
			stack->push(buf);
			break;
		case 4:
			stack->inventor();
			break;
		case 5:
			stack->removeStack();
			break;
		case 6:
			stack->sumStack(new Stack());
			break;
		case 7:
			stack->deleteDoppelganger();
			break;
		}
		printf("\nНажмите Enter, чтобы продолжить...");
		_getch();
	}
}
