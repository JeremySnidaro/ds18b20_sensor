#include <mysql.h>

#ifndef SQLDATABASE_H_
#define SQLDATABASE_H_


class SqlDatabase
{
    MYSQL mysql;
    MYSQL_ROW row;
    MYSQL *connection;
    MYSQL_RES *result;

public:
  SqlDatabase(const char* ipServer,const char* user,const char* password,const char* database);
  ~SqlDatabase();
  
  const char** sendQuery(const char* query);
  bool isPresent(const char* query);
  
};

#endif