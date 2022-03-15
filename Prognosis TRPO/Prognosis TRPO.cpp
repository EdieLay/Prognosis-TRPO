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
	Quarter q;
	vector<Goods> All_Goods;
	Prognosis All_Prognosis;
	All_Goods.clear();

	/* q.set_quarter_name("Q1");
	q.set_price_buy(500);
	q.set_amount_sale(700);
	q.set_amount_instock(12);
	q.set_amount_buy(50);
	q.set_amount_sale(38); */
	g.set_name("tovar");
	g.set_category("categoria");
	g.set_ID(1001);
	g.set_price_buy_next(43);

	g.Add_Quarter();
	g.Add_Quarter();
	g.Get_Good_Info();
	cout << endl;

	All_Goods.push_back(g);

	/*q = g.get_Quarter("1");
	cout << q.get_quarter_name() << endl;
	cout << q.get_price_buy() << endl;
	cout << q.get_price_sale() << endl;
	cout << q.get_amount_instock() << endl;
	cout << q.get_amount_buy() << endl;
	cout << q.get_amount_sale() << endl;*/

	All_Prognosis.Price_Count(All_Goods);
	All_Prognosis.show_price_prognosis(All_Prognosis.get_price_prognosis());
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
