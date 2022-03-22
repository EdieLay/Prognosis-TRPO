#pragma once
#include <iostream>
#include <clocale>
#include <Windows.h>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int err_0() {
	int a, ival = 1;
	cin >> a;
	while (ival == 1) {
		if (cin.fail() || a < 0) {
			cin.clear();
			cin.ignore(32767, '\n');
			cout << "Ошибка! Попробуйте еще раз: ";
			cin >> a;
		}
		else
			ival = 0;
	}
	return a;
}

float err_1() {
	float a;
	int ival = 1;
	cin >> a;
	while (ival == 1) {
		if (cin.fail() || a < 0) {
			cin.clear();
			cin.ignore(32767, '\n');
			cout << "Ошибка! Попробуйте еще раз: ";
			cin >> a;
		}
		else
			ival = 0;
	}
	return a;
}

class Deal {
	unsigned int deal_number;
	float price_buy;
	float price_sale;
	unsigned int amount_instock;
	unsigned int amount_buy;
	unsigned int amount_sale;
public:
	Deal() {
		deal_number = 0;
		price_buy = 0;
		price_sale = 0;
		amount_instock = 0;
		amount_buy = 0;
		amount_sale = 0;
	}
	Deal(unsigned int dn, float pb, float ps, unsigned int ai, unsigned int ab, unsigned int as) { 
		deal_number = dn;
		price_buy = pb;
		price_sale = ps;
		amount_instock = ai;
		amount_buy = ab;
		amount_sale = as;
	}
	~Deal() {}
	unsigned int get_deal_number() { return deal_number; }
	float get_price_buy() { return price_buy; }
	float get_price_sale() { return price_sale; }
	unsigned int get_amount_instock() { return amount_instock; }
	unsigned int get_amount_buy() { return amount_buy; }
	unsigned int get_amount_sale() { return amount_sale; }

	void set_deal_name(unsigned int dn) { deal_number = dn; }
	void set_price_buy(float pb) { price_buy = pb; }
	void set_price_sale(float ps) { price_sale = ps; }
	void set_amount_instock(unsigned int ai) { amount_instock = ai; }
	void set_amount_buy(unsigned int ab) { amount_buy = ab; }
	void set_amount_sale(unsigned int as) { amount_sale = as; }
};

class Goods {
	string name;
	string category;
	unsigned int ID;
	float price_buy_next;
	vector<Deal> History;
public:
	Goods() {
		name = "0";
		category = "0";
		ID = 0;
		price_buy_next = 0;
		History = { {0, 0, 0, 0, 0, 0} }; 
		History.pop_back();
	}
	Goods(string n, string c, unsigned int ident, float p) {
		name = n;
		category = c;
		ID = ident;
		price_buy_next = p;
		History = { {0, 0, 0, 0, 0, 0} };
		History.pop_back();
	}
	~Goods() {}
	string get_name() { return name; }
	string get_category() { return category; }
	unsigned int get_ID() { return ID; }
	float get_price_buy_next() { return price_buy_next; }
	vector<Deal> get_History() { return History; }

	//Deal& get_History(int index) { return History[index]; }
	Deal& get_Deal(unsigned int dn) {
		vector<Deal>::iterator iter = History.begin();
		while (iter != History.end()) {
			if ((*iter).get_deal_number() == dn) {
				return *iter;
			}
			else iter++;
		}
	}

	void set_name(string n) { name = n; }
	void set_category(string c) { category = c; }
	void set_ID(unsigned int ident) { ID = ident; }
	void set_price_buy_next(float p) { price_buy_next = p; }
	void set_History(int index, Deal h) { History[index] = h; } //нужно ли вообще?

	void Add_Deal() {
		float pb, ps;
		unsigned int ai, ab, as, qn;
		cout << "Введите номер сделки: ";
		qn = err_0();
		cout << "Введите закупочную цену товара: ";
		pb = err_1();
		cout << "Введите цену продажи товара: ";
		ps = err_1();
		cout << "Введите количество товара в наличии: ";
		ai = err_0();
		cout << "Введите количество закупленного товара: ";
		ab = err_0();
		cout << "Введите количество проданного товара: ";
		as = err_0();
		History.push_back(Deal(qn, pb, ps, ai, ab, as));
		cout << "_________________________________________________________\n";
		cin.get();
	}
	void Get_Good_Info() {
		cout << "Наименование товара: " << name << endl;
		cout << "Категория товара: " << category << endl;
		cout << "ID товара: " << ID << endl;
		cout << "\t\tИстория товара: " << endl;
		vector<Deal>::iterator iter = History.begin();
		while (iter != History.end()) {
			cout << "\tНомер сделки: " << (*iter).get_deal_number() << endl;
			cout << "Закупочная цена товара: " << (*iter).get_price_buy() << endl;
			cout << "Цена продажи товара: " << (*iter).get_price_sale() << endl;
			cout << "Количество товара в наличии: " << (*iter).get_amount_instock() << endl;
			cout << "Количество закупленного товара: " << (*iter).get_amount_buy() << endl;
			cout << "Количество проданного товара: " << (*iter).get_amount_sale() << endl;
			iter++;
		}
		cout << "_________________________________________________________\n";
	}
};

float get_demand(float y, float y1, float y2, int x1, int x2)
{
	return (y - y1) * ((float)x2 - (float)x1) / (y2 - y1) + (float)x1;
}

pair<float, float> func_max(float first_point, float second_point, float y, float y1, float y2, int x1, int x2, float prognosis_price_buy, float previous_max)
{
	float max_func = -1000000, i = 0, argument_step = (second_point - first_point)/10;
	while ((y + i - prognosis_price_buy) * get_demand(y + i, y1, y2, x1, x2) > max_func)
	{
		max_func = (y + i - prognosis_price_buy) * get_demand(y + i, y1, y2, x1, x2);
		i += argument_step;
	}
	if ((floor(max_func) == floor(previous_max)) || (floor(max_func) == ceil(previous_max)) || (floor(previous_max) == ceil(max_func)))
		return { y + i - argument_step, get_demand(y + i - argument_step, y1, y2, x1, x2) };
	else return func_max(y + i - 2 * argument_step, y + i, y + i - 2 * argument_step, y1, y2, x1, x2, prognosis_price_buy, max_func);
}

class Prognosis
{
	vector<pair<string, pair<float, float>>> price_prognosis;
public:
	Prognosis()
	{
		price_prognosis = { {"0", {0, 0} } };
		price_prognosis.clear();
	}
	void Price_Count(vector<Goods> all_goods)
	{
		float max_price_sale, min_price_sale, max_amount_sale, min_amount_sale, temp_price, temp_amount;
		vector<Deal> curr_history;
		vector<Goods>::iterator goods_iter = all_goods.begin();
		vector<Deal>::iterator deal_iter;
		while (goods_iter != all_goods.end())
		{
			curr_history = (*goods_iter).get_History();
			if (curr_history.size() > 1)
			{
				deal_iter = curr_history.begin();
				max_price_sale = (*deal_iter).get_price_sale();
				min_price_sale = max_price_sale;
				max_amount_sale = (*deal_iter).get_amount_sale();
				min_amount_sale = max_amount_sale;
				deal_iter++;
				while (deal_iter != curr_history.end())
				{
					temp_price = (*deal_iter).get_price_sale();
					temp_amount = (*deal_iter).get_amount_sale();
					max_price_sale = max(max_price_sale, temp_price);
					min_price_sale = min(min_price_sale, temp_price);
					max_amount_sale = max(max_amount_sale, temp_amount);
					min_amount_sale = min(min_amount_sale, temp_amount); // сделать, чтобы количество проданного товара соответствовало цене
					deal_iter++;
				}
				if (max_price_sale > min_price_sale && max_amount_sale > min_amount_sale)
				{
					price_prognosis.push_back(make_pair((*goods_iter).get_name(), func_max(min_price_sale, max_price_sale, min_price_sale, max_price_sale, min_price_sale, min_amount_sale, max_amount_sale, (*goods_iter).get_price_buy_next(), -100000)));
				}
				else
				{
					price_prognosis.push_back(make_pair((*goods_iter).get_name(), make_pair(0, 0)));
				}
			}
			else price_prognosis.push_back(make_pair((*goods_iter).get_name(), make_pair(0, 0)));
			goods_iter++;
		}
	}
	void show_price_prognosis(vector<pair<string, pair <float, float>>> price_prognosis)
	{
		vector<pair<string, pair<float, float>>>::iterator iter = price_prognosis.begin();
		while (iter != price_prognosis.end())
		{
			cout << "Название товара: " << (*iter).first << endl;
			cout << "Спрогнозированная цена продажи: " << (*iter).second.first << endl;
			cout << "Спрогнозированный спрос: " << floor((*iter).second.second) << endl;
			iter++;
		}
	}
	vector<pair<string, pair<float, float>>> get_price_prognosis() { return price_prognosis; }
};