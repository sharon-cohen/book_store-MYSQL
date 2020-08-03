#include "books.h"
#include "orders.h"
#include "deal.h"
#include "worker.h"
#include "customer.h"
#include "delivery.h"
#include <string>

int main(void)
{
	
	bool IsAdmin = false;
	bool start = true;


	while (start)
	{


		char user[30], pass[30];
		cout << "user name: ";
		cin >> user;
		cout << "password";
		cin >> pass;


		if (strcmp(user, USER) == 0 && strcmp(pass, PASSWORD) == 0)
		{
			IsAdmin = true;
			cout << "\nLOGIN  WORKER SUCCESS.\n";
			start = false;
		}
		else {

			if (strcmp(user, USERWORKER) == 0 && strcmp(pass, PASSWORKER) == 0) {
				printf("\nLOGIN  ADMIN SUCCESS.\n");
				IsAdmin = false;
				start = false;
			}

			else
			{
				printf("\nLOGIN FAILED.\n");
				
			}
		}

	}
	int choose = 0;
	books b(IsAdmin);
	orders o(IsAdmin);
	deal d(IsAdmin);
	worker w(IsAdmin);
	customer c(IsAdmin);
	delivery del(IsAdmin);
	int cont=1;

	cout << "welcome to our second-hand bookstore database app!" << endl;
	do
	{
		cout << "select the desired action:" << endl;
		cout << "1) is book x in stock?" << endl;
		cout << "2) who is the oldest customer?" << endl;
		cout << "3) what is the oldest book?" << endl;
		cout << "4) show the current order list" << endl;
		cout << "5) how many copies of book y were sold by the store?" << endl;
		cout << "6) who is the most read writer between the dates x to y?" << endl;
		cout << "7) list of the 3 customers who have purchased the most books over the years" << endl;
		cout << "8) who is the book with the largest number of translations currently in stock?" << endl;
		cout << "9) customer x purchase history: what books did he purchase, on what datesand what price did he pay for each book" << endl;
		cout << "10) order history of person x" << endl;
		cout << "11) shipping cost calculation" << endl;
		cout << "12) has customer x ever split a book purchase for multiple shipments and if so what are the shipping data ? " << endl;
		cout << "13) what is the current status of a particular delivery?" << endl;
		cout << "14) what is the amount of shipments made by xpress in a particular month?" << endl;
		cout << "15) the total money transferred to the store account via the bit app" << endl;
		cout << "16) what are the transactions that have been made during the last 12 months, and which have led greater profit than the average trading profit in these 12 months ? " << endl;
		cout << "17) how many shipments have been made during the last 12 months via israel post, and how many have been made via xpress?" << endl;
		cout << "18) data on all shipments ever made, including at least 2 different editions of the same book" << endl;
		cout << "19) data on all customers who have purchased, at any time, at least one book from the store, and who have not made any purchases during the last 24 months" << endl;
		cout << "20) list of customers who placed orders, the books they ordered arrived at the store, the store contacted them to inform them of the availability of the book. the contact was made 14 days ago, and customers have not yet purchased the book." << endl;
		cout << "21) number of books in the storage on a monthly basis" << endl;
		cout << "22) how many books did the store purchase between d1 and d2, and what was the total payment for them." << endl;
		cout << "23) the store profits from sales in a particular month" << endl;
		cout << "24) annual average monthly transactions" << endl;
		if (IsAdmin) {
			cout << "25) the salary of worker z in a particular month " << endl;
			cout << "26) who sells the most deals in month x?" << endl;
		}
		cout << "-1) exit" << endl;
		cin >> choose;

		switch (choose)
		{
		case 1:
			b.isInStock();
			cout << "press 1 to continue or 0 to exit" << endl;
			cin >> cont;
			break;
		case 2:
			c.oldestCustomer();
			cout << "press 1 to continue or 0 to exit" << endl;
			cin >> cont;
			break;
		case 3:
			b.theOldestBook();
			cout << "press 1 to continue or 0 to exit" << endl;
			cin >> cont;
			break;
		case 4:
			o.orderList();
			cout << "press 1 to continue or 0 to exit" << endl;
			cin >> cont;
			break;
		case 5:
			b.soldBookCopies();
			cout << "press 1 to continue or 0 to exit" << endl;
			cin >> cont;
			break;
		case 6:
			b.mostReadWriter();
			cout << "press 1 to continue or 0 to exit" << endl;
			cin >> cont;
			break;
		case 7:
			c.top3buyCustomer();
			cout << "press 1 to continue or 0 to exit" << endl;
			cin >> cont;
			break;
		case 8:
			b.MostTranslated();
			cout << "press 1 to continue or 0 to exit" << endl;
			cin >> cont;
			break;
		case 9:
			d.customerDealsHistory();
			cout << "press 1 to continue or 0 to exit" << endl;
			cin >> cont;
			break;
		case 10:
			o.customerOrdersHistory();
			cout << "press 1 to continue or 0 to exit" << endl;
			cin >> cont;
			break;
		case 11:
			del.deliveryPrice();
			cout << "press 1 to continue or 0 to exit" << endl;
			cin >> cont;
			break;
		case 12:
			c.SplitDelivery();
			cout << "press 1 to continue or 0 to exit" << endl;
			cin >> cont;
			break;
		case 13:
			del._statusByid();
			cout << "press 1 to continue or 0 to exit" << endl;
			cin >> cont;
			break;
		case 14:
			del.sumDeliveryXpress();
			cout << "press 1 to continue or 0 to exit" << endl;
			cin >> cont;
			break;
		case 15:
			d.MoneyFromBIT();
			cout << "press 1 to continue or 0 to exit" << endl;
			cin >> cont;
			break;
		case 16:
			d.MoreThanAVG();
			cout << "press 1 to continue or 0 to exit" << endl;
			cin >> cont;
			break;
		case 17:
			del.LastYearDeliveriesByCompany();
			cout << "press 1 to continue or 0 to exit" << endl;
			cin >> cont;
			break;
		case 18:
			del.DifferentEdition();
			cout << "press 1 to continue or 0 to exit" << endl;
			cin >> cont;
			break;
		case 19:
			c.noDeal24Months();
			cout << "press 1 to continue or 0 to exit" << endl;
			cin >> cont;
			break;
		case 20:
			c.contact14DaysAgo();
			cout << "press 1 to continue or 0 to exit" << endl;
			cin >> cont;
			break;
		case 21:
			b.booksInStorage();
			cout << "press 1 to continue or 0 to exit" << endl;
			cin >> cont;
			break;
		case 22:
			b.buyBooksByStore();
			cout << "press 1 to continue or 0 to exit" << endl;
			cin >> cont;
			break;
		case 23:
			d.MonthProfit();
			cout << "press 1 to continue or 0 to exit" << endl;
			cin >> cont;
			break;
		case 24:
			d.AVGdeals();
			cout << "press 1 to continue or 0 to exit" << endl;
			cin >> cont;
			break;
		case 25:
			w.SalaryInMonth();
			cout << "press 1 to continue or 0 to exit" << endl;
			cin >> cont;
			break;
		case 26:
			w.theBestWorker();
			cout << "press 1 to continue or 0 to exit" << endl;
			cin >> cont;
			break;
		case -1:
			cout << "thank you" << endl;
			break;

		default:
			break;
		}
	} while (choose != 27 && cont==1);

}
