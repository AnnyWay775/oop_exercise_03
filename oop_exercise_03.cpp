/*
Кулагин Даниил М8О-201Б
Вариант 15. 
6-угольник
8-угольник
Треугольник
*/


#include <iostream>
#include <vector>
#include <stdio.h>
#include <math.h>
using namespace std;


double pozitiver(double a) {
	if (a > 0) {
		return a;
	}
	else {
		return -a;
	}
}

class Coordinates {
public:
	double x;
	double y;
};

class Figure {
private:
	vector <Coordinates> coord;
public:
	Coordinates center() {
		Coordinates res;
		if (coord.size() != 0) {
			res.x = 0;
			res.y = 0;
			for (int i = 0; i < coord.size(); i++) {
				res.x += coord[i].x;
				res.y += coord[i].y;
			}
			res.x = res.x / coord.size();
			res.y = res.y / coord.size();
			cout << "Координаты центра:(" << res.x << ";" << res.y << ")" << endl;
		}
		else {
			cout << "Координаты пусты!" << endl;
		}
		return res;
	};
	void setCoordinates(int c) {
		Coordinates buf;
		char trash;
		cout << "Введите координаты в формате x,y:" << endl;
		for (int i = 0; i < c; i++) {
			cin >> buf.x >> trash >> buf.y;
			coord.push_back(buf);
		}
	};
	vector<Coordinates> getCoordinates() {
		return coord;
	}
	void printCoordinates() {
		if (coord.size() != 0) {
			switch (coord.size()) {
			case 6: cout << "Шестиугольник-";
				break;
			case 8: cout << "Восьмиугольник-";
				break;
			case 3: cout << "Треугольник-";
				break;
			}
			for (int i = 0; i < coord.size(); i++) {
				cout << "(" << coord[i].x << ";" << coord[i].y << ")" << " ";
			}
			cout << endl;
		}
		else {
			cout << "Coordinates empty" << endl;
		}
	};
	virtual double area() = 0;

};

class Hexagon : public Figure {
public:
	Hexagon() {
		setCoordinates(6);
	}
	~Hexagon() {
		setCoordinates(6);
	}
	double area() {
		double a, b, c, d, result;
		a = getCoordinates()[1].x;
		b = getCoordinates()[0].x;
		c = getCoordinates()[1].y;
		d = getCoordinates()[0].y;
		result = 2.598 * sqrt((a - b) * (a - b) + (c - d) * (c - d));
		return result;
	}
};

class Octagon :public Figure {
public:
	Octagon() {
		setCoordinates(8);
	}
	~Octagon() {
		setCoordinates(8);
	}
	double area() {
		return 4.828 * ((getCoordinates()[5].y - getCoordinates()[0].y) / 2.414) * ((getCoordinates()[5].y - getCoordinates()[0].y) / 2.414);
	}
};

class Triangle : public Figure {
public:
	Triangle() {
		setCoordinates(3);
		if (0.5 * pozitiver((getCoordinates()[1].x - getCoordinates()[0].x) * (getCoordinates()[2].y - getCoordinates()[0].y) - (getCoordinates()[2].x - getCoordinates()[0].x) * (getCoordinates()[1].y - getCoordinates()[0].y)) == 0) {
			cout << "Некорректный ввод координат треугольника!" << endl;
		}
	}
	~Triangle() {
	}
	double area() {
		return  0.5 * pozitiver((getCoordinates()[1].x - getCoordinates()[0].x) * (getCoordinates()[2].y - getCoordinates()[0].y) - (getCoordinates()[2].x - getCoordinates()[0].x) * (getCoordinates()[1].y - getCoordinates()[0].y));
	}
};

void printMenu() {
	cout << "Выберите пункт меню:" << endl;
	cout << "1)Добавить фигуру в список" << endl;
	cout << "2)Вывести все фигуры из списка" << endl;
	cout << "3)Удалить фигуру из списка" << endl;
	cout << "4)Операции над фигурами" << endl;
	cout << "5)Сумма площадей всех фигур из списка" << endl;
	cout << "0)Выход" << endl;
	cout << "------------------------------------------------------------------" << endl;
}
void printFigures(vector<Figure*> fig) {
	int z = 1;
	if (fig.size() != 0) {
		cout << "Доступные фигуры:" << endl;
		z = 1;
		for (Figure* f : fig) {
			cout << z << ")";
			(*f).printCoordinates();
			z++;
		}
	}
	else {
		cout << "Фигур пока нет!" << endl;
	}
	cout << "------------------------------------------------------------------" << endl;
}
int main() {
	setlocale(LC_ALL, "Russian");
	vector<Figure*> figures;
	bool flag = true, addflag = true;
	int choose = 0, addchoose = 4, td = 0, z = 0;
	double b = 0;
	char ans = 'n';
	while (flag) {
		printMenu();
		cin >> choose;
		switch (choose) {
		case 1:
			addchoose = 4;
			addflag = true;
			while (addflag) {
				cout << "Какую фигуру хотите добавить?" << endl;
				cout << "1)Шестиугольник\n2)Восьмиугольник\n3)Треугольник\n4)Назад" << endl;
				Figure* tr;
				cin >> addchoose;
				switch (addchoose) {
				case 1:
					tr = new Hexagon();
					break;
				case 2:
					tr = new Octagon();
					break;
				case 3:
					tr = new Triangle();
					break;
				case 4:
					addflag = false;
					break;
				}
				if (addflag) figures.push_back(tr);
			}
			break;
		case 2:
			printFigures(figures);
			break;
		case 3:
			if (figures.size() != 0) {
				printFigures(figures);
				cout << figures.size() + 1 << ")все" << endl;
				cin >> z;
				if (z == figures.size() + 1) {
					cout << "Вы действительно хотите удалить все фигуры?(y/n):";
					char ans = 'n';
					cin >> ans;
					if (ans == 'y') {
						figures.clear();
						cout << "Удалено!" << endl;
					}
					else {
						cout << "Отмена." << endl;
					}
				}
				else {
					cout << "Вы действительно хотите удалить " << z << " фигуру?(y/n):";
					cin >> ans;
					if (ans == 'y') {
						figures.erase(figures.begin() + z - 1);
						cout << "Удалено!" << endl;
					}
					else {
						cout << "Отмена." << endl;
					}
				}
			}
			else {
				cout << "Фигур пока нет" << endl;
			}
			break;
		case 4:
			addchoose = 4;
			addflag = true;
			printFigures(figures);
			cout << "С какой фигурой необходимо работать?:";
			cin >> z;
			if (z > 0 && z <= figures.size()) {
				Figure* f = figures[z - 1];
				while (addflag) {
					cout << "Выберите операцию:" << endl;
					cout << "1)Координаты вершин фигуры" << endl;
					cout << "2)Геометрический центр фигуры" << endl;
					cout << "3)Площадь фигуры" << endl;
					cout << "4)Вернуться в меню" << endl;
					cin >> td;
					switch (td) {
					case 1: (*f).printCoordinates();
						break;
					case 2:
						(*f).center();
						break;
					case 3: cout << "Площадь фигуры=" << (*f).area() << endl;
						break;
					case 4: addflag = false;
						break;
					}
				}
			}
			else {
				cout << "Неправильный номер!" << endl;
			}
			break;
		case 5:
			b = 0;
			for (Figure* f : figures) {
				b += (*f).area();
			}
			cout << "Общая площадь=" << b << endl;
			break;
		case 0: flag = false;
			break;
		}
	}
	cout << "------------------------------------------------------------------" << endl;
	return 0;
}