#pragma once	
#include "database-detail.h"
#include "header.h"
#include <string>
#include <iostream>

class delivery {
protected:

	MYSQL* connect;
	MYSQL_RES* res_set;
	MYSQL_ROW row;

	unsigned int i;
public:
	delivery(bool IsAdmin);
	void _statusByid();
	void sumDeliveryXpress();
	void LastYearDeliveriesByCompany();
	void DifferentEdition();
	void deliveryPrice();
};