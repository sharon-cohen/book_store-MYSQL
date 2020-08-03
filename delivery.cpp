#include "delivery.h"

delivery::delivery(bool IsAdmin)
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

void delivery::_statusByid()
{
	cout << "enter delivery id: " << endl;
	string id_delivery;
	std::cin >> id_delivery;
	string query = "select _status from delivery where delivery_id='";
	query += id_delivery;
	query += "'";
	const char* chr = query.c_str();
	mysql_query(connect, chr);
	i = 0;
	res_set = mysql_store_result(connect);

	unsigned int numrows = mysql_num_rows(res_set);

	int num_fields = mysql_num_fields(res_set);
	row = mysql_fetch_row(res_set);
	cout << row[0] << endl;
}

void delivery::sumDeliveryXpress()
{
	cout << "enter year: " << endl;
	string year;
	cin >> year;
	cout << "enter month: " << endl;
	string month;
	cin >> month;
	string query = "select 10*sum(delivery.weight)+20, month(date_deal) from delivery, deal, delivery_type where delivery.num_deal=deal.num_deal and MONTH(date_deal) = ";
	query += month;
	query += " AND YEAR(date_deal) = ";
	query += year;
	query += " and delivery_type.name_company='Xpress'";
	const char* chr = query.c_str();
	mysql_query(connect, chr);
	i = 0;
	res_set = mysql_store_result(connect);

	unsigned int numrows = mysql_num_rows(res_set);

	int num_fields = mysql_num_fields(res_set);
	row = mysql_fetch_row(res_set);
	if (row[0] == NULL)
		cout << "No shipments were made by Xpress in the above month" << endl;
	else
		cout << "The amount of deliveries made by Xpress in the above month:" << row[0] << endl;
}

void delivery::LastYearDeliveriesByCompany()
{

	mysql_query(connect, "select count(delivery_id), name_company from delivery, deal, delivery_type WHERE deal.date_deal>= DATE_ADD(CURDATE(), INTERVAL -12 month) and delivery.num_deal=deal.num_deal group by name_company;");
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

void delivery::DifferentEdition()
{
	mysql_query(connect, "select delivery.delivery_id, delivery._status, delivery.weight, count(delivery_edition.delivery_id) from delivery inner join delivery_edition On delivery.delivery_id=delivery_edition.delivery_id group by delivery_edition.delivery_id having count(delivery_edition.delivery_id)>1;");
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

void delivery::deliveryPrice()
{
	int x = 1;
	int i = 0;
	string arr[10];
	int deliveryType;
	int count = 0;
	while (x != 0 && i < 10) {
		cin.ignore();
		cout << "enter book title (Animal Farm / Charlotte’s Web / Gone with the Wind / Little Women / Lolita / Lord of the Flies / Romeo and Juliet / The Hobbit / The Kite Runner / Wuthering Heights)" << endl;
		getline(cin, arr[i]);
		i++;
		cout << "press 1 for more, 0 for done" << endl;
		cin >> x;
		++count;
	}


	cout << "enter delivey type (1=Israel Post-Express, 2=Israel Post-Regular, 3= Xpress-to the house, 4=Xpress-Collecting point)" << endl;
	cin >> deliveryType;

	int deliveryCost = 0;
	switch (deliveryType)
	{
	case 1:
		deliveryCost = 30;
		break;
	case 2:
		deliveryCost = 20;
	case 3:
		deliveryCost = 40;
	case 4:
		deliveryCost = 10;
	default:
		break;
	}

	string query = "select sum(weight) from books where title = '";
	for (int i = 0; i < count - 1; ++i) {
		query += arr[i];
		query += "' or title='";
	}
	query += arr[count - 1];
	query += "';";
	const char* chr = query.c_str();
	mysql_query(connect, chr);
	i = 0;
	res_set = mysql_store_result(connect);

	unsigned int numrows = mysql_num_rows(res_set);

	int num_fields = mysql_num_fields(res_set);
	row = mysql_fetch_row(res_set);
	if (row[0] == NULL)
		cout << "Error entering data" << endl;

	else {
		auto x = atoi(row[0]);
		cout << "the shipping cost is:" << x * 10 + deliveryCost << endl;
	}

}