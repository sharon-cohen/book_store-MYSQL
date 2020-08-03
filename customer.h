#pragma once
#include "database-detail.h"
#include "header.h"
#include <string>

class customer {
protected:

	MYSQL* connect;
	MYSQL_RES* res_set;
	MYSQL_ROW row;

	unsigned int i;
public:
	customer(bool IsAdmin);
	void oldestCustomer();
	void top3buyCustomer();
	void SplitDelivery();

	void noDeal24Months();
	void contact14DaysAgo();
};