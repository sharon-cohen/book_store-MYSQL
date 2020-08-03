#include "database-detail.h"
#include "header.h"

class deal {
protected:

	MYSQL* connect;
	MYSQL_RES* res_set;
	MYSQL_ROW row;

	unsigned int i;
public:
	deal(bool IsAdmin);
	void customerDealsHistory();
	void MoneyFromBIT();
	void MoreThanAVG();
	void MonthProfit();
	void AVGdeals();

};