// Prognosis TRPO.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <clocale>
#include <Windows.h>
#include "PrognosisClasses.h"

using namespace std;

int main()
{
	setlocale(LC_ALL, "rus");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	Goods g;
	Deal q;
	vector<Goods> All_Goods;
	Prognosis All_Prognosis;
	All_Goods.clear();

	g.set_name("tovar");
	g.set_category("categoria");
	g.set_ID(1001);
	g.set_price_buy_next(43);

	g.Add_Deal();
	g.Add_Deal();
	g.Get_Good_Info();
	cout << endl;

	All_Goods.push_back(g);

	All_Prognosis.Price_Count(All_Goods);
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
