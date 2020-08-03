#include "worker.h"
#include <string>
using namespace std;
worker::worker(bool IsAdmin)
{
	connect = mysql_init(NULL);
	if (!connect)
	{
		cout << "MySQL Initialization Failed";
	}

	if(IsAdmin==true)
	connect = mysql_real_connect(connect, SERVER, USER, PASSWORD, DATABASE, 0, NULL, 0);
	if(IsAdmin==false)
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

void worker::SalaryInMonth()
{
	cout << "enter year: " << endl;
	string year;
	std::cin >> year;
	cout << "enter month: " << endl;
	string month;
	cin >> month;
	cout << "enter worker id: " << endl;
	string id;
	cin >> id;
	string query = " select hours*50, num_worker, MONTH(month_year), YEAR(month_year) from worker_salary WHERE MONTH(month_year) = ";
	query += month;
	query += " AND YEAR(month_year) = ";
	query += year;
	query += " AND num_worker = ";
	query += id;

	const char* chr = query.c_str();
	mysql_query(connect, chr);
	i = 0;
	res_set = mysql_store_result(connect);

	unsigned int numrows = mysql_num_rows(res_set);
	row = mysql_fetch_row(res_set);
	if (row == NULL) {
		cout << "The above worker did not work in the above month" << endl;
		return;
	}

	if (row != NULL)
	{
		cout << "This employee's salary this month: " << row[0] << endl;
	}
}

void worker::theBestWorker()
{
	cout << "enter year: " << endl;
	string year;
	cin >> year;
	cout << "enter month: " << endl;
	string month;
	cin >> month;
	string query = " select worker.first_name, worker.last_name, deal.num_worker from deal, worker where MONTH(date_deal) = ";
	query += month;
	query += " AND YEAR(date_deal) = ";
	query += year;
	query += " group by num_worker order by count(num_deal) desc limit 1; ";

	const char* chr = query.c_str();
	mysql_query(connect, chr);
	i = 0;
	res_set = mysql_store_result(connect);
	unsigned int numrows = mysql_num_rows(res_set);
	int num_fields = mysql_num_fields(res_set);
	row = mysql_fetch_row(res_set);
	if (row == NULL) {
		cout << "no data" << endl;
		return;
	}
	else {
		cout << "The employee with the most deals this month: " << endl;
		for (int i = 0; i < num_fields - 1; i++)
			cout << row[i] << " ";
		cout << endl;
	}
}