// DatabaseUser.cpp : Defines the entry point for the console application.
//

#include "Database.h"
#include "stdafx.h"


int main()
{
	Database::Database db = Database::Database();
	db.testLinkage();
	Database::Table table = Database::Table();
	table.testLinkage();
	Database::Record record = Database::Record(5);
	record.testLinkage();
    return 0;
}

