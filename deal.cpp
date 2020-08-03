#include "deal.h"
#include <string>
deal::deal(bool IsAdmin)
{
	connect = mysql_init(NULL);
	if (!connect)
	{
		cout << "MySQL Initialization Failed";
	}

	if (IsAdmin == true)
		connect = mysql_real_connect(connect, SERVER, USER, PASSWORD, DATABASE, 0, NULL, 0);
	if (IsAdmin == false)
		connect = mysql_real_connect(connect, SERVER, USERWORKER, PASSWORKER, DATABASE, 0, NULL, 0);

	if (connect)
	{
		cout << "Connection Succeeded\n";
	}

	else
	{
		cout << "Connection Failed\n";
	}
}

void deal::customerDealsHistory()
{
	cout << "enter the customer id: " << endl;
	string id_customer;
	cin >> id_customer;
	string query = "select books.title, date_deal, price from books inner join deal_book On books.title = deal_book.title inner join deal on deal_book.num_deal = deal.num_deal where id = '";
	query += id_customer;
	query += "';";

	const char* chr = query.c_str();
	mysql_query(connect, chr);

	i = 0;
	res_set = mysql_store_result(connect);

	unsigned int numrows = mysql_num_rows(res_set);
	int num_fields = mysql_num_fields(res_set);
	row = mysql_fetch_row(res_set);
	if (row == NULL)
	{
		cout << "this customer hasn't deals history" << endl;
		return;
	}
	else {
		cout << "This customer's deals history: " << endl;
		for (int j = 0; j < numrows; j++)
		{
			for (i = 0; i < num_fields; i++)
			{
				cout << row[i] << endl;
			}
		}
	}
}

void deal::MoneyFromBIT()
{
	cout << "enter year: " << endl;
	string year;
	cin >> year;
	cout << "enter month: " << endl;
	string month;
	cin >> month;
	string query = "select SUM(payment_sum) from deal where payment_way = 'Bit' and MONTH(date_deal) = ";
	query += month;
	query += " and YEAR(date_deal) = ";
	query += year;
	query += ";";
	const char* chr = query.c_str();
	mysql_query(connect, chr);
	i = 0;
	res_set = mysql_store_result(connect);

	unsigned int numrows = mysql_num_rows(res_set);

	int num_fields = mysql_num_fields(res_set);
	row = mysql_fetch_row(res_set);
	if (row[0] == NULL)
		cout << "No money was transferred from BIT in the above month" << endl;
	else
		cout << "The amount of money transferred from BIT in the above month:" << row[0] << endl;
}

void deal::MoreThanAVG()
{
	mysql_query(connect, "SELECT deal.num_deal FROM deal WHERE payment_sum > (SELECT AVG(payment_sum) FROM deal) AND date_deal >= DATE_ADD(CURDATE(), INTERVAL - 1 YEAR); ");

	i = 0;
	res_set = mysql_store_result(connect);
	unsigned int numrows = mysql_num_rows(res_set);
	cout << "The deals from the last 12 months with more profit than average: " << endl;
	while (((row = mysql_fetch_row(res_set)) != NULL))
	{
		cout << "deal No." << row[i] << endl;

	}
}

void deal::MonthProfit()
{
	cout << "enter year: " << endl;
	string year;
	cin >> year;
	cout << "enter month: " << endl;
	string month;
	cin >> month;
	string query = "select sum(payment_sum)- sum(_sum*price_store) from deal,supplies, books, supplies_book where MONTH(date_deal) =  ";
	query += month;
	query += " AND YEAR(date_deal) =";
	query += year;
	query += " and supplies_book.supply_id = supplies.supply_id and books.title=supplies_book.title and MONTH(full_date) = ";
	query += month;
	query += " AND YEAR(full_date) = ";
	query += year;

	const char* chr = query.c_str();
	mysql_query(connect, chr);
	i = 0;
	res_set = mysql_store_result(connect);

	unsigned int numrows = mysql_num_rows(res_set);
	row = mysql_fetch_row(res_set);
	if (row == NULL || *row == 0) {
		cout << "The store did not make a profit in the above month" << endl;
		return;
	}
	cout << "Store profit in this month: " << endl;
	if (row != NULL)
	{
		cout << row[0] << endl;

	}

}

void deal::AVGdeals()
{
	mysql_query(connect, "select AVG(payment_sum), month(date_deal) from deal where deal.date_deal >= DATE_ADD(CURDATE(), INTERVAL - 1 YEAR) GROUP BY MONTH(date_deal); ");

	i = 0;
	res_set = mysql_store_result(connect);

	unsigned int numrows = mysql_num_rows(res_set);
	int num_fields = mysql_num_fields(res_set);

	cout << "Annual average monthly transactions: " << endl;
	while (((row = mysql_fetch_row(res_set)) != NULL))
	{
		for (int i = 0; i < num_fields; i++)
			cout << row[i] << " ";
		cout << endl;

	}
}