#pragma once
#include <iostream>
#include <clocale>
#include <Windows.h>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <list>
#include <iomanip>
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
	string name;
	unsigned int deal_number;
	float price_buy;
	float price_sale;
	unsigned int amount_instock;
	unsigned int amount_buy;
	unsigned int amount_sale;
public:
	Deal() {
		name = "0";
		deal_number = 0;
		price_buy = 0;
		price_sale = 0;
		amount_instock = 0;
		amount_buy = 0;
		amount_sale = 0;
	}
	Deal(string n, unsigned int dn, float pb, float ps, unsigned int ai, unsigned int ab, unsigned int as) {
		name = n;
		deal_number = dn;
		price_buy = pb;
		price_sale = ps;
		amount_instock = ai;
		amount_buy = ab;
		amount_sale = as;
	}
	~Deal() {}
	string get_name() { return name; }
	unsigned int get_deal_number() { return deal_number; }
	float get_price_buy() { return price_buy; }
	float get_price_sale() { return price_sale; }
	unsigned int get_amount_instock() { return amount_instock; }
	unsigned int get_amount_buy() { return amount_buy; }
	unsigned int get_amount_sale() { return amount_sale; }


};

class Goods {
	unsigned int ID;
	string category;
	float price_buy_next;
	vector<Deal> History;
public:
	Goods() {
		category = "0";
		ID = 0;
		price_buy_next = 0;
		History = { {"0", 0, 0, 0, 0, 0, 0} };
		History.pop_back();
	}
	Goods(string c, unsigned int ident, float p) {
		category = c;
		ID = ident;
		price_buy_next = p;
		History = { {"0", 0, 0, 0, 0, 0, 0} };
		History.pop_back();
	}
	~Goods() {}
	string get_category() { return category; }
	unsigned int get_ID() { return ID; }
	float get_price_buy_next() { return price_buy_next; }
	vector<Deal> get_History() { return History; }
	Deal& get_Deal(unsigned int dn) {
		vector<Deal>::iterator iter = History.begin();
		while (iter != History.end()) {
			if ((*iter).get_deal_number() == dn) {
				return *iter;
			}
			else iter++;
		}
	}

	void Add_Deal(string n, unsigned int dn, float pb, float ps, unsigned int ai, unsigned int ab, unsigned int as) {
		History.push_back(Deal(n, dn, pb, ps, ai, ab, as));
	}

	void Get_Good_Info() {
		cout << "ID товара: " << ID << endl;
		cout << "Категория товара: " << category << endl;
		cout << "\t\tИстория товара: " << endl;
		vector<Deal>::iterator iter = History.begin();
		while (iter != History.end()) {
			cout << "\tНомер сделки: " << (*iter).get_deal_number() << endl;
			cout << "Наименование товара: " << (*iter).get_name() << endl;
			cout << "Закупочная цена товара: " << (*iter).get_price_buy() << endl;
			cout << "Цена продажи товара: " << (*iter).get_price_sale() << endl;
			cout << "Количество товара в наличии: " << (*iter).get_amount_instock() << endl;
			cout << "Количество закупленного товара: " << (*iter).get_amount_buy() << endl;
			cout << "Количество проданного товара: " << (*iter).get_amount_sale() << endl;
			iter++;
		}
		cout << "_________________________________________________________\n";
	}

	string GetCsvGoods() {
		string data;

		vector<Deal>::iterator iter = History.begin();
		data = data + to_string(ID) + ";" + (*iter).get_name() + ";" + category + ";" + to_string((*iter).get_deal_number()) + ";" + to_string((*iter).get_price_buy()) + ";" +
			to_string((*iter).get_price_sale()) + ";" + to_string((*iter).get_amount_instock()) + ";" + to_string((*iter).get_amount_buy()) + ";" + to_string((*iter).get_amount_sale());
		iter++;

		return data;
	}
};

vector<Goods> get_data() {
	string str, str0, n_n, n_c;
	unsigned int n_id, n_ai, n_ab, n_as, n_dn = 1;
	float n_p, n_pb, n_ps;
	int n0 = 0, n1 = 0;
	bool b;

	string path = "Deals.csv";
	ifstream file;
	file.open(path);
	if (!file.is_open()) cout << "Ошибка открытия файла!" << endl;
	else cout << "Файл открыт!" << endl;

	vector<Goods> all_Goods;
	all_Goods.clear();
	int amount_goods = -1;

	while (!file.eof()) {
		getline(file, str);
		n0++;
	}
	file.close();
	file.open(path);

	vector<Goods>::iterator iter_goods;
	getline(file, str);
	int y, x = 0;
	while (n1 != n0 - 2) {
		getline(file, str);
		n1++;

		x = 0; y = x;
		while (str[x] != ';') x++; //1
		for (int i = 0; i < x; i++) {
			str0 += str[i];
		}
		n_id = stoi(str0);
		str0.clear();
		x++;
		y = x;

		while (str[x] != ';') x++;
		for (int i = y; i < x; i++) {
			n_n += str[i];
		}
		x++;
		y = x;

		while (str[x] != ';') x++;
		for (int i = y; i < x; i++) {
			n_c += str[i];
		}
		x++;
		y = x;

		while (str[x] != ';') x++; //4
		for (int i = y; i < x; i++) {
			str0 += str[i];
		}
		n_pb = stof(str0);
		str0.clear();
		x++;
		y = x;

		while (str[x] != ';') x++;
		for (int i = y; i < x; i++) {
			str0 += str[i];
		}
		n_ps = stof(str0);
		str0.clear();
		x++;
		y = x;

		while (str[x] != ';') x++; //6
		for (int i = y; i < x; i++) {
			str0 += str[i];
		}
		n_ai = stoi(str0);
		str0.clear();
		x++;
		y = x;

		while (str[x] != ';') x++;
		for (int i = y; i < x; i++) {
			str0 += str[i];
		}
		n_ab = stoi(str0);
		str0.clear();
		x++;
		y = x;

		while (str[x] != ';') x++;
		for (int i = y; i < x; i++) {
			str0 += str[i];
		}
		n_as = stoi(str0);
		str0.clear();
		x++;
		y = x;

		while (str[x] != ';') x++; //9
		for (int i = y; i < x; i++) {
			str0 += str[i];
		}
		n_p = stof(str0);
		str0.clear();

		b = true;
		if (amount_goods > -1) {
			iter_goods = all_Goods.begin();
			while (iter_goods != all_Goods.end())
			{
				if ((*iter_goods).get_ID() == n_id)
				{
					b = false;
					break;
				}
				iter_goods++;
			}
		}

		if (b) {
			all_Goods.push_back(Goods(n_c, n_id, n_p));
			n_dn = 1;
			amount_goods++;
		}


		all_Goods[amount_goods].Add_Deal(n_n, n_dn, n_pb, n_ps, n_ai, n_ab, n_as);
		n_dn++;

		n_n.clear();
		n_c.clear();
	}
	file.close();
	return all_Goods;
}

/*vector<Goods> get_data() {
	string line_from_file, str0, n_n, new_category;
	unsigned int newId = 0, n_ai, n_ab, n_as, n_dn = 1;
	float new_price_buy_next, n_pb, n_ps;
	int number_of_lines = 0, n1 = 0;
	bool b;
	vector<Goods>::iterator iter_goods;

	string path = "Deals.csv";
	ifstream file;
	file.open(path);

	if (!file.is_open())
		cout << "Ошибка открытия файла!" << endl;
	else
		cout << "Файл открыт!" << endl;

	vector<Goods> vector_Goods;
	vector_Goods.clear();

	if (file) {
		vector<string> vector_csv_element;
		list<vector<string>> two_list_csv_element;

		string header{};
		if (getline(file, header))
			cout << header << '\n';

		while (getline(file, line_from_file)) {
			string word;
			for (char item_line : line_from_file) {
				word += item_line;
				if (item_line == ';') {
					vector_csv_element.push_back(word);
					word = "";
				}
			}
			vector_csv_element.push_back(word);///для последнего элемента
			two_list_csv_element.push_back(vector_csv_element);
			vector_csv_element.clear();
		}

		for (vector<string> item_list : two_list_csv_element) { ///вывод
			for (string item_string : item_list) {
				cout << item_string << "\t";
			}
			cout << "\n";
		}
		try {
			for (vector<string> item_vector : two_list_csv_element) {///запись
				if (newId != stoi(item_vector[0])) {
					new_category = item_vector[2];
					newId = stoi(item_vector[0]);
					new_price_buy_next = stoi(item_vector[8]);
					vector_Goods.push_back(Goods(new_category, newId, new_price_buy_next));
				}
				vector_Goods.back().Add_Deal(item_vector[1], n_dn++, stoi(item_vector[3]), stoi(item_vector[4]), stoi(item_vector[5]), stoi(item_vector[6]), stoi(item_vector[7]));
			}
		}
		catch (exception e) {
			cout << "недостаточно элементов";
			cout << e.what();
		}

	}

	file.close();
	return vector_Goods;
}*/

float get_demand(float y, float y1, float y2, unsigned int x1, unsigned int x2)
{
	return (y - y1) * ((float)x2 - (float)x1) / (y2 - y1) + (float)x1;
}

pair<float, unsigned int> func_max(float first_point, float second_point, float y, float y1, float y2, unsigned int x1, unsigned int x2, float prognosis_price_buy, float previous_max)
{
	float max_func = -1000000, i = 0, argument_step = (second_point - first_point)/10;
	while ((y + i - prognosis_price_buy) * get_demand(y + i, y1, y2, x1, x2) > max_func)
	{
		max_func = (y + i - prognosis_price_buy) * get_demand(y + i, y1, y2, x1, x2);
		i += argument_step;
	}
	if ((floor(max_func) == floor(previous_max)) || (floor(max_func) == ceil(previous_max)) || (floor(previous_max) == ceil(max_func)))
		return { y + i - argument_step, (unsigned int)floor(get_demand(y + i - argument_step, y1, y2, x1, x2)) };
	else return func_max(y + i - 2 * argument_step, y + i, y + i - 2 * argument_step, y1, y2, x1, x2, prognosis_price_buy, max_func);
}

float get_avg_float(vector<Deal> curr_history, int option)
{
	float avg = 0;
	int i;
	if (option == 1)
	{
		for (i = 0; i <= curr_history.size() / 2; i++)
			avg += curr_history[i].get_price_sale();
		avg /= curr_history.size() / 2 + 1;
		return avg;
	}
	else if (option == 2)
	{
		for (i = (curr_history.size() + 1) / 2 - 1; i < curr_history.size(); i++)
			avg += curr_history[i].get_price_sale();
		avg /= curr_history.size() / 2 + 1;
		return avg;
	}
	else return -1;
}

unsigned int get_avg_int(vector<Deal> curr_history, int option)
{
	unsigned int avg = 0;
	int i;
	if (option == 1)
	{
		for (i = 0; i <= curr_history.size() / 2; i++)
			avg += curr_history[i].get_amount_sale();
		avg /= curr_history.size() / 2 + 1;
		return avg;
	}
	else if (option == 2)
	{
		for (i = (curr_history.size() + 1) / 2 - 1; i < curr_history.size(); i++)
			avg += curr_history[i].get_amount_sale();
		avg /= curr_history.size() / 2 + 1;
		return avg;
	}
	else return -1;
}

bool comp(Deal a, Deal b)
{
	return a.get_price_sale() > b.get_price_sale();
}

class Prognosis
{
	vector<pair<float, unsigned int>> price_prognosis;
public:
	Prognosis()
	{
		price_prognosis = { {0, 0 } };
		price_prognosis.clear();
	}
	void Price_Count(vector<Goods> all_goods)
	{
		float avg_pr1, avg_pr2;
		unsigned int avg_am1, avg_am2;
		vector<Deal> curr_history;
		vector<Goods>::iterator goods_iter = all_goods.begin();
		while (goods_iter != all_goods.end())
		{
			curr_history = (*goods_iter).get_History();
			sort(curr_history.begin(), curr_history.end(), comp);
			if (curr_history.size() == 2)
			{
				avg_pr1 = curr_history[0].get_price_sale();
				avg_am1 = curr_history[0].get_amount_sale();
				avg_pr2 = curr_history[1].get_price_sale();
				avg_am2 = curr_history[1].get_amount_sale();
				if (avg_pr1 > avg_pr2 && avg_am1 < avg_am2 || (avg_pr1 < avg_pr2 && avg_am1 > avg_am2))
					price_prognosis.push_back(func_max(min(avg_pr1, avg_pr2), max(avg_pr1, avg_pr2), min(avg_pr1, avg_pr2), avg_pr1, avg_pr2, avg_am1, avg_am2, (*goods_iter).get_price_buy_next(), -1000000));
				else price_prognosis.push_back(make_pair(0, 0));
			}
			else if (curr_history.size() >= 3)
			{
				avg_pr1 = get_avg_float(curr_history, 1);
				avg_am1 = get_avg_int(curr_history, 1);
				avg_pr2 = get_avg_float(curr_history, 2);
				avg_am2 = get_avg_int(curr_history, 2);
				if (avg_pr1 > avg_pr2 && avg_am1 < avg_am2 || (avg_pr1 < avg_pr2 && avg_am1 > avg_am2))
					price_prognosis.push_back(func_max(min(avg_pr1, avg_pr2), max(avg_pr1, avg_pr2), min(avg_pr1, avg_pr2), avg_pr1, avg_pr2, avg_am1, avg_am2, (*goods_iter).get_price_buy_next(), -1000000));
				else price_prognosis.push_back(make_pair(0, 0));
			}
			else
				price_prognosis.push_back(make_pair(0, 0));
			goods_iter++;
		}
	}

	vector<pair<float, unsigned int>> get_price_prognosis() { return price_prognosis; }

	void GetAllPricePrognosis() {
		vector<pair<float, unsigned int>>::iterator price_item = price_prognosis.begin();

		for (price_item; price_item != price_prognosis.end(); ++price_item) {
			cout << "Прогнозируемая цена: " << price_item->first
				<< "\nПрогнозируемый спрос:  " << price_item->second << endl;
		}
	}

	/*string GetCsvPrognosis() {
		string data;

		vector<pair<float, unsigned int>>::iterator price_item = price_prognosis.begin();
		data = data + to_string(price_item->first) + ";" + to_string(price_item->second) + "\n";
		price_item++;
		return data;
	}*/
};

void print_prognosis(vector<Goods> all_Goods, vector<pair<float, unsigned int>> prognosis)
{
	vector<Goods>::iterator goods_iter = all_Goods.begin();
	vector<pair<float, unsigned int>>::iterator pr_iter = prognosis.begin();
	cout << "ID\tЦена\t\tСпрос" << endl;
	while (pr_iter != prognosis.end())
	{
		cout << (*goods_iter).get_ID() << "\t" << (*pr_iter).first << "\t\t" << (*pr_iter).second << endl;
		pr_iter++;
		goods_iter++;
	}
}