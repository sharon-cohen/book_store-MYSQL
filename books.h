#include "database-detail.h"
#include "header.h"
#include <string>
#include <iostream> 


class books {
protected:

	MYSQL* connect;
	MYSQL_RES* res_set;
	MYSQL_ROW row;
	unsigned int i;

public:
	books(bool IsAdmin);
	void isInStock();
	void theOldestBook();
	void MostTranslated();
	void booksInStorage();
	void buyBooksByStore();
	void soldBookCopies();
	void mostReadWriter();
};