#include "orders.h"
#include <string>
orders::orders(bool IsAdmin)
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

void orders::orderList()
{
	mysql_query(connect, "SELECT * FROM order_book where _status = 'in proccess' order by order_date; ");

	i = 0;
	res_set = mysql_store_result(connect);

	unsigned int numrows = mysql_num_rows(res_set);
	int num_fields = mysql_num_fields(res_set);

	cout << "Current order list: " << endl;

	while (((row = mysql_fetch_row(res_set)) != NULL))
	{
		for (int i = 0; i < num_fields - 1; i++)
			cout << row[i] << " ";
		cout << endl;
	}
}

void orders::customerOrdersHistory()
{
	cout << "enter coustomer id" << endl;
	string id_customer;
	cin >> id_customer;
	string query = "select id, order_book.order_id, title, _sum, order_date, _status from order_book inner join ordervbook On order_book.order_id=ordervbook.order_id and id='";
	query += id_customer;
	query += "'";
	const char* chr = query.c_str();
	mysql_query(connect, chr);
	i = 0;
	res_set = mysql_store_result(connect);

	unsigned int numrows = mysql_num_rows(res_set);

	int num_fields = mysql_num_fields(res_set);
	row = mysql_fetch_row(res_set);
	if (row == NULL)
	{
		cout << "this customer hasn't orders history" << endl;
		return;
	}
	else {
		cout << "This customer's orders history: " << endl;
		for (int j = 0; j < numrows; j++)
		{
			for (i = 0; i < num_fields; i++)
			{
				cout << row[i] << endl;
			}
		}
	}
}