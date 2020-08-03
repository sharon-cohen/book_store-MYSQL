#include "customer.h"

customer::customer(bool IsAdmin)
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

void customer::oldestCustomer()
{
	cout << "the oldest customer:" << endl;
	mysql_query(connect, "select first_name, last_name from customer Order BY join_date limit 1");
	i = 0;
	res_set = mysql_store_result(connect);

	unsigned int numrows = mysql_num_rows(res_set);

	int num_fields = mysql_num_fields(res_set);
	while ((row = mysql_fetch_row(res_set)))
	{
		for (int i = 0; i < num_fields; i++)
		{

			if (row[i] != NULL)
				cout << row[i] << " ";
			else
				cout << "no data" << endl;
		}
		cout << endl;
	}
}

void customer::top3buyCustomer()
{
	mysql_query(connect, "select id from (select id, SUM(_sum) FROM(SELECT deal_book._sum, deal.id FROM deal_book INNER JOIN deal ON deal_book.num_deal = deal.num_deal) test GROUP BY id order by SUM(_sum) DESC) try limit 3 ");
	i = 0;
	res_set = mysql_store_result(connect);

	unsigned int numrows = mysql_num_rows(res_set);

	int num_fields = mysql_num_fields(res_set);
	cout << "The 3 customers who bought the most:" << endl;
	while ((row = mysql_fetch_row(res_set)))
	{
		for (int i = 0; i < num_fields; i++)
		{
			if (row[i] != NULL)
				cout << row[i] << endl;
			else
				cout << "NULL" << endl;
		}
	}

}

void customer::SplitDelivery()
{
	cout << "enter coustomer id" << endl;
	string id_customer;
	std::cin >> id_customer;
	string query = "select deal.id, count(deal.num_deal), delivery_id, deal.num_deal , weight, _status, type_delivery from delivery, deal where deal.num_deal = delivery.num_deal and deal.id='";
	query += id_customer;
	query += "' group by num_deal having count(deal.num_deal)>1;";
	const char* chr = query.c_str();
	mysql_query(connect, chr);
	i = 0;
	res_set = mysql_store_result(connect);

	unsigned int numrows = mysql_num_rows(res_set);
	if (numrows == 0)
		cout << "this customer hasn't split delivery" << endl;
	int num_fields = mysql_num_fields(res_set);
	while ((row = mysql_fetch_row(res_set)))
	{
		for (int i = 0; i < num_fields; i++)
		{
			if (row[i] != NULL)
				cout << row[i] << " ";
			else
				cout << "NULL" << endl;

		}
	}
}

void customer::noDeal24Months()
{
	mysql_query(connect, "select distinct customer.id, first_name, last_name from customer, deal where customer.id=deal.id and deal.date_deal<= DATE_ADD(CURDATE(), INTERVAL -24 month);");
	i = 0;
	res_set = mysql_store_result(connect);

	unsigned int numrows = mysql_num_rows(res_set);

	int num_fields = mysql_num_fields(res_set);
	while ((row = mysql_fetch_row(res_set)))
	{
		for (int i = 0; i < num_fields; i++)
		{
			if (row[i] != NULL)
				cout << row[i] << " ";
			else
				cout << "NULL" << endl;


		}
		cout << endl;
	}
}

void customer::contact14DaysAgo()
{
	mysql_query(connect, "select id, _status, closed_date from order_book WHERE closed_date>= DATE_ADD(CURDATE(), INTERVAL -14 DAY) and _status='send message';");
	i = 0;
	res_set = mysql_store_result(connect);

	unsigned int numrows = mysql_num_rows(res_set);

	int num_fields = mysql_num_fields(res_set);
	while ((row = mysql_fetch_row(res_set)))
	{
		for (int i = 0; i < num_fields; i++)
		{
			if (row[i] != NULL)
				cout << row[i] << " ";
			else
				cout << "NULL" << endl;


		}
		cout << endl;
	}
}