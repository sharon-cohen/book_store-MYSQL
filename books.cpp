#include "books.h"
#include <string>
#include <iostream>

books::books(bool IsAdmin)
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

void books::isInStock()
{
	cin.ignore();
	cout << "enter the book name: ";
	string book_name;
	getline(cin, book_name);
	string query = "SELECT current_inventory FROM books where title = '";
	query += book_name;
	query += "'";
	query += " and current_inventory > 0; ";
	const char* chr = query.c_str();
	mysql_query(connect, chr);

	i = 0;
	res_set = mysql_store_result(connect);

	unsigned int numrows = mysql_num_rows(res_set);
	row = mysql_fetch_row(res_set);

	if (row==NULL)
		cout << "this book isn't in stock right now" << endl;

	while ((row!= NULL))
	{

		if (row[i] > 0) {
			cout << "this book is in stock right now" << endl;
			return;
		}

	}
	//cout << "this book isn't in stock right now" << endl;
}

void books::theOldestBook()
{
	mysql_query(connect, " select distinct supplies_book.title from supplies, supplies_book, books where full_date = (select min(full_date) from supplies) and books.current_inventory > 0 order by full_date limit 1; ");

	i = 0;
	res_set = mysql_store_result(connect);

	unsigned int numrows = mysql_num_rows(res_set);

	while (((row = mysql_fetch_row(res_set)) != NULL))
	{
		cout << "the oldest book is " << row[i] << endl;
	}

}

void books::MostTranslated()
{
	mysql_query(connect, "select distinct  e.title, count(e.title) _count from edition e inner join edition_translating et on et.edition_id = e.edition_id group by title order by  _count DESC LIMIT 1; ");

	i = 0;
	res_set = mysql_store_result(connect);

	unsigned int numrows = mysql_num_rows(res_set);

	while (((row = mysql_fetch_row(res_set)) != NULL))
	{
		cout << "the most tanslated book is " << row[i] << endl;
	}
}

void books::booksInStorage()
{
	mysql_query(connect, "select supplies_book._sum, year(full_date), month(full_date) from books, supplies, supplies_book where books.title=supplies_book.title and location='Storage' and supplies.supply_id=supplies_book.supply_id group by books.title order by year(full_date), month(full_date);");

	i = 0;
	res_set = mysql_store_result(connect);
	unsigned int numrows = mysql_num_rows(res_set);
	int num_fields = mysql_num_fields(res_set);

	cout << "this books are in the storage:" << endl;
	while (((row = mysql_fetch_row(res_set)) != NULL))
	{
		for (int i = 0; i < num_fields; i++)
			cout << row[i] << " ";
		cout << endl;
	}

}

void books::buyBooksByStore()
{
	string date_one;
	string date_two;
	cout << "Enter the start date (for example: 2020-07-05 )" << endl;
	cin >> date_one;
	cout << "Enter the end date: " << endl;
	cin >> date_two;
	string query = "select sum(_sum), sum(_sum*price_store) from supplies, books, supplies_book  where supplies_book.supply_id = supplies.supply_id and books.title=supplies_book.title and full_date between '";
	query += date_one;
	query += "' and '";
	query += date_two;
	query += "'";

	const char* chr = query.c_str();
	mysql_query(connect, chr);
	i = 0;
	res_set = mysql_store_result(connect);
	unsigned int numrows = mysql_num_rows(res_set);
	int num_fields = mysql_num_fields(res_set);
	row = mysql_fetch_row(res_set);

	for (int i = 0; i < num_fields - 1; i++) {
		if (*row[0] == '0')
		{
			cout << "The store did not purchase books on the above dates" << endl;

		}
		else
			cout << "the store bought in those dates: " << endl << row[i] << " books and paid " << row[i + 1] << " " << endl;;
	}
}

void books::soldBookCopies()
{
	cout << "enter the book name: ";
	string book_name;
	cin.ignore();
	getline(cin, book_name);
	string query = "select sum(deal_book._sum) from deal_book where title = '";
	query += book_name;
	query += "';";

	const char* chr = query.c_str();
	mysql_query(connect, chr);
	i = 0;
	res_set = mysql_store_result(connect);
	unsigned int numrows = mysql_num_rows(res_set);
	row = mysql_fetch_row(res_set);

	if (row[0] == NULL)
	{
		cout << "This book was never in stock" << endl;

	}
	else
		cout << "Number of copies of this book sold: " << row[0] << endl;
}

void books::mostReadWriter()
{
	string date_one;
	string date_two;
	cout << "Enter the start date (for example: 2020-07-05 )" << endl;
	cin >> date_one;
	cout << "Enter the end date: " << endl;
	cin >> date_two;
	string query = "SELECT _name, MAX(themax) from(select ba._name, db.num_deal, d.date_deal, db.title, SUM(db._sum) themax from book_authers ba inner join deal_book db on ba.title = db.title inner join deal d on d.num_deal = db.num_deal WHERE d.date_deal >= '";
	query += date_one;
	query += "' ";
	query += "and d.date_deal < '";
	query += date_two;
	query += "' ";
	query += "group by ba._name)  _max; ";
	const char* chr = query.c_str();
	mysql_query(connect, chr);
	i = 0;
	res_set = mysql_store_result(connect);
	unsigned int numrows = mysql_num_rows(res_set);
	row = mysql_fetch_row(res_set);
	if (row[0] == NULL) {
		cout << "No writer was read on these dates";
		return;
	}

	else
	{
		cout << "the most read writer is :" << row[i] << endl;

	}
}