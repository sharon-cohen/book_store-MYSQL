#include "database-detail.h"
#include "header.h"

class orders {
protected:

	MYSQL* connect;
	MYSQL_RES* res_set;
	MYSQL_ROW row;

	unsigned int i;
public:
	orders(bool IsAdmin);
	void orderList();
	void customerOrdersHistory();

};