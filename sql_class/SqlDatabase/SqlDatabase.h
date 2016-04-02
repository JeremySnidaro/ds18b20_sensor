#include <mysql.h>

#ifndef SQL_DATABASE_H_
#define SQL_DATABASE_H_


class SqlDatabase
{
    MYSQL mysql;
    MYSQL_ROW row;
    MYSQL *connection;

public:
  SqlDatabase (const char* ipServer, const char* user,
               const char* password, const char* database);
  ~SqlDatabase();
  
  void sendQuery (const char* query);
  
};

#endif // SQL_DATABASE_H_

