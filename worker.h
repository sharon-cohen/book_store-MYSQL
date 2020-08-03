#include "database-detail.h"
#include "header.h"

class worker {
protected:

	MYSQL* connect;
	MYSQL_RES* res_set;
	MYSQL_ROW row;

	unsigned int i;
public:
	worker(bool IsAdmin);
	void SalaryInMonth();
	void theBestWorker();
};